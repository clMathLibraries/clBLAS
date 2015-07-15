################################################################################
# Auto-Gemm
# - Automatically generate gemm kernels based on tile parameters
# - This script generates the following to ease integration into clBLAS:
#   1) generate all the kernel files
#   2) list to add to src/library/CMakeLists.txt:SRC_CL_TEMPLATES
#   3) list to add to src/library/CMakeLists.txt:SRC_CL_TEMPLATES_GEN
#   4) list to add to src/library/bingen.cmake:BIN_CL_TEMPLATES_HAWAII_CL2
#   5) list to add to src/library/blas/functor/gcn_zgemm.cc:23 - DONE
# TODO
# - after writing kernel files, make list of valid micro tiles for correct size list
# - zgemm() call is in xgemm.cc
# - one functions writes every combination to a file, while one reads from that file, therefore manual intervention for deleting slow kernels
# - estimating occupancy for a kernel (low occupancy remove it?)
# - optimize for beta = 0
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
# Main - Process all kernel parameter combinations
################################################################################
def processAllKernelParameterCombinations(argv):

# enumerate which kernels to generate
  precision = "s"
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

  kernelSelectionLogic = KernelSelectionLogic(precision, listOrder, listTrans, listBeta, listWorkGroupDims, listMicroTileDims, listUnroll, listMicroTileSizes);
  kernelIncludes = KernelIncludes(precision)

  # files to write lists to
  fileSrcClTemplates = open(precision + "gemm_SRC_CL_TEMPLATES.txt", "w")
  fileSrcClTemplatesGen = open(precision + "gemm_SRC_CL_TEMPLATES_GEN.txt", "w")
  fileBinClTemplates = open(precision + "gemm_BIN_CL_TEMPLATES.txt", "w")
  fileCppKernelParameters = open(precision + "gemm_cppKernelParameters.h", "w")


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
              processKernel( \
                  kernel, \
                  kernelSelectionLogic, \
                  fileSrcClTemplates, \
                  fileSrcClTemplatesGen, \
                  fileBinClTemplates, \
                  kernelIncludes, \
                  fileCppKernelParameters )
  # save written files
  kernelSelectionLogic.finish()
  kernelSelectionLogic.writeToFile()
  fileSrcClTemplates.close()
  fileSrcClTemplatesGen.close()
  fileBinClTemplates.close()
  kernelIncludes.writeToFile()
  fileCppKernelParameters.close()



################################################################################
# Main - Order Tile Sizes
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
# Main - Process kernel
################################################################################
def processKernel( \
    kernel, \
    kernelSelectionLogic, \
    fileSrcClTemplates, \
    fileSrcClTemplatesGen, \
    fileBinClTemplates, \
    kernelIncludes, \
    fileCppKernelParameters ):
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
  fileSrcClTemplates.write("  %s.cl\n" % kernelName)

  # 3) list to add to src/library/CMakeLists.txt:SRC_CL_TEMPLATES_GEN
  fileSrcClTemplatesGen.write("  %s.clHawaii_64.bin.cl\n" % kernelName)

  # 4) list to add to src/library/bingen.cmake:BIN_CL_TEMPLATES_HAWAII_CL2
  fileBinClTemplates.write("  ${CLTEMPLATE_PATH}%s.cl\n" % kernelName)

  # 5) list to add to src/library/blas/functor/gcn_zgemm.cc:23
  kernelSelectionLogic.newKernel(kernel)
  kernelIncludes.addKernel(kernel)

  # 5) list to add to ktest for automated kernel testing
  fileCppKernelParameters.write("  { %u, %u, %u, %u, %u, %u, %u, %u, %u },\n" % ( \
      1 if kernel.order=="clblasColumnMajor" else 0, \
      1 if kernel.transA=="T" else 0, \
      1 if kernel.transB=="T" else 0, \
      1 if kernel.beta>0 else 0, \
      kernel.microTileNumRows, \
      kernel.microTileNumCols, \
      kernel.wgNumRows, \
      kernel.wgNumCols, \
      kernel.unroll ) )


"""  fileCppKernelParameters.write("  { ")
  if kernel.order=="clblasColumnMajor":
    fileCppKernelParameters.write("1, ")
  else:
    fileCppKernelParameters.write("0, ")

  if kernel.transA=="T":
    fileCppKernelParameters.write("1, ")
  else:
    fileCppKernelParameters.write("0, ")

  if kernel.transB=="T":
    fileCppKernelParameters.write("1, ")
  else:
    fileCppKernelParameters.write("0, ")

  if kernel.beta > 0:
    fileCppKernelParameters.write("1, ")
  else:
    fileCppKernelParameters.write("0, ")

  fileCppKernelParameters.write("%d, %d, %d, %d, %d }" % (kernel.microTileNumRows, kernel.microTileNumCols, kernel.wgNumRows, kernel.wgNumCols, kernel.unroll ) )
"""







################################################################################
# Kernel - Creates a GEMM OpenCL Kernel
################################################################################

# define gemm data types
# "s", "d", "c", "z"
hostDataChar = { "s":"s", "d":"d", "c":"c", "z":"z" }
hostDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }
openclDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }

class GemmTileOpenCLKernel:

  ##############################################################################
  # Kernel - default constructor
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
    self.localRowPad = 0
    self.localColPad = 0
    self.unroll = 8
    self.ks = "haven't called makeKernelString()" # kernel string
    self.el = "\\n\"\n\""


  ##############################################################################
  # Kernel - get multiples
  ##############################################################################
  def getMultipleM(self):
    return (self.wgNumRows * self.microTileNumRows)
  def getMultipleN(self):
    return (self.wgNumCols * self.microTileNumCols)
  def getMultipleK(self):
    return (self.unroll)


  ##############################################################################
  # Kernel - get kernel name
  ##############################################################################
  def getKernelName(self):
    kernelName = "%sgemm_%1s%1s_%03d_%03d_%01d_%02dx%02d_%01dx%01d" % (hostDataChar[self.precision], self.transA, self.transB, (self.wgNumRows * self.microTileNumRows), (self.wgNumCols * self.microTileNumCols), self.unroll, self.wgNumRows, self.wgNumCols, self.microTileNumRows, self.microTileNumCols)
    if (self.order=="clblasColumnMajor"):
      kernelName += "_ColMajor"
    else:
      kernelName += "_RowMajor"
    if (self.beta==1):
      kernelName += "_BETA"
    return kernelName


  ##############################################################################
  # Kernel - are kernel parameters valid?
  ##############################################################################
  def kernelParamsValid(self):
    numALoads = (self.wgNumRows*self.microTileNumRows*self.unroll)/(self.wgNumRows*self.wgNumCols)
    numALoadsR = (self.wgNumRows*self.microTileNumRows*self.unroll)%(self.wgNumRows*self.wgNumCols)
    numBLoads = (self.wgNumCols*self.microTileNumCols*self.unroll)/(self.wgNumRows*self.wgNumCols)
    numBLoadsR = (self.wgNumCols*self.microTileNumCols*self.unroll)%(self.wgNumRows*self.wgNumCols)
    if (numALoads>0 and numALoadsR>0):
      self.ks = "(%2d * %d * %d = %3d) A elements can't be loaded by (%2d * %2d = %3d) threads" % (self.wgNumRows,self.microTileNumRows,self.unroll,(self.wgNumRows*self.microTileNumRows*self.unroll),self.wgNumRows,self.wgNumCols,(self.wgNumRows*self.wgNumCols))
      return False
    elif (numBLoads>0 and numBLoadsR>0):
      self.ks = "(%2d * %d * %d = %3d) B elements can't be loaded by (%2d * %2d = %3d) threads" % (self.wgNumCols,self.microTileNumCols,self.unroll,(self.wgNumCols*self.microTileNumCols*self.unroll),self.wgNumRows,self.wgNumCols,(self.wgNumRows*self.wgNumCols))
      return False
    else:
      return True


  ##############################################################################
  # Kernel - make gemm kernel based on parameters
  ##############################################################################
  def makeKernelString(self):

    ####################################
    # parameters valid?
    if self.kernelParamsValid() == False:
      return self.ks

    ####################################
    # initializations
    self.ks = ""
    self.ks += self.el
    self.ks += "/* %s */" % self.getKernelName()
    self.ks += self.el

    ####################################
    # kernel parameters
    self.ks += self.el
    self.ks += "/* kernel parameters */" + self.el
    if self.order == "clblasColumnMajor":
      self.ks += "#define COLUMN_MAJOR          1" + self.el
    else:
      self.ks += "#define COLUMN_MAJOR          0" + self.el
    if self.transA == "T":
      self.ks += "#define TRANSPOSE_A           1" + self.el
    else:
      self.ks += "#define TRANSPOSE_A           0" + self.el
    if self.transB == "T":
      self.ks += "#define TRANSPOSE_B           1" + self.el
    else:
      self.ks += "#define TRANSPOSE_B           0" + self.el
    self.ks += "" + self.el
    self.ks += "#define WG_NUM_ROWS          %d%s" % (self.wgNumRows, self.el )
    self.ks += "#define WG_NUM_COLS          %d%s" % (self.wgNumCols, self.el )
    self.ks += "#define MICRO_TILE_NUM_ROWS  %d%s" % (self.microTileNumRows, self.el )
    self.ks += "#define MICRO_TILE_NUM_COLS  %d%s" % (self.microTileNumCols, self.el )
    self.ks += "#define MACRO_TILE_NUM_ROWS  %s%s" % ((self.wgNumRows * self.microTileNumRows), self.el )
    self.ks += "#define MACRO_TILE_NUM_COLS  %s%s" % ((self.wgNumCols * self.microTileNumCols), self.el )
    self.ks += "#define NUM_UNROLL_ITER      %s%s" % (self.unroll, self.el )
    self.ks += "" + self.el
    self.ks += "#define LOCAL_ROW_PAD        %s%s" % (self.localRowPad, self.el)
    self.ks += "#define LOCAL_COL_PAD        %s%s" % (self.localColPad, self.el)

    ####################################
    # global memory indices
    # A
    self.ks += self.el
    self.ks += "/* global memory indices */" + self.el
    if (self.order=="clblasColumnMajor")==(self.transA=="T"):
      self.ks += "#define GET_GLOBAL_INDEX_A(ROW,COL) ((ROW)*lda+(COL))" + self.el
    else:
      self.ks += "#define GET_GLOBAL_INDEX_A(ROW,COL) ((COL)*lda+(ROW))" + self.el
    # B
    if (self.order=="clblasColumnMajor")==(self.transB=="T"):
      self.ks += "#define GET_GLOBAL_INDEX_B(ROW,COL) ((ROW)*ldb+(COL))" + self.el
    else:
      self.ks += "#define GET_GLOBAL_INDEX_B(ROW,COL) ((COL)*ldb+(ROW))" + self.el
    # C
    if (self.order=="clblasColumnMajor"):
      self.ks += "#define GET_GLOBAL_INDEX_C(ROW,COL) ((COL)*ldc+(ROW))" + self.el
    else:
      self.ks += "#define GET_GLOBAL_INDEX_C(ROW,COL) ((ROW)*ldc+(COL))" + self.el

    ####################################
    # local memory indices
    # A
    self.ks += self.el
    self.ks += "/* local memory indices */" + self.el
    self.ks += "#define GET_LOCAL_INDEX_A(ROW,COL) ((ROW) + (COL)*((MACRO_TILE_NUM_ROWS)+(LOCAL_COL_PAD)) )" + self.el
    # B
    self.ks += "#define GET_LOCAL_INDEX_B(ROW,COL) ((COL) + (ROW)*((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) )" + self.el

    ####################################
    # data types
    self.ks += self.el
    self.ks += "/* data types */" + self.el
    self.ks += "#define DATA_TYPE_STR %s%s" % (openclDataType[self.precision], self.el)
    if self.precision=="s" or self.precision=="d":
      # real arithmetic
      self.ks += "#define TYPE_MAD(MUL0,MUL1,DST) DST = mad(MUL0,MUL1,DST);" + self.el
      if self.beta==1:
        self.ks += "#define TYPE_MAD_WRITE(DST,ALPHA,REG,BETA) DST = (ALPHA)*(REG) + (BETA)*(DST);" + self.el
      else:
        self.ks += "#define TYPE_MAD_WRITE(DST,ALPHA,REG,BETA) DST = (ALPHA)*(REG);" + self.el

    else:
      # complex arithmetic
      self.ks += (
        "#define TYPE_MAD(MUL0,MUL1,DST) \\\\" + self.el +
        "  DST.s0 = mad(  MUL0.s0, MUL1.s0, DST.s0 ); \\\\" + self.el +
        "  DST.s0 = mad( -MUL0.s1, MUL1.s1, DST.s0 ); \\\\" + self.el +
        "  DST.s1 = mad(  MUL0.s0, MUL1.s1, DST.s1 ); \\\\" + self.el +
        "  DST.s1 = mad(  MUL0.s1, MUL1.s0, DST.s1 );" + self.el )
      if self.beta==1:
        self.ks += (
          "#define TYPE_MAD_WRITE( DST, ALPHA, REG, BETA ) \\\\" + self.el +
          "  /* (1) */ \\\\" + self.el +
          "  type_mad_tmp = REG.s0; \\\\" + self.el +
          "  REG.s0 *= ALPHA.s0; \\\\" + self.el +
          "  REG.s0 = mad( -ALPHA.s1, REG.s1, REG.s0 ); \\\\" + self.el +
          "  REG.s1 *= ALPHA.s0; \\\\" + self.el +
          "  REG.s1 = mad(  ALPHA.s1, type_mad_tmp, REG.s1 ); \\\\" + self.el +
          "  /* (2) */ \\\\" + self.el +
          "  REG.s0 = mad(  BETA.s0, DST.s0, REG.s0 ); \\\\" + self.el +
          "  REG.s0 = mad( -BETA.s1, DST.s1, REG.s0 ); \\\\" + self.el +
          "  REG.s1 = mad(  BETA.s1, DST.s0, REG.s1 ); \\\\" + self.el +
          "  REG.s1 = mad(  BETA.s0, DST.s1, REG.s1 ); \\\\" + self.el +
          "  /* (3) */ \\\\" + self.el +
          "  DST = REG;" + self.el )
      else:
        self.ks += (
          "#define TYPE_MAD_WRITE( DST, ALPHA, REG, BETA ) \\\\" + self.el +
          "  /* (1) */ \\\\" + self.el +
          "  type_mad_tmp = REG.s0; \\\\" + self.el +
          "  REG.s0 *= ALPHA.s0; \\\\" + self.el +
          "  REG.s0 = mad( -ALPHA.s1, REG.s1, REG.s0 ); \\\\" + self.el +
          "  REG.s1 *= ALPHA.s0; \\\\" + self.el +
          "  REG.s1 = mad(  ALPHA.s1, type_mad_tmp, REG.s1 ); \\\\" + self.el +
          #"  /* (2) */ \\\\" + self.el +
          #"  REG.s0 = mad(  BETA.s0, DST.s0, REG.s0 ); \\\\" + self.el +
          #"  REG.s0 = mad( -BETA.s1, DST.s1, REG.s0 ); \\\\" + self.el +
          #"  REG.s1 = mad(  BETA.s1, DST.s0, REG.s1 ); \\\\" + self.el +
          #"  REG.s1 = mad(  BETA.s0, DST.s1, REG.s1 ); \\\\" + self.el +
          "  /* (3) */ \\\\" + self.el +
          "  DST = REG;" + self.el )

    ####################################
    # micro-tile
    self.ks += self.el
    self.ks += "/* %dx%d micro-tile */%s" % (self.microTileNumRows, self.microTileNumCols, self.el)
    self.ks += "#define MICRO_TILE \\\\" + self.el
    for a in range(0, self.microTileNumRows):
      self.ks += "  rA[%d] = localA[offA + %d*WG_NUM_ROWS]; \\\\%s" % (a, a, self.el)
    for b in range(0, self.microTileNumCols):
      self.ks += "  rB[%d] = localB[offB + %d*WG_NUM_COLS]; \\\\%s" % (b, b, self.el)
    self.ks += "  offA += (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD); \\\\" + self.el
    self.ks += "  offB += (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD); \\\\" + self.el
    for a in range(0, self.microTileNumRows):
      for b in range(0, self.microTileNumCols):
        self.ks += "  TYPE_MAD(rA[%d],rB[%d],rC[%d][%d]); \\\\%s" % (a, b, a, b, self.el)
    self.ks += "  mem_fence(CLK_LOCAL_MEM_FENCE);" + self.el
    self.ks += self.el

    ####################################
    # function signature
    ####################################
    self.ks += "__attribute__((reqd_work_group_size(WG_NUM_COLS,WG_NUM_ROWS,1)))" + self.el
    self.ks += "__kernel void %s" % ( self.getKernelName() )
    self.ks += "(" + self.el
    # arguments
    self.ks += (
      "  uint const M," + self.el +
      "  uint const N," + self.el +
      "  uint const K," + self.el +
      "  DATA_TYPE_STR const alpha," + self.el +
      "  DATA_TYPE_STR const beta," + self.el +
      "  __global DATA_TYPE_STR const * restrict A," + self.el +
      "  __global DATA_TYPE_STR const * restrict B," + self.el +
      "  __global DATA_TYPE_STR       *          C," + self.el +
      "  uint const lda," + self.el +
      "  uint const ldb," + self.el +
      "  uint const ldc," + self.el +
      "  uint const offsetA," + self.el +
      "  uint const offsetB," + self.el +
      "  uint const offsetC" + self.el +
      ") {" + self.el )

    ####################################
    # apply offsets
    self.ks += self.el
    self.ks += (
      "  /* apply offsets */" + self.el +
      "  A += offsetA;" + self.el +
      "  B += offsetB;" + self.el +
      "  C += offsetC;" + self.el )

    ####################################
    # allocate registers
    self.ks += self.el
    self.ks += (
      "  /* allocate registers */" + self.el +
      "  DATA_TYPE_STR rC[MICRO_TILE_NUM_ROWS][MICRO_TILE_NUM_COLS] = {0};" + self.el +
      "  DATA_TYPE_STR rA[MICRO_TILE_NUM_ROWS];" + self.el +
      "  DATA_TYPE_STR rB[MICRO_TILE_NUM_COLS];" + self.el )

    ####################################
    # allocate local memory
    self.ks += self.el
    self.ks += (
      "  /* allocate local memory */" + self.el +
      "  __local DATA_TYPE_STR localA[NUM_UNROLL_ITER*(MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD)];" + self.el +
      "  __local DATA_TYPE_STR localB[NUM_UNROLL_ITER*(MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD)];" + self.el )

    ####################################
    # work item indices
    self.ks += self.el
    self.ks += (
      "  /* work item indices */" + self.el +
      "  uint groupRow = get_group_id(0);" + self.el +
      "  uint groupCol = get_group_id(1);" + self.el +
      "  uint localRow = get_local_id(0);" + self.el +
      "  uint localCol = get_local_id(1);" + self.el +
      "  uint localSerial = localRow + localCol*WG_NUM_ROWS;" + self.el )

    ####################################
    # global indices being loaded
    self.ks += self.el
    self.ks += "  /* global indices being loaded */" + self.el
    if (self.order=="clblasColumnMajor")==(self.transA=="T"):
      self.ks += ( "#define globalARow (groupRow*MACRO_TILE_NUM_ROWS + localSerial/NUM_UNROLL_ITER)" + self.el +
      "#define globalACol (localSerial%NUM_UNROLL_ITER)" + self.el +
      "#define globalAStride ( GET_GLOBAL_INDEX_A( (WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER, (WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER ) )" + self.el )
    else:
      self.ks += ( "#define globalARow (groupRow*MACRO_TILE_NUM_ROWS + localSerial%MACRO_TILE_NUM_ROWS)" + self.el +
      "#define globalACol (localSerial/MACRO_TILE_NUM_ROWS)" + self.el +
      "#define globalAStride ( GET_GLOBAL_INDEX_A( (WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_ROWS, (WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_ROWS ) )" + self.el )

    if (self.order=="clblasColumnMajor")==(self.transB=="T"):
      self.ks += ( "#define globalBRow (localSerial/MACRO_TILE_NUM_COLS)" + self.el +
      "#define globalBCol (groupCol*MACRO_TILE_NUM_COLS + localSerial%MACRO_TILE_NUM_COLS)" + self.el +
      "#define globalBStride ( GET_GLOBAL_INDEX_B( (WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_COLS, (WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_COLS) )" + self.el )
    else:
      self.ks += ( "#define globalBRow (localSerial%NUM_UNROLL_ITER)" + self.el +
      "#define globalBCol (groupCol*MACRO_TILE_NUM_COLS + localSerial/NUM_UNROLL_ITER)" + self.el +
      "#define globalBStride ( GET_GLOBAL_INDEX_B( (WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER, (WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER) )" + self.el )

    self.ks += ( "  A += GET_GLOBAL_INDEX_A( globalARow, globalACol );" + self.el +
      "  B += GET_GLOBAL_INDEX_B( globalBRow, globalBCol );" + self.el )

    ####################################
    # loop over k
    self.ks += self.el
    self.ks += (
      "  /* loop over k */" + self.el +
      "  uint block_k = K / NUM_UNROLL_ITER;" + self.el +
      "  do {" + self.el )

    ####################################
    # local indices being written
    self.ks += self.el
    self.ks += "    /* local indices being written */" + self.el
    if (self.order=="clblasColumnMajor")==(self.transA=="T"):
      self.ks += ( "#define localARow (localSerial / NUM_UNROLL_ITER)" + self.el +
      "#define localACol (localSerial % NUM_UNROLL_ITER)" + self.el +
      "#define localAStride (WG_NUM_ROWS*WG_NUM_COLS/NUM_UNROLL_ITER)" + self.el )
    else:
      self.ks += ( "#define localARow (localSerial % MACRO_TILE_NUM_ROWS)" + self.el +
      "#define localACol (localSerial / MACRO_TILE_NUM_ROWS)" + self.el +
      "#define localAStride (WG_NUM_ROWS*WG_NUM_COLS)" + self.el )

    if (self.order=="clblasColumnMajor")==(self.transB=="T"):
      print "transB == T"
      self.ks += ( "#define localBRow ( localSerial / MACRO_TILE_NUM_COLS )" + self.el +
      "#define localBCol ( localSerial % MACRO_TILE_NUM_COLS )" + self.el +
      "#define localBStride  (WG_NUM_ROWS*WG_NUM_COLS)" + self.el )
    else:
      self.ks += ( "#define localBRow ( localSerial % NUM_UNROLL_ITER )" + self.el +
      "#define localBCol ( localSerial / NUM_UNROLL_ITER )" + self.el +
      "#define localBStride (WG_NUM_ROWS*WG_NUM_COLS/NUM_UNROLL_ITER)" + self.el )


    self.ks += ("    __local DATA_TYPE_STR *lA = localA + GET_LOCAL_INDEX_A(localARow, localACol);" + self.el +
      "    __local DATA_TYPE_STR *lB = localB + GET_LOCAL_INDEX_B(localBRow, localBCol);" + self.el +
      "    barrier(CLK_LOCAL_MEM_FENCE);" + self.el )

    ####################################
    # load global -> local
    # threads to do loading = (wgNumRows*wgNumCols)
    # A elements to be loaded = wgNumRows*microTileNumRows*unroll
    # B elements to be loaded = wgNumCols*microTileNumCols*unroll
    self.ks += self.el
    self.ks += "    /* load global -> local */" + self.el
    numALoads  = (self.wgNumRows*self.microTileNumRows*self.unroll) \
        / (self.wgNumRows*self.wgNumCols)
    numALoadsR = (self.wgNumRows*self.microTileNumRows*self.unroll) \
        % (self.wgNumRows*self.wgNumCols)
    numBLoads  = (self.wgNumCols*self.microTileNumCols*self.unroll) \
        / (self.wgNumRows*self.wgNumCols)
    numBLoadsR = (self.wgNumCols*self.microTileNumCols*self.unroll) \
        % (self.wgNumRows*self.wgNumCols)

    for a in range(0, numALoads):
      self.ks += "    lA[ %d*localAStride ] = A[ %d*globalAStride ];%s" % (a, a, self.el)
    if numALoadsR:
      self.ks += "    if (localSerial < (WG_NUM_ROWS*MICRO_TILE_NUM_ROWS*NUM_UNROLL_ITER) ) {" + self.el
      self.ks += "      lA[ %d*localAStride ] = A[ %d*globalAStride ];%s" % (numALoads, numALoads, self.el)
      self.ks += "    }" + self.el

    for b in range(0, numBLoads):
      self.ks += "    lB[ %d*localBStride ] = B[ %d*globalBStride ];%s" % (b, b, self.el)
    if numBLoadsR:
      self.ks += "    if (localSerial < (WG_NUM_COLS*MICRO_TILE_NUM_COLS*NUM_UNROLL_ITER) ) {" + self.el
      self.ks += "      lB[ %d*localBStride ] = B[ %d*globalBStride ];%s" % (numBLoads, numBLoads, self.el)
      self.ks += "    }" + self.el
    self.ks += (
      "    barrier(CLK_LOCAL_MEM_FENCE);" + self.el +
      "    uint offA = localRow;" + self.el +
      "    uint offB = localCol;" + self.el )

    ####################################
    # do mads
    self.ks += self.el
    self.ks += "    /* do mads */" + self.el
    for u in range(0, self.unroll):
      self.ks += "    MICRO_TILE" + self.el

    ####################################
    # shift to next k block
    self.ks += self.el
    self.ks += "    /* shift to next k block */" + self.el
    if (self.order=="clblasColumnMajor")==(self.transA=="T"):
      self.ks += "    A += NUM_UNROLL_ITER;" + self.el
    else:
      self.ks += "    A += lda*NUM_UNROLL_ITER;" + self.el
    if (self.order=="clblasColumnMajor")==(self.transB=="T"):
      self.ks += "    B += ldb*NUM_UNROLL_ITER;" + self.el
    else:
      self.ks += "    B += NUM_UNROLL_ITER;" + self.el

    ####################################
    # end loop
    self.ks += self.el
    self.ks += "  } while (--block_k > 0);" + self.el
    self.ks += self.el

    ####################################
    # which global Cij index
    self.ks += self.el
    self.ks += "  /* which global Cij index */" + self.el
    self.ks += "  uint globalCRow = groupRow * MACRO_TILE_NUM_ROWS + localRow;" + self.el
    self.ks += "  uint globalCCol = groupCol * MACRO_TILE_NUM_COLS + localCol;" + self.el

    ####################################
    # write global Cij
    self.ks += self.el
    self.ks += "  /* write global Cij */" + self.el
    if self.precision=="c":
      self.ks += "  float type_mad_tmp;" + self.el
    if self.precision=="z":
      self.ks += "  double type_mad_tmp;" + self.el


    for a in range(0, self.microTileNumRows):
      for b in range(0, self.microTileNumCols):
        self.ks += "  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+%d*WG_NUM_ROWS, globalCCol+%d*WG_NUM_COLS) ], alpha, rC[%d][%d], beta )%s" % (a, b, a, b, self.el)

    ####################################
    # end kernel
    self.ks += self.el
    self.ks += "}" + self.el

    return self.ks


  ##############################################################################
  # Kernel - Write kernel to file
  ##############################################################################
  def writeKernelToFile(self):
    kernelName = self.getKernelName()
    kernelString = self.makeKernelString()
    kernelFileName = "gemmKernels/" + kernelName+"_src.h"
    kernelFile = open(kernelFileName, "w")
    kernelFile.write("static const char * const %s_src =\"" % (kernelName) )
    kernelFile.write(kernelString)
    kernelFile.write("\";\n")
    kernelFile.close()





################################################################################
# INC - Kernel Includes
################################################################################
class KernelIncludes:

  ##############################################################################
  # INC - default constructor
  ##############################################################################
  def __init__(self, precision):
    self.includeSourceFileName = precision+"gemmSourceIncludes.h"
    self.includeBinaryFileName = precision+"gemmBinaryIncludes.h"
    self.srcStr = "#ifndef " + precision + "gemm_SOURCE_INCLUDES_H\n"
    self.srcStr += "#define " + precision + "gemm_SOURCE_INCLUDES_H\n"
    self.srcStr += "\n"
    self.binStr = "#ifndef " + precision + "gemm_BINARY_INCLUDES_H\n"
    self.binStr += "#define " + precision + "gemm_BINARY_INCLUDES_H\n"
    self.binStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getKernelName()
    self.srcStr += "#include \"gemmKernels/%s_src.h\"\n" % kernelName
    self.binStr += "#include \"gemmKernels/%s_bin.h\"\n" % kernelName

  def writeToFile(self):
    srcFile = open(self.includeSourceFileName, "w")
    srcFile.write( self.srcStr )
    srcFile.write( "\n#endif\n" )
    srcFile.close()
    binFile = open(self.includeBinaryFileName, "w")
    binFile.write( self.binStr )
    binFile.write( "\n#endif\n" )
    binFile.close()



################################################################################
# KSL - Kernel Selection Logic File
################################################################################
class KernelSelectionLogic:

  zeroIndent = "  "
  tab = "  "
  ##############################################################################
  # KSL - default constructor
  ##############################################################################
  def __init__(self, \
      precision, \
      listOrder, \
      listTrans, \
      listBeta, \
      listWorkGroupDims, \
      listMicroTileDims, \
      listUnroll, \
      listMicroTileSizes ):

    self.kernelSelectionFileName = precision + "gemmKernelSelection.h"
    self.listMicroTileSizes = listMicroTileSizes

    self.logic = (
      "#include \"" + precision + "gemmSourceIncludes.h\"\n"
      "// #include \"" + precision + "gemmBinaryIncludes.h\"\n"
      "\n"
      "// kernel selection logic\n"
      "void " + precision + "gemmSelectKernel(\n"
      "  clblasOrder order,\n"
      "  clblasTranspose transA,\n"
      "  clblasTranspose transB,\n"
      "  unsigned int M,\n"
      "  unsigned int N,\n"
      "  unsigned int K,\n"
      "  bool betaNonZero,\n"
      "  float optimalNumElementsPerWorkItem,\n"
      "  const char **kernelSource\n"
      ") {\n" )
    self.orderInitialized = False
    self.transInitialized = False
    self.betaInitialized = False
    self.previousTileSize = 0


  ####################################
  # KSL - new order
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
  # KSL - new trans
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
  # KSL - new beta
  def newBeta(self, beta):
    if (self.betaInitialized):
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab + "}\n" # 3 tabs
      self.logic += self.zeroIndent+self.tab+self.tab # 2 tabs
      self.logic += "} else "
    else:
      self.logic += self.zeroIndent+self.tab+self.tab # 2 tabs
    self.logic += "if ( "
    if beta == 0:
      self.logic += "!betaNonZero"
    else:
      self.logic += "betaNonZero"
    self.logic += " ) {\n"
    self.betaInitialized = True
    self.previousTileSize = 0


  ##############################################################################
  # KSL - add new kernel
  ##############################################################################
  def newKernel(self, kernel):

    # first tile size for beta?
    if self.previousTileSize == 0:
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab # 3 tabs
      self.logic += "if (optimalNumElementsPerWorkItem > " + str(self.listMicroTileSizes[1]) + ") {\n"
      self.previousTileSize = self.listMicroTileSizes[0]
      self.kernelInitialized = False

    # new tile size?
    tileSize = kernel.microTileNumRows * kernel.microTileNumCols
    tileSizeIndex = self.listMicroTileSizes.index(tileSize)
    if tileSize != self.previousTileSize:
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab # 3 tabs
      self.logic += "}\n"
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab # 3 tabs
      self.logic += "if (optimalNumElementsPerWorkItem > "
      if tileSizeIndex+1 < len(self.listMicroTileSizes):
        self.logic += str(self.listMicroTileSizes[tileSizeIndex+1])
      else:
        self.logic += str(0)
      self.logic += ") {\n"
      self.kernelInitialized = False
      self.previousTileSize = tileSize

    # new kernel
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "if ( M%%%d == 0 && N%%%d == 0 && K%%%d == 0) {\n" % (kernel.getMultipleM(), kernel.getMultipleN(), kernel.getMultipleK())
    #self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    #self.logic += "printf(\"selected kernel: " + kernel.getKernelName() + "\\n\");\n"
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*kernelSource= " + kernel.getKernelName() + "_src;\n"
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "return;\n"
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "}\n"


  ####################################
  # KSL - finish (close braces)
  def finish(self):
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab + "}\n" # 3 tabs
    self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
    self.logic += self.zeroIndent+self.tab + "}\n" # 1 tab
    self.logic += self.zeroIndent + "}\n" # 0 tab
    self.logic += "}\n" # close function


  ##############################################################################
  # KSL - write to file
  ##############################################################################
  def writeToFile(self):
    selectionFile = open(self.kernelSelectionFileName, "w")
    selectionFile.write(self.logic)
    selectionFile.write("\n")
    selectionFile.close()






################################################################################
# Call Main
################################################################################
if __name__ == "__main__":
  main(sys.argv[1:])
