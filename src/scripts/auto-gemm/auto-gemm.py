################################################################################
# Auto-Gemm
# - Automatically generate gemm kernels based on tile parameters
# - This script generates the following to ease integration into clBLAS:
#   1) generate all the kernel files
#   2) list to add to src/library/CMakeLists.txt:SRC_CL_TEMPLATES
#   3) list to add to src/library/CMakeLists.txt:SRC_CL_TEMPLATES_GEN
#   4) list to add to src/library/bingen.cmake:BIN_CL_TEMPLATES_HAWAII_CL2
#   5) list to add to src/library/blas/functor/gcn_zgemm.cc:23
# TODO
# - after writing kernel files, make list of valid micro tiles for correct size list
# - zgemm() call is in xgemm.cc
# - one functions writes every combination to a file, while one reads from that file, therefore manual intervention for deleting slow kernels
# - estimating occupancy for a kernel (low occupancy remove it?)
# - if more threads than loads put in a if statement
# - can I loop over remaining k partial block
################################################################################

import sys
import getopt



# global variables
totalParameterCombinations = 0
validParameterCombinations = 0



################################################################################
# Main
################################################################################
def main(argv):
  global totalParameterCombinations, validParameterCombinations
  processAllKernelParameterCombinations(argv)
  print "%d / %d parameter combinations valid" % (validParameterCombinations, totalParameterCombinations)



################################################################################
# Process all kernel parameter combinations
################################################################################
def processAllKernelParameterCombinations(argv):

# enumerate which kernels to generate
  precision = "d"
  listOrder = [ "clblasColumnMajor", "clblasRowMajor" ]
  listTrans = [
    [ "N", "N" ],
    [ "T", "N" ],
    [ "N", "T" ],
    [ "T", "T" ],
    ]
  listBeta = [ 0, 1 ]
  listWorkGroupDims = [ [16, 16] ]
  listMicroTileDims = [

    [4, 8], [8, 4], # 32
    [3, 8], [8, 3], # 24
    [2, 8], [8, 2], # 16
    [1, 8], [8, 1], #  8

    [5, 7], [7, 5], # 35
    [4, 7], [7, 4], # 28
    [3, 7], [7, 3], # 21
    [2, 7], [7, 2], # 14
    [1, 7], [7, 1], #  7

    [6, 6],         # 36
    [5, 6], [6, 5], # 30
    [4, 6], [6, 4], # 24
    [3, 6], [6, 3], # 18
    [2, 6], [6, 2], # 12
    [1, 6], [6, 1], #  6

    [5, 5],         # 25
    [4, 5], [5, 4], # 20
    [3, 5], [5, 3], # 15
    [2, 5], [5, 2], # 10
    [1, 5], [5, 1], #  5

    [4, 4],         # 16
    [3, 4], [4, 3], # 12
    [2, 4], [4, 2], #  8
    [1, 4], [4, 1], #  4

    [3, 3],         #  9
    [2, 3], [3, 2], #  6
    [1, 3], [3, 1], #  3

    [2, 2],         #  4
    [1, 2], [2, 1], #  2

    [1, 1],         #  1

    ]
  listMicroTileDims.sort(orderTileSizes, reverse=True)
  # make list of unique tile sizes
  listMicroTileSizes = []
  for tile in listMicroTileDims:
    size = tile[0]*tile[1]
    if size not in listMicroTileSizes:
      listMicroTileSizes.append(size)

  listUnroll = [ 8, 4, 2, 1 ]

  kernelSelectionLogic = KernelSelectionLogic(listOrder, listTrans, listBeta, listWorkGroupDims, listMicroTileDims, listUnroll, listMicroTileSizes);

  # for each kernel parameter combination
  for order in listOrder:
    kernelSelectionLogic.newOrder(order)
    for trans in listTrans:
      kernelSelectionLogic.newTrans(trans)
      for beta in listBeta:
        kernelSelectionLogic.newBeta(beta)
        for workGroupDim in listWorkGroupDims:
          for microTileDim in listMicroTileDims:
            for unroll in listUnroll:
              # set kernel parameters
              kernel = GemmTileOpenCLKernel()
              kernel.precision = precision
              kernel.order = order
              kernel.transA = trans[0]
              kernel.transB = trans[1]
              kernel.beta = beta
              kernel.wgNumRows = workGroupDim[0]
              kernel.wgNumCols = workGroupDim[1]
              kernel.microTileNumRows = microTileDim[0]
              kernel.microTileNumCols = microTileDim[1]
              kernel.unroll = unroll
              # process kernel parameters
              processKernel(kernel, kernelSelectionLogic)
  kernelSelectionLogic.finish()
  kernelSelectionLogic.writeToFile()



################################################################################
# Order Tile Sizes
# - process tiles largest -> smallest (elements/work-item)
# - for same size tile, choose squarer one
################################################################################
def orderTileSizes(tileA, tileB):
  tileASize = tileA[0] * tileA[1]
  tileBSize = tileB[0] * tileB[1]
  if (tileASize > tileBSize):
    return 1
  elif (tileBSize > tileASize):
    return -1
  else:
    if (tileB[0]+tileB[1]) > (tileA[0]+tileA[1]):
      return 1
    elif (tileA[0]+tileA[1]) > (tileB[0]+tileB[1]):
      return -1
    else:
      return 0


################################################################################
# Process kernel
################################################################################
def processKernel(kernel, kernelSelectionLogic):
  global totalParameterCombinations, validParameterCombinations

  # check if parameter combination is valid
  totalParameterCombinations += 1
  kernelName = kernel.getKernelName()
  if kernel.kernelParamsValid():
    #print "Processing: " + kernelName
    validParameterCombinations += 1
  else:
    errorString = kernel.ks
    print kernelName + " - ERROR - " + errorString
    #print "ERROR:      " + kernelName + " - skipping"
    return

  print "%s: s = %3d" % (kernelName, kernel.microTileNumRows*kernel.microTileNumCols)
  # 1) write kernel to file
  kernel.writeKernelToFile()

  # 2) list to add to src/library/CMakeLists.txt:SRC_CL_TEMPLATES
  #addToSrcClTemplates(kernel)

  # 3) list to add to src/library/CMakeLists.txt:SRC_CL_TEMPLATES_GEN
  #addToSrcClTemplatesGen
  # 4) list to add to src/library/bingen.cmake:BIN_CL_TEMPLATES_HAWAII_CL2

  # 5) list to add to src/library/blas/functor/gcn_zgemm.cc:23
  kernelSelectionLogic.newKernel(kernel)










################################################################################
#  Creates a GEMM OpenCL Kernel
################################################################################

# define gemm data types
# "s", "d", "c", "z"
hostDataChar = { "s":"s", "d":"d", "c":"c", "z":"z" }
hostDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }
openclDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }

class GemmTileOpenCLKernel:

  ##############################################################################
  #  default constructor
  ##############################################################################
  def __init__(self):
    self.precision = "s" # s, d, c, z
    self.order = "clblasColumnMajor" # column, row
    self.transA = "N" # N, T
    self.transB = "N" # N, T
    self.beta = 1
    self.wgNumRows = 16
    self.wgNumCols = 16
    self.microTileNumRows = 1
    self.microTileNumCols = 1
    self.localRowPad = 1
    self.localColPad = 1
    self.unroll = 8
    self.ks = "haven't called makeKernelString()" # kernel string


  ##############################################################################
  #  get multiples
  ##############################################################################
  def getMultipleM(self):
    return (self.wgNumRows * self.microTileNumRows)
  def getMultipleN(self):
    return (self.wgNumCols * self.microTileNumCols)
  def getMultipleK(self):
    return (self.unroll)


  ##############################################################################
  #  get kernel name
  ##############################################################################
  def getKernelName(self):
    kernelName = "%sgemm_%1s%1s_%03d_%03d_%01d_%02dx%02d_%01dx%01d" % (hostDataChar[self.precision], self.transA, self.transB, (self.wgNumCols * self.microTileNumCols), (self.wgNumRows * self.microTileNumRows), self.unroll, self.wgNumRows, self.wgNumCols, self.microTileNumRows, self.microTileNumCols)
    if (self.beta==1):
      kernelName += "__BETA"
    return kernelName


  ##############################################################################
  #  are kernel parameters valid?
  ##############################################################################
  def kernelParamsValid(self):
    numALoadsR = (self.wgNumRows*self.microTileNumRows*self.unroll)%(self.wgNumRows*self.wgNumCols)
    numBLoadsR = (self.wgNumCols*self.microTileNumCols*self.unroll)%(self.wgNumRows*self.wgNumCols)
    if (numALoadsR):
      self.ks = "(%2d * %d * %d = %3d) A elements can't be loaded by (%2d * %2d = %3d) threads" % (self.wgNumRows,self.microTileNumRows,self.unroll,(self.wgNumRows*self.microTileNumRows*self.unroll),self.wgNumRows,self.wgNumCols,(self.wgNumRows*self.wgNumCols))
      return False
    elif (numBLoadsR):
      self.ks = "(%2d * %d * %d = %3d) B elements can't be loaded by (%2d * %2d = %3d) threads" % (self.wgNumCols,self.microTileNumCols,self.unroll,(self.wgNumCols*self.microTileNumCols*self.unroll),self.wgNumRows,self.wgNumCols,(self.wgNumRows*self.wgNumCols))
      return False
    else:
      return True


  ##############################################################################
  #  make gemm kernel based on parameters
  ##############################################################################
  def makeKernelString(self):

    ####################################
    # parameters valid?
    numALoadsR = (self.wgNumRows*self.microTileNumRows*self.unroll)%(self.wgNumRows*self.wgNumCols)
    numBLoadsR = (self.wgNumCols*self.microTileNumCols*self.unroll)%(self.wgNumRows*self.wgNumCols)
    if (numALoadsR or numALoadsR) > 0:
      self.ks = "NULL: mismatch between tile dimentions and unroll; cannot do simple global->local load"
      return self.ks

    ####################################
    # initializations
    self.ks = "" # kernel string

    ####################################
    # kernel parameters
    self.ks += "\n// kernel parameters\n"
    self.ks += "#define ORDER                %s\n" % self.order
    self.ks += "#define TRANSPOSE_A          %s\n" % self.transA
    self.ks += "#define TRANSPOSE_B          %s\n" % self.transB
    self.ks += "\n"
    self.ks += "#define WG_NUM_ROWS          %d\n" % self.wgNumRows
    self.ks += "#define WG_NUM_COLS          %d\n" % self.wgNumCols
    self.ks += "#define MICRO_TILE_NUM_ROWS  %d\n" % self.microTileNumRows
    self.ks += "#define MICRO_TILE_NUM_COLS  %d\n" % self.microTileNumCols
    self.ks += "#define MACRO_TILE_NUM_ROWS  %s\n" % (self.wgNumRows * self.microTileNumRows)
    self.ks += "#define MACRO_TILE_NUM_COLS  %s\n" % (self.wgNumCols * self.microTileNumCols)
    self.ks += "\n"
    self.ks += "#define LOCAL_ROW_PAD        %s\n" % self.localRowPad
    self.ks += "#define LOCAL_COL_PAD        %s\n" % self.localColPad

    ####################################
    # global memory indices
    # A
    self.ks += "\n// global memory indices\n"
    if (self.order=="clblasColumnMajor")==(self.transA==0):
      self.ks += "#define GET_GLOBAL_INDEX_A(ROW,COL) ((COL)*lda+(ROW))\n"
    else:
      self.ks += "#define GET_GLOBAL_INDEX_A(ROW,COL) ((ROW)*lda+(COL))\n"
    # B
    if (self.order=="clblasColumnMajor")==(self.transB==0):
      self.ks += "#define GET_GLOBAL_INDEX_B(ROW,COL) ((ROW)*ldb+(COL))\n"
    else:
      self.ks += "#define GET_GLOBAL_INDEX_B(ROW,COL) ((COL)*ldb+(ROW))\n"
    # C
    if (self.order=="clblasColumnMajor"):
      self.ks += "#define GET_GLOBAL_INDEX_C(ROW,COL) ((COL)*ldc+(ROW))\n"
    else:
      self.ks += "#define GET_GLOBAL_INDEX_C(ROW,COL) ((ROW)*ldc+(COL))\n"

    ####################################
    # local memory indices
    # A
    self.ks += "\n// local memory indices\n"
    self.ks += "#define GET_LOCAL_INDEX_A(ROW,COL) (ROW + COL*(MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD) )\n"
    self.ks += "#define GET_LOCAL_STEP_A ( ((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) * ((WG_NUM_ROWS)*(WG_NUM_COLS)/(MACRO_TILE_NUM_COLS))\n"
    # B
    self.ks += "#define GET_LOCAL_INDEX_B(ROW,COL)   ((COL) + (ROW)*((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) )\n"
    self.ks += "#define GET_LOCAL_STEP_B ( ((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) * ((WG_NUM_ROWS)*(WG_NUM_COLS)/(MACRO_TILE_NUM_COLS))\n"

    ####################################
    # data types
    self.ks += "\n// data types\n"
    self.ks += "#define DATA_TYPE_STR %s\n" % openclDataType[self.precision]
    if self.precision==("s" or "d"):
      # real arithmetic
      self.ks += "#define TYPE_MAD(MUL0,MUL1,DST) DST = mad(MUL0,MUL1,DST);\n"
      self.ks += "#define TYPE_MAD_WRITE(DST,ALPHA,REG,BETA) DST = (ALPHA)*(REG) + (BETA)*(DST);\n"
    else:
      # complex arithmetic
      self.ks += (
        "#define TYPE_MAD(MUL0,MUL1,DST) \\\n"
        "  DST.s0 = mad(  MUL0.s0, MUL1.s0, DST.s0 ); \\\n"
        "  DST.s0 = mad( -MUL0.s1, MUL1.s1, DST.s0 ); \\\n"
        "  DST.s1 = mad(  MUL0.s0, MUL1.s1, DST.s1 ); \\\n"
        "  DST.s1 = mad(  MUL0.s1, MUL1.s0, DST.s1 );\n" )
      self.ks += (
        "#define TYPE_MAD_WRITE( DST, ALPHA, REG, BETA ) \\\n"
        "  /* (1) */ \\\n"
        "  type_mad2_tmp = REG.s0; \\\n"
        "  REG.s0 *= ALPHA.s0; \\\n"
        "  REG.s0 = mad( -ALPHA.s1, REG.s1, REG.s0 ); \\\n"
        "  REG.s1 *= ALPHA.s0; \\\n"
        "  REG.s1 = mad(  ALPHA.s1, type_mad2_tmp, REG.s1 ); \\\n"
        "  /* (2) */ \\\n"
        "  REG.s0 = mad(  BETA.s0, DST.s0, REG.s0 ); \\\n"
        "  REG.s0 = mad( -BETA.s1, DST.s1, REG.s0 ); \\\n"
        "  REG.s1 = mad(  BETA.s1, DST.s0, REG.s1 ); \\\n"
        "  REG.s1 = mad(  BETA.s0, DST.s1, REG.s1 ); \\\n"
        "  /* (3) */ \\\n"
        "  DST = REG;\n" )

    ####################################
    # micro-tile
    self.ks += "\n// %dx%d micro-tile\n" % (self.microTileNumRows, self.microTileNumCols)
    self.ks += "#define MICRO_TILE \\\n"
    for a in range(0, self.microTileNumRows):
      self.ks += "  rA[%d] = localA[offA + %d*WG_NUM_ROWS]; \\\n" % (a, a)
    for b in range(0, self.microTileNumCols):
      self.ks += "  rB[%d] = localB[offB + %d*WG_NUM_COLS]; \\\n" % (b, b)
    self.ks += "  offA += (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD; \\\n"
    self.ks += "  offB += (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD; \\\n"
    for a in range(0, self.microTileNumRows):
      for b in range(0, self.microTileNumCols):
        self.ks += "  TYPE_MAD(rA[%d],rB[%d],rC[%d][%d]); \\\n" % (a, b, a, b)
    self.ks += "  mem_fence(CLK_LOCAL_MEM_FENCE);\n\n"

    ####################################
    # function signature
    ####################################
    self.ks += "__attribute__((reqd_work_group_size(WG_NUM_COLS,WG_NUM_ROWS,1)))\n"
    self.ks += "__kernel void %s" % ( self.getKernelName() )
    self.ks += "(\n"
    # arguments
    self.ks += (
      "  uint const M,\n"
      "  uint const N,\n"
      "  uint const K,\n"
      "  DATA_TYPE_STR const alpha,\n"
      "  DATA_TYPE_STR const beta,\n"
      "  __global DATA_TYPE_STR const * restrict A,\n"
      "  __global DATA_TYPE_STR const * restrict B,\n"
      "  __global DATA_TYPE_STR       *          C,\n"
      "  uint const lda,\n"
      "  uint const ldb,\n"
      "  uint const ldc,\n"
      "  uint const offsetA,\n"
      "  uint const offsetB,\n"
      "  uint const offsetC\n"
      ") {\n" )

    ####################################
    # apply offsets
    self.ks += (
      "\n  // apply offsets\n"
      "  A += offsetA;\n"
      "  B += offsetB;\n"
      "  C += offsetC;\n" )

    ####################################
    # allocate registers
    self.ks += (
      "\n  // allocate registers\n"
      "  DATA_TYPE_STR rC[MICRO_TILE_NUM_ROWS][MICRO_TILE_NUM_COLS] = {0};\n"
      "  DATA_TYPE_STR rA[MICRO_TILE_NUM_ROWS];\n"
      "  DATA_TYPE_STR rB[MICRO_TILE_NUM_COLS];\n" )

    ####################################
    # allocate local memory
    self.ks += (
      "\n  // allocate local memory\n"
      "  __local DATA_TYPE_STR localA[NUM_UNROLL_ITER*(MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD)];\n"
      "  __local DATA_TYPE_STR localB[NUM_UNROLL_ITER*(MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD)];\n" )

    ####################################
    # work item indices
    self.ks += (
      "\n  // work item indices\n"
      "  uint groupRow = get_group_id(0);\n"
      "  uint groupCol = get_group_id(1);\n"
      "  uint localRow = get_local_id(0);\n"
      "  uint localCol = get_local_id(1);\n"
      "  uint localSerial = localRow + localCol*WG_NUM_ROWS;\n" )

    ####################################
    # global indices being loaded
    self.ks += (
      "\n  // global indices begin loaded\n"
      "#define globalARow (groupRow*MACRO_TILE_NUM_ROWS + localSerial%MACRO_TILE_NUM_ROWS)\n"
      "#define globalACol (localSerial/MACRO_TILE_NUM_ROWS)\n"
      "#define globalAIdx (GET_GLOBAL_INDEX_A( globalARow, globalACol ) )\n"
      "  A += globalAIdx;\n"
      "  // which gBij is this thread responsible for loading?\n"
      "#define globalBRow (localSerial/MACRO_TILE_NUM_COLS)\n"
      "#define globalBCol (groupCol*MACRO_TILE_NUM_COLS + localSerial%MACRO_TILE_NUM_COLS)\n"
      "#define globalBIdx (GET_GLOBAL_INDEX_B( globalBRow, globalBCol ) )\n"
      "  B += globalBIdx;\n" )

    ####################################
    # loop over k
    self.ks += (
      "\n  // loop over k\n"
      "  uint block_k = K / NUM_UNROLL_ITER;\n"
      "  do {\n" )

    ####################################
    # local indices begin written
    self.ks += (
      "\n    // local indices begin written\n"
      "    // which lAij is this thread responsible for writing?\n"
      "#define localARow (localSerial % MACRO_TILE_NUM_ROWS)\n"
      "#define localACol (localSerial / MACRO_TILE_NUM_ROWS)\n"
      "#define localAStride ( (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD) * (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_ROWS) )\n"
      "#define globalAStride ( GET_GLOBAL_INDEX_A(0, (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_ROWS) ) )\n"
      "#define localAIdx ( GET_LOCAL_INDEX_A(localARow, localACol) )\n"
      "      __local DATA_TYPE_STR *lA = localA + localAIdx;\n"
      "      // which lBij is this thread responsible for writing?\n"
      "#define localBRow ( localSerial / MACRO_TILE_NUM_COLS )\n"
      "#define localBCol ( localSerial % MACRO_TILE_NUM_COLS )\n"
      "#define localBIdx ( GET_LOCAL_INDEX_B(localBRow, localBCol) )\n"
      "#define localBStride  ( (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD) * (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_COLS) )\n"
      "#define globalBStride ( GET_GLOBAL_INDEX_B( (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_COLS), 0 ) )\n"
      "      __local DATA_TYPE_STR *lB = localB + localBIdx;\n"
      "      barrier(CLK_LOCAL_MEM_FENCE);\n" )

    ####################################
    # load global -> local
    # threads to do loading = (wgNumRows*wgNumCols)
    # A elements to be loaded = wgNumRows*microTileNumRows*unroll
    # B elements to be loaded = wgNumCols*microTileNumCols*unroll
    self.ks += "\n    // load global -> local\n"
    numALoads  = (self.wgNumRows*self.microTileNumRows*self.unroll)/(self.wgNumRows*self.wgNumCols)
    numBLoads  = (self.wgNumCols*self.microTileNumCols*self.unroll)/(self.wgNumRows*self.wgNumCols)
    for a in range(0, numALoads):
      self.ks += "    lA[ %d*localAStride ] = A[ %d*globalAStride ];\n" % (a, a)
    for b in range(0, numBLoads):
      self.ks += "    lB[ %d*localBStride ] = B[ %d*globalBStride ];\n" % (b, b)
    self.ks += (
      "    barrier(CLK_LOCAL_MEM_FENCE);\n\n"
      "    uint offA = localRow;\n"
      "    uint offB = localCol;\n" )

    ####################################
    # do mads
    self.ks += "\n    // do mads\n"
    for u in range(0, self.unroll):
      self.ks += "    MICRO_TILE\n"

    ####################################
    # shift to next k block
    self.ks += "\n    // shift to next k block\n"
    if self.transA=="N":
      self.ks += "    A += lda*NUM_UNROLL_ITER; // transA==N\n"
    else:
      self.ks += "    A += NUM_UNROLL_ITER; // transA==T\n"
    if self.transB=="N":
      self.ks += "    B += NUM_UNROLL_ITER; // transB==N\n"
    else:
      self.ks += "    B += ldb*NUM_UNROLL_ITER; // transB==T\n"

    ####################################
    # end loop
    self.ks += "\n  } while (--block_k > 0);\n\n"

    ####################################
    # which global Cij index
    self.ks += "\n  // which global Cij index\n"
    self.ks += "  uint globalCRow = groupRow * MACRO_TILE_NUM_ROWS + localRow;\n"
    self.ks += "  uint globalCCol = groupCol * MACRO_TILE_NUM_COLS + localCol;\n"

    ####################################
    # write global Cij
    self.ks += "\n  // write global Cij\n"
    for a in range(0, self.microTileNumRows):
      for b in range(0, self.microTileNumCols):
        self.ks += "  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+%d*WG_NUM_ROWS, globalCCol+%d*WG_NUM_COLS) ], alpha, rC[%d][%d], beta )\n" % (a, b, a, b)

    ####################################
    # end kernel
    self.ks += "\n\n}\n"

    return self.ks


  ##############################################################################
  # Write kernel to file
  ##############################################################################
  def writeKernelToFile(self):
    kernelName = self.getKernelName()
    kernelString = self.makeKernelString()
    kernelFileName = kernelName+".cl"
    kernelFile = open(kernelFileName, "w")
    kernelFile.write("static const char * %s = \"\n\n" % kernelName)
    kernelFile.write(kernelString)
    kernelFile.write("\";\n")
    kernelFile.close()





################################################################################
# Kernel Selection Logic
################################################################################
class KernelSelectionLogic:

  zeroIndent = "  "
  tab = "  "
  ##############################################################################
  # default constructor
  ##############################################################################
  def __init__(self, \
      listOrder, \
      listTrans, \
      listBeta, \
      listWorkGroupDims, \
      listMicroTileDims, \
      listUnroll, \
      listMicroTileSizes ):

    self.listMicroTileSizes = listMicroTileSizes

    self.logic = "xgemmSelectKernel( " # logic string
    self.orderInitialized = False
    self.transInitialized = False
    self.betaInitialized = False
    self.previousTileSize = 0


  ####################################
  # new order
  def newOrder(self, order):
    if (self.orderInitialized):
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab + "}\n" # 3 tabs
      self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
      self.logic += self.zeroIndent+self.tab + "}\n" # 1 tab
      self.logic += self.zeroIndent
      self.logic += "} else "
    else:
      self.logic += self.zeroIndent
    self.logic += "if (order == " + order + ") {\n"
    self.orderInitialized = True
    self.transInitialized = False
    self.betaInitialized = False
    self.previousTileSize = 0


  ####################################
  # new trans
  def newTrans(self, trans):
    if (self.transInitialized):
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab + "}\n" # 3 tabs
      self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
      self.logic += self.zeroIndent+self.tab # 1 tab
      self.logic += "} else "
    else:
      self.logic += self.zeroIndent+self.tab # 1 tabs
    self.logic += "if (transA == "
    if trans[0] == "N":
      self.logic += "clblasNoTrans"
    else:
      self.logic += "clblasTrans"
    self.logic += " && transB == "
    if trans[1] == "N":
      self.logic += "clblasNoTrans"
    else:
      self.logic += "clblasTrans"
    self.logic += ") {\n"
    self.transInitialized = True
    self.betaInitialized = False
    self.previousTileSize = 0

  ####################################
  # new beta
  def newBeta(self, beta):
    if (self.betaInitialized):
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab + "}\n" # 3 tabs
      self.logic += self.zeroIndent+self.tab+self.tab # 2 tabs
      self.logic += "} else "
    else:
      self.logic += self.zeroIndent+self.tab+self.tab # 2 tabs
    self.logic += "if ( "
    if beta == 0:
      self.logic += "BETA_IS_ZERO(beta)"
    else:
      self.logic += "BETA_IS_NONZERO(beta)"
    self.logic += " ) {\n"
    self.betaInitialized = True
    self.previousTileSize = 0


  ##############################################################################
  # add new kernel
  ##############################################################################
  def newKernel(self, kernel):

    # first tile size for beta?
    if self.previousTileSize == 0:
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab # 3 tabs
      self.logic += "if (optimalNumElementsPerWorkItem > " + str(self.listMicroTileSizes[0]) + ") {\n"
      self.previousTileSize = self.listMicroTileSizes[0]
      self.kernelInitialized = False

    # new tile size?
    tileSize = kernel.microTileNumRows * kernel.microTileNumCols
    tileSizeIndex = self.listMicroTileSizes.index(tileSize)
    if tileSize != self.previousTileSize:
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab # 3 tabs
      self.logic += "}\n"
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab # 3 tabs
      self.logic += "if (optimalNumElementsPerWorkItem > " + str(self.listMicroTileSizes[tileSizeIndex+1]) + ") {\n"
      self.kernelInitialized = False
      self.previousTileSize = tileSize

    # new kernel
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "if ( M%%%d == 0 && N%%%d == 0 && K%%%d == 0) {\n" % (kernel.getMultipleM(), kernel.getMultipleN(), kernel.getMultipleK())
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "selectedKernel = " + kernel.getKernelName() + ";\n"
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "return;\n"
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "}\n"


  ####################################
  # finish (close braces)
  def finish(self):
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab + "}\n" # 3 tabs
    self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
    self.logic += self.zeroIndent+self.tab + "}\n" # 1 tab
    self.logic += self.zeroIndent + "}\n" # 0 tab


  ##############################################################################
  # write to file
  ##############################################################################
  def writeToFile(self):
    selectionFileName = "kernelSelectionLogic.h"
    selectionFile = open(selectionFileName, "w")
    selectionFile.write("// kernel selection logic\n")
    selectionFile.write(self.logic)
    selectionFile.write("\n")
    selectionFile.close()






################################################################################
# Call Main
################################################################################
if __name__ == "__main__":
  main(sys.argv[1:])
