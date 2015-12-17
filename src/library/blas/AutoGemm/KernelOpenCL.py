import os
import sys
import copy
import Common
import KernelParameters
import AutoGemmParameters
import argparse


##############################################################################
# Make OpenCL Kernel String
##############################################################################
def makeOpenCLKernelString(kernel):
  endLine = "\\n\"\n\""

  ####################################
  # parameters valid?
  if kernel.isValid() == False:
    return kernel.getName() + " invalid"

  ####################################
  # initializations
  kStr = ""
  kStr += endLine
  kStr += "/* %s */" % kernel.getName()
  kStr += endLine

  ####################################
  # Double precision pragma
  prec = kernel.getName()[0].lower()
  if prec == "d" or prec == "z":
    kStr += endLine
    kStr += "#pragma OPENCL EXTENSION cl_khr_fp64 : enable" + endLine

  ####################################
  # kernel parameters
  kStr += endLine
  kStr += "/* kernel parameters */" + endLine
  #if kernel.order == "clblasColumnMajor":
  #  kStr += "#define COLUMN_MAJOR          1" + endLine
  #else:
  #  kStr += "#define COLUMN_MAJOR          0" + endLine
  #if kernel.transA == "T":
  #  kStr += "#define TRANSPOSE_A           1" + endLine
  #else:
  #  kStr += "#define TRANSPOSE_A           0" + endLine
  #if kernel.transB == "T":
  #  kStr += "#define TRANSPOSE_B           1" + endLine
  #else:
  #  kStr += "#define TRANSPOSE_B           0" + endLine
  #kStr += "" + endLine
  kStr += "#define WG_NUM_ROWS          %d%s" % (kernel.workGroupNumRows, endLine )
  kStr += "#define WG_NUM_COLS          %d%s" % (kernel.workGroupNumCols, endLine )
  kStr += "#define MICRO_TILE_NUM_ROWS  %d%s" % (kernel.microTileNumRows, endLine )
  kStr += "#define MICRO_TILE_NUM_COLS  %d%s" % (kernel.microTileNumCols, endLine )
  kStr += "#define MACRO_TILE_NUM_ROWS  %s%s" % ((kernel.workGroupNumRows * kernel.microTileNumRows), endLine )
  kStr += "#define MACRO_TILE_NUM_COLS  %s%s" % ((kernel.workGroupNumCols * kernel.microTileNumCols), endLine )
  kStr += "#define NUM_UNROLL_ITER      %s%s" % (kernel.unroll, endLine )
  kStr += "" + endLine
  kStr += "#define LOCAL_ROW_PAD        %s%s" % (kernel.localRowPad, endLine)
  kStr += "#define LOCAL_COL_PAD        %s%s" % (kernel.localColPad, endLine)

  ####################################
  # global memory indices
  # A
  kStr += endLine
  kStr += "/* global memory indices */" + endLine
  if (kernel.order=="clblasColumnMajor")==(kernel.transA=="N"):
    kStr += "#define GET_GLOBAL_INDEX_A(ROW,COL) ((COL)*lda+(ROW))" + endLine
  else:
    kStr += "#define GET_GLOBAL_INDEX_A(ROW,COL) ((ROW)*lda+(COL))" + endLine
  # B
  if (kernel.order=="clblasColumnMajor")==(kernel.transB=="N"):
    kStr += "#define GET_GLOBAL_INDEX_B(ROW,COL) ((COL)*ldb+(ROW))" + endLine
  else:
    kStr += "#define GET_GLOBAL_INDEX_B(ROW,COL) ((ROW)*ldb+(COL))" + endLine
  # C
  if (kernel.order=="clblasColumnMajor"):
    kStr += "#define GET_GLOBAL_INDEX_C(ROW,COL) ((COL)*ldc+(ROW))" + endLine
  else:
    kStr += "#define GET_GLOBAL_INDEX_C(ROW,COL) ((ROW)*ldc+(COL))" + endLine

  ####################################
  # local memory indices
  # A
  kStr += endLine
  kStr += "/* local memory indices */" + endLine
  kStr += "#define GET_LOCAL_INDEX_A(ROW,COL) ((ROW) + (COL)*((MACRO_TILE_NUM_ROWS)+(LOCAL_COL_PAD)) )" + endLine
  # B
  kStr += "#define GET_LOCAL_INDEX_B(ROW,COL) ((COL) + (ROW)*((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) )" + endLine

  ####################################
  # data types
  kStr += endLine
  kStr += "/* data types */" + endLine
  kStr += "#define DATA_TYPE_STR %s%s" \
      % (Common.openclDataType[kernel.precision], endLine)
  if kernel.precision=="s" or kernel.precision=="d":
    # real arithmetic
    kStr += "#define TYPE_MAD(MULA,MULB,DST) DST = mad(MULA,MULB,DST);" + endLine
    if kernel.beta==1:
      kStr += "#define TYPE_MAD_WRITE(DST,ALPHA,REG,BETA) DST = (ALPHA)*(REG) + (BETA)*(DST);" + endLine
    else:
      kStr += "#define TYPE_MAD_WRITE(DST,ALPHA,REG,BETA) DST = (ALPHA)*(REG);" + endLine

  else:
    # complex arithmetic
    if kernel.transA!="C" and kernel.transB!="C":
      # neither conjugate
      kStr += (
        "#define TYPE_MAD(MULA,MULB,DST) \\\\" + endLine +
        "  DST.s0 = mad(  MULA.s0, MULB.s0, DST.s0 ); \\\\" + endLine +
        "  DST.s0 = mad( -MULA.s1, MULB.s1, DST.s0 ); \\\\" + endLine +
        "  DST.s1 = mad(  MULA.s0, MULB.s1, DST.s1 ); \\\\" + endLine +
        "  DST.s1 = mad(  MULA.s1, MULB.s0, DST.s1 );" + endLine )
    elif kernel.transA=="C" and kernel.transB!="C":
      # A conjugate (negate imaginary A.s1)
      kStr += (
        "#define TYPE_MAD(MULA,MULB,DST) \\\\" + endLine +
        "  DST.s0 = mad(  MULA.s0, MULB.s0, DST.s0 ); \\\\" + endLine +
        "  DST.s0 = mad(  MULA.s1, MULB.s1, DST.s0 ); \\\\" + endLine +
        "  DST.s1 = mad(  MULA.s0, MULB.s1, DST.s1 ); \\\\" + endLine +
        "  DST.s1 = mad( -MULA.s1, MULB.s0, DST.s1 );" + endLine )
    elif kernel.transA!="C" and kernel.transB=="C":
      # B conjugate (negate imaginary B.s1)
      kStr += (
        "#define TYPE_MAD(MULA,MULB,DST) \\\\" + endLine +
        "  DST.s0 = mad(  MULA.s0,  MULB.s0, DST.s0 ); \\\\" + endLine +
        "  DST.s0 = mad( -MULA.s1, -MULB.s1, DST.s0 ); \\\\" + endLine +
        "  DST.s1 = mad(  MULA.s0, -MULB.s1, DST.s1 ); \\\\" + endLine +
        "  DST.s1 = mad(  MULA.s1,  MULB.s0, DST.s1 );" + endLine )
    else:
      # A & B conjugate (negate imaginary .s1)
      kStr += (
        "#define TYPE_MAD(MULA,MULB,DST) \\\\" + endLine +
        "  DST.s0 = mad(  MULA.s0,  MULB.s0, DST.s0 ); \\\\" + endLine +
        "  DST.s0 = mad(  MULA.s1, -MULB.s1, DST.s0 ); \\\\" + endLine +
        "  DST.s1 = mad(  MULA.s0, -MULB.s1, DST.s1 ); \\\\" + endLine +
        "  DST.s1 = mad( -MULA.s1,  MULB.s0, DST.s1 );" + endLine )
    if kernel.beta==1:
      kStr += (
        "#define TYPE_MAD_WRITE( DST, ALPHA, REG, BETA ) \\\\" + endLine +
        "  /* (1) */ \\\\" + endLine +
        "  type_mad_tmp = REG.s0; \\\\" + endLine +
        "  REG.s0 *= ALPHA.s0; \\\\" + endLine +
        "  REG.s0 = mad( -ALPHA.s1, REG.s1, REG.s0 ); \\\\" + endLine +
        "  REG.s1 *= ALPHA.s0; \\\\" + endLine +
        "  REG.s1 = mad(  ALPHA.s1, type_mad_tmp, REG.s1 ); \\\\" + endLine +
        "  /* (2) */ \\\\" + endLine +
        "  REG.s0 = mad(  BETA.s0, DST.s0, REG.s0 ); \\\\" + endLine +
        "  REG.s0 = mad( -BETA.s1, DST.s1, REG.s0 ); \\\\" + endLine +
        "  REG.s1 = mad(  BETA.s1, DST.s0, REG.s1 ); \\\\" + endLine +
        "  REG.s1 = mad(  BETA.s0, DST.s1, REG.s1 ); \\\\" + endLine +
        "  /* (3) */ \\\\" + endLine +
        "  DST = REG;" + endLine )
    else:
      kStr += (
        "#define TYPE_MAD_WRITE( DST, ALPHA, REG, BETA ) \\\\" + endLine +
        "  /* (1) */ \\\\" + endLine +
        "  type_mad_tmp = REG.s0; \\\\" + endLine +
        "  REG.s0 *= ALPHA.s0; \\\\" + endLine +
        "  REG.s0 = mad( -ALPHA.s1, REG.s1, REG.s0 ); \\\\" + endLine +
        "  REG.s1 *= ALPHA.s0; \\\\" + endLine +
        "  REG.s1 = mad(  ALPHA.s1, type_mad_tmp, REG.s1 ); \\\\" + endLine +
        "  DST = REG;" + endLine )

  ####################################
  # micro-tile
  kStr += endLine
  kStr += "/* %dx%d micro-tile */%s" % (kernel.microTileNumRows, kernel.microTileNumCols, endLine)
  kStr += "#define MICRO_TILE \\\\" + endLine
  for a in range(0, int(kernel.microTileNumRows)):
    kStr += "  rA[%d] = localA[offA + %d*WG_NUM_ROWS]; \\\\%s" % (a, a, endLine)
  for b in range(0, int(kernel.microTileNumCols)):
    kStr += "  rB[%d] = localB[offB + %d*WG_NUM_COLS]; \\\\%s" % (b, b, endLine)
  kStr += "  offA += (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD); \\\\" + endLine
  kStr += "  offB += (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD); \\\\" + endLine
  for a in range(0, int(kernel.microTileNumRows)):
    for b in range(0, int(kernel.microTileNumCols)):
      kStr += "  TYPE_MAD(rA[%d],rB[%d],rC[%d][%d]); \\\\%s" % (a, b, a, b, endLine)
  kStr += "  mem_fence(CLK_LOCAL_MEM_FENCE);" + endLine
  kStr += endLine

  ####################################
  # function signature
  ####################################
  kStr += "__attribute__((reqd_work_group_size(WG_NUM_COLS,WG_NUM_ROWS,1)))" + endLine
  kStr += "__kernel void %s" % ( kernel.getName() )
  kStr += "(" + endLine
  # arguments
  kStr += (
    "  __global DATA_TYPE_STR const * restrict A," + endLine +
    "  __global DATA_TYPE_STR const * restrict B," + endLine +
    "  __global DATA_TYPE_STR       *          C," + endLine +
    "  DATA_TYPE_STR const alpha," + endLine +
    "  DATA_TYPE_STR const beta," + endLine +
    "  uint const M," + endLine +
    "  uint const N," + endLine +
    "  uint const K," + endLine +
    "  uint const lda," + endLine +
    "  uint const ldb," + endLine +
    "  uint const ldc," + endLine +
    "  uint const offsetA," + endLine +
    "  uint const offsetB," + endLine +
    "  uint const offsetC" + endLine +
    ") {" + endLine )

  ####################################
  # apply offsets
  kStr += endLine
  kStr += (
    "  /* apply offsets */" + endLine +
    "  A += offsetA;" + endLine +
    "  B += offsetB;" + endLine +
    "  C += offsetC;" + endLine )

  ####################################
  # allocate registers
  kStr += endLine
  kStr += (
    "  /* allocate registers */" + endLine +
    "  DATA_TYPE_STR rC[MICRO_TILE_NUM_ROWS][MICRO_TILE_NUM_COLS] = { {0} };" + endLine +
    "  DATA_TYPE_STR rA[MICRO_TILE_NUM_ROWS];" + endLine +
    "  DATA_TYPE_STR rB[MICRO_TILE_NUM_COLS];" + endLine )

  ####################################
  # allocate local memory
  kStr += endLine
  kStr += (
    "  /* allocate local memory */" + endLine +
    "  __local DATA_TYPE_STR localA[NUM_UNROLL_ITER*(MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD)];" + endLine +
    "  __local DATA_TYPE_STR localB[NUM_UNROLL_ITER*(MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD)];" + endLine )

  ####################################
  # work item indices
  kStr += endLine
  kStr += "  /* work item indices */" + endLine
  if kernel.isRowKernel():
    kStr += "  uint groupRow = M / " + str(kernel.workGroupNumRows*kernel.microTileNumRows) + "; // last row" + endLine
  else:
    kStr += "  uint groupRow = get_group_id(0);" + endLine
  if kernel.isColKernel():
    kStr += "  uint groupCol = N / " + str(kernel.workGroupNumCols*kernel.microTileNumCols) + "; // last column" + endLine
  else:
    kStr += "  uint groupCol = get_group_id(1);" + endLine

  ####################################
  # z-order - TODO doesn't improve caching, only lowers occupancy
  if False:
    kStr += (
        "  // convert work-group order to z-order" + endLine +
        "  unsigned int morton = get_group_id(1) * get_num_groups(0) + get_group_id(0);" + endLine +
        "  groupRow = morton;" + endLine +
        "  groupCol = ( groupRow >> 1 );" + endLine +
        "  groupRow &= 0x55555555;" + endLine +
        "  groupCol &= 0x55555555;" + endLine +
        "  groupRow |= ( groupRow >> 1 );" + endLine +
        "  groupCol |= ( groupCol >> 1 );" + endLine +
        "  groupRow &= 0x33333333;" + endLine +
        "  groupCol &= 0x33333333;" + endLine +
        "  groupRow |= ( groupRow >> 2 );" + endLine +
        "  groupCol |= ( groupCol >> 2 );" + endLine +
        "  groupRow &= 0x0f0f0f0f;" + endLine +
        "  groupCol &= 0x0f0f0f0f;" + endLine +
        "  groupRow |= ( groupRow >> 4 );" + endLine +
        "  groupCol |= ( groupCol >> 4 );" + endLine +
        "  groupRow &= 0x00ff00ff;" + endLine +
        "  groupCol &= 0x00ff00ff;" + endLine +
        "  groupRow |= ( groupRow >> 8 );" + endLine +
        "  groupCol |= ( groupCol >> 8 );" + endLine +
        "  groupRow &= 0x0000ffff;" + endLine +
        "  groupCol &= 0x0000ffff;" + endLine + endLine
        )

  kStr += (
    "  uint localRow = get_local_id(0);" + endLine +
    "  uint localCol = get_local_id(1);" + endLine +
    "  uint localSerial = localRow + localCol*WG_NUM_ROWS;" + endLine )

  ####################################
  # global indices being loaded
  kStr += endLine
  kStr += "  /* global indices being loaded */" + endLine
  if (kernel.order=="clblasColumnMajor")==(kernel.transA=="N"):
    kStr += (
      "#define globalARow(LID) (groupRow*MACRO_TILE_NUM_ROWS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_ROWS)" + endLine +
      "#define globalACol(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_ROWS)" + endLine )
  else:
    kStr += (
      "#define globalARow(LID) (groupRow*MACRO_TILE_NUM_ROWS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER)" + endLine +
      "#define globalACol(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER)" + endLine )

  if (kernel.order=="clblasColumnMajor")==(kernel.transB=="N"):
    kStr += (
      "#define globalBRow(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER)" + endLine +
      "#define globalBCol(LID) (groupCol*MACRO_TILE_NUM_COLS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER)" + endLine )
  else:
    kStr += (
      "#define globalBRow(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_COLS)" + endLine +
      "#define globalBCol(LID) (groupCol*MACRO_TILE_NUM_COLS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_COLS)" + endLine )

  #kStr += (
  #  "  A += GET_GLOBAL_INDEX_A( globalARow, globalACol );" + endLine +
  #  "  B += GET_GLOBAL_INDEX_B( globalBRow, globalBCol );" + endLine )

  ####################################
  # loop over k
  kStr += endLine
  kStr += (
    "  /* loop over k */" + endLine +
    "  uint block_k = K / NUM_UNROLL_ITER;" + endLine +
    "  do {" + endLine )

  ####################################
  # local indices being written
  kStr += endLine
  kStr += "    /* local indices being written */" + endLine
  if (kernel.order=="clblasColumnMajor")==(kernel.transA=="N"):
    kStr += (
      "#define localARow (localSerial % MACRO_TILE_NUM_ROWS)" + endLine +
      "#define localACol (localSerial / MACRO_TILE_NUM_ROWS)" + endLine +
      "#define localAStride (WG_NUM_ROWS*WG_NUM_COLS)" + endLine )
  else:
    kStr += (
      "#define localARow (localSerial / NUM_UNROLL_ITER)" + endLine +
      "#define localACol (localSerial % NUM_UNROLL_ITER)" + endLine +
      "#define localAStride (WG_NUM_ROWS*WG_NUM_COLS/NUM_UNROLL_ITER)" + endLine )

  if (kernel.order=="clblasColumnMajor")==(kernel.transB=="N"):
    kStr += (
      "#define localBRow ( localSerial % NUM_UNROLL_ITER )" + endLine +
      "#define localBCol ( localSerial / NUM_UNROLL_ITER )" + endLine +
      "#define localBStride (WG_NUM_ROWS*WG_NUM_COLS/NUM_UNROLL_ITER)" + endLine )
  else:
    kStr += (
      "#define localBRow ( localSerial / MACRO_TILE_NUM_COLS )" + endLine +
      "#define localBCol ( localSerial % MACRO_TILE_NUM_COLS )" + endLine +
      "#define localBStride  (WG_NUM_ROWS*WG_NUM_COLS)" + endLine )


  kStr += (
    "    __local DATA_TYPE_STR *lA = localA + GET_LOCAL_INDEX_A(localARow, localACol);" + endLine +
    "    __local DATA_TYPE_STR *lB = localB + GET_LOCAL_INDEX_B(localBRow, localBCol);" + endLine +
    "    barrier(CLK_LOCAL_MEM_FENCE);" + endLine )

  ####################################
  # load global -> local
  # threads to do loading = (workGroupNumRows*workGroupNumCols)
  # A elements to be loaded = workGroupNumRows*microTileNumRows*unroll
  # B elements to be loaded = workGroupNumCols*microTileNumCols*unroll
  kStr += endLine
  kStr += "    /* load global -> local */" + endLine
  numALoads  = (kernel.workGroupNumRows*kernel.microTileNumRows*kernel.unroll) \
      // (kernel.workGroupNumRows*kernel.workGroupNumCols) # // -- integer divide
  numALoadsR = (kernel.workGroupNumRows*kernel.microTileNumRows*kernel.unroll) \
      % (kernel.workGroupNumRows*kernel.workGroupNumCols)
  numBLoads  = (kernel.workGroupNumCols*kernel.microTileNumCols*kernel.unroll) \
      // (kernel.workGroupNumRows*kernel.workGroupNumCols) # // - integer divide
  numBLoadsR = (kernel.workGroupNumCols*kernel.microTileNumCols*kernel.unroll) \
      % (kernel.workGroupNumRows*kernel.workGroupNumCols)

  # TODO - zeroString for real and complex
  if kernel.precision == "c":
    zeroString = "(float2)(0.f, 0.f)"
  elif kernel.precision == "z":
    zeroString = "(double2)(0.0, 0.0)"
  else:
    zeroString = "0.0"
  for a in range(0, int(numALoads)):
    kStr += "    lA[ %d*localAStride ] = " % a
    if kernel.isRowKernel():
      kStr += "( globalARow(%d) >= M) ? %s : " % ( a, zeroString )
    kStr += "A[ GET_GLOBAL_INDEX_A( globalARow(%d), globalACol(%d) ) ];%s" % (a, a, endLine)
  if numALoadsR:
    kStr += "    if ( localSerial + " + str(numALoads) + "*WG_NUM_ROWS*WG_NUM_COLS < (WG_NUM_ROWS*MICRO_TILE_NUM_ROWS*NUM_UNROLL_ITER) ) {" + endLine
    kStr += "      lA[ %d*localAStride ] = " % numALoads
    if kernel.isRowKernel():
      kStr += "( globalARow(%d) >= M) ? %s : " % ( numALoads, zeroString )
    kStr += "A[ GET_GLOBAL_INDEX_A( globalARow(%d), globalACol(%d) ) ];%s" % (numALoads, numALoads, endLine)
    kStr += "    }" + endLine

  for b in range(0, int(numBLoads)):
    kStr += "    lB[ %d*localBStride ] = " % b
    if kernel.isColKernel():
      kStr += "( globalBCol(%d) >= N) ? %s : " % ( b, zeroString )
    kStr += "B[ GET_GLOBAL_INDEX_B( globalBRow(%d), globalBCol(%d) ) ];%s" % (b, b, endLine)
  if numBLoadsR:
    kStr += "    if ( localSerial + " + str(numBLoads) + "*WG_NUM_ROWS*WG_NUM_COLS < (WG_NUM_COLS*MICRO_TILE_NUM_COLS*NUM_UNROLL_ITER) ) {" + endLine
    kStr += "      lB[ %d*localBStride ] = " % numBLoads
    if kernel.isColKernel():
      kStr += "(globalBCol(%d) >= N) ? %s : " % ( numBLoads, zeroString )
    kStr += "B[ GET_GLOBAL_INDEX_B( globalBRow(%d), globalBCol(%d) ) ];%s" % (numBLoads, numBLoads, endLine)
    kStr += "    }" + endLine
  kStr += (
    "    barrier(CLK_LOCAL_MEM_FENCE);" + endLine +
    "    uint offA = localRow;" + endLine +
    "    uint offB = localCol;" + endLine )

  ####################################
  # do mads
  kStr += endLine
  kStr += "    /* do mads */" + endLine
  for u in range(0, int(kernel.unroll)):
    kStr += "    MICRO_TILE" + endLine

  ####################################
  # shift to next k block
  kStr += endLine
  kStr += "    /* shift to next k block */" + endLine
  if (kernel.order=="clblasColumnMajor")==(kernel.transA=="N"):
    kStr += "    A += lda*NUM_UNROLL_ITER;" + endLine
  else:
    kStr += "    A += NUM_UNROLL_ITER;" + endLine
  if (kernel.order=="clblasColumnMajor")==(kernel.transB=="N"):
    kStr += "    B += NUM_UNROLL_ITER;" + endLine
  else:
    kStr += "    B += ldb*NUM_UNROLL_ITER;" + endLine

  ####################################
  # end loop
  kStr += endLine
  kStr += "  } while (--block_k > 0);" + endLine
  kStr += endLine

  ####################################
  # which global Cij index
  kStr += endLine
  kStr += "  /* which global Cij index */" + endLine
  kStr += "  uint globalCRow = groupRow * MACRO_TILE_NUM_ROWS + localRow;" + endLine
  kStr += "  uint globalCCol = groupCol * MACRO_TILE_NUM_COLS + localCol;" + endLine

  ####################################
  # write global Cij
  kStr += endLine
  kStr += "  /* write global Cij */" + endLine
  if kernel.precision=="c":
    kStr += "  float type_mad_tmp;" + endLine
  if kernel.precision=="z":
    kStr += "  double type_mad_tmp;" + endLine

  for a in range(0, int(kernel.microTileNumRows)):
    for b in range(0, int(kernel.microTileNumCols)):
      if kernel.isRowKernel():
        kStr += "  if (globalCRow+%d*WG_NUM_ROWS < M)" % a
      if kernel.isColKernel():
        kStr += "  if (globalCCol+%d*WG_NUM_COLS < N)" % b
      if kernel.isRowKernel() or kernel.isColKernel():
        kStr += "{"
      kStr += "  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+%d*WG_NUM_ROWS, globalCCol+%d*WG_NUM_COLS) ], alpha, rC[%d][%d], beta )" % (a, b, a, b)
      if kernel.isRowKernel() or kernel.isColKernel():
        kStr += "}"
      kStr += endLine

  ####################################
  # end kernel
  kStr += endLine
  kStr += "}" + endLine

  return kStr


##############################################################################
# Write OpenCL kernel to file
##############################################################################
def writeOpenCLKernelToFile(kernel):
  kernelName = kernel.getName()
  kernelString = makeOpenCLKernelString(kernel)
  kernelFileName = Common.getKernelSourcePath() + kernelName +"_src.cpp"
  kernelFile = open(kernelFileName, "w")
  kernelFile.write( Common.getAutoGemmHeader() )
  kernelFile.write("#ifndef KERNEL_" + kernelName.upper() + "_SRC_H\n")
  kernelFile.write("#define KERNEL_" + kernelName.upper() + "_SRC_H\n")
  kernelFile.write("\n")
  kernelFile.write("const unsigned int %s_workGroupNumRows = %u;\n" % (kernel.getName(), kernel.workGroupNumRows ) )
  kernelFile.write("const unsigned int %s_workGroupNumCols = %u;\n" % (kernel.getName(), kernel.workGroupNumCols ) )
  kernelFile.write("const unsigned int %s_microTileNumRows = %u;\n" % (kernel.getName(), kernel.microTileNumRows ) )
  kernelFile.write("const unsigned int %s_microTileNumCols = %u;\n" % (kernel.getName(), kernel.microTileNumCols ) )
  kernelFile.write("const unsigned int %s_unroll = %u;\n" % (kernel.getName(), kernel.unroll) )
  kernelFile.write("\n")
  kernelFile.write("const char * const %s_src =\"" % (kernelName) )
  kernelFile.write(kernelString)
  kernelFile.write("\";\n")
  kernelFile.write("\n")
  kernelFile.write("#else\n")
  kernelFile.write("#pragma message(\"AutoGemmKernelSources.cpp: %s was overriden by user kernel.\")\n" % kernel.getName() )
  kernelFile.write("#endif\n")
  kernelFile.close()


##############################################################################
# Write OpenCL kernel to file
##############################################################################
def writeOpenCLKernels():

  if not os.path.exists( Common.getKernelSourcePath() ):
    os.makedirs( Common.getKernelSourcePath() )
  if not os.path.exists( Common.getKernelBinaryPath() ):
    os.makedirs( Common.getKernelBinaryPath() )

  numKernels = 0
  # for each precision
  kernel = KernelParameters.KernelParameters()
  for precision in AutoGemmParameters.precisions:
    kernel.precision = precision

    # valid tiles for this precision
    tiles = AutoGemmParameters.getTilesForPrecision(precision)

    # for non tile parameters
    for order in AutoGemmParameters.orders:
      kernel.order = order
      for transA in AutoGemmParameters.transposes[precision]:
        kernel.transA = transA
        for transB in AutoGemmParameters.transposes[precision]:
          kernel.transB = transB
          for beta in AutoGemmParameters.betas:
            kernel.beta = beta

            # for tile parameters
            for tile in tiles:
              # tile kernel
              kernel.useTile(tile)
              writeOpenCLKernelToFile(kernel)
              # row kernel
              rowKernel = copy.copy(kernel)
              rowKernel.macroTileNumRows = 1
              writeOpenCLKernelToFile(rowKernel)
              # col kernel
              colKernel = copy.copy(kernel)
              colKernel.macroTileNumCols = 1
              writeOpenCLKernelToFile(colKernel)
              # corner kernel
              cornerKernel = copy.copy(kernel)
              cornerKernel.macroTileNumRows = 1
              cornerKernel.macroTileNumCols = 1
              writeOpenCLKernelToFile(cornerKernel)
              numKernels += 4
  print("AutoGemm.py: generated %d kernels" % numKernels)



################################################################################
# Main
################################################################################
if __name__ == "__main__":
  ap = argparse.ArgumentParser(description="KernelOpenCL")
  ap.add_argument("precision", choices=["s","d","c","z"], help="precision" )
  ap.add_argument("order", choices=["row","col"], help="order: row major or column major" )
  ap.add_argument("transA", choices=["N","T", "C"], help="transA" )
  ap.add_argument("transB", choices=["N","T", "C"], help="transB" )
  ap.add_argument("beta", choices=[0, 1], type=int, help="0 for beta is zero, 1 for beta is non-zero" )
  ap.add_argument("workGroupNumRows", type=int )
  ap.add_argument("workGroupNumCols", type=int )
  ap.add_argument("microTileNumRows", type=int )
  ap.add_argument("microTileNumCols", type=int )
  ap.add_argument("unroll", type=int, help="number of iterations to unroll the loop over k" )
  ap.add_argument("outputPath", default=".", help="output path; %s will be appended to path" % Common.getRelativeKernelSourcePath() )

  args = ap.parse_args()

  kernel = KernelParameters.KernelParameters()
  kernel.precision = args.precision
  if args.order == "col":
    kernel.order = "clblasColumnMajor"
  else:
    kernel.order = "clblasRowMajor"
  kernel.transA = args.transA
  kernel.transB = args.transB
  kernel.beta = args.beta
  kernel.workGroupNumRows = args.workGroupNumRows
  kernel.workGroupNumCols = args.workGroupNumCols
  kernel.microTileNumRows = args.microTileNumRows
  kernel.microTileNumCols = args.microTileNumCols
  kernel.unroll = args.unroll
  Common.setOutputPath(args.outputPath)

  kernel.macroTileNumRows = kernel.workGroupNumRows * kernel.microTileNumRows
  kernel.macroTileNumCols = kernel.workGroupNumCols * kernel.microTileNumCols

  if not os.path.exists( Common.getKernelSourcePath() ):
    os.makedirs( Common.getKernelSourcePath() )

  writeOpenCLKernelToFile(kernel)

  kernelName = kernel.getName()
  kernelFileName = Common.getKernelSourcePath() + kernelName +"_src.cpp"
  print("kernel \"%s\" written to %s" % (kernelName, kernelFileName))
