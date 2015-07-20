################################################################################
# Auto-Gemm
# - Automatically generate gemm kernels based on tile parameters
# - This script generates the following to ease integration into clBLAS:
#   - generate all the kernel files
#   - list to add to src/library/CMakeLists.txt:SRC_CL_TEMPLATES
#   - list to add to src/library/CMakeLists.txt:SRC_CL_TEMPLATES_GEN
#   - list to add to src/library/bingen.cmake:BIN_CL_TEMPLATES_HAWAII_CL2
#   - kernel selection logic
#   - include files for kernel strings
#
# TODO
# - after writing kernel files, make list of valid micro tiles for correct size list
# - zgemm() call is in xgemm.cc
# - one functions writes every combination to a file, while one reads from that file, therefore manual intervention for deleting slow kernels
# - max tile size product for a given precision
# - fuse together unroll=8 and unroll=1 in same kernel
################################################################################

import os
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

  # create directories
  precision = "c"
  kernelSourcePath = precision.capitalize() + "gemmKernelSources"
  kernelBinaryPath = precision.capitalize() + "gemmKernelBinaries"
  if not os.path.exists(kernelSourcePath):
    os.makedirs(kernelSourcePath)
  if not os.path.exists(kernelBinaryPath):
    os.makedirs(kernelBinaryPath)

  # non-tile parameters
  listOrder = [ "clblasColumnMajor", "clblasRowMajor" ]
  listTrans = [
    [ "N", "N" ],
    [ "T", "N" ],
    [ "N", "T" ],
    [ "T", "T" ],
    ]
  listBeta = [ 0, 1 ]

  # tile parameters
  microTileMaxProductDict = { "s":(6*6), "d":(6*6), "c":(3*6), "z":(3*3) }
  microTileMaxProduct = microTileMaxProductDict[ precision ]
  microTileMaxEdgeLengthDict = { "s":8, "d":8, "c":8, "z":8 }
  microTileMaxEdgeLength = microTileMaxEdgeLengthDict[ precision ]
  listUnroll = [ 8, 1 ]
  listWorkGroupDims = [ [16, 16] ]
  listTileKernelParameters = []
  listEdgeKernelParameters = []
  # list all valid tile parameter combinations
  listMicroTileSizes = [
      [ 6, 6 ], # 36
      [ 8, 4 ], # 32
      #[ 7, 4 ], # 28
      [ 6, 4 ], # 24
      #[ 5, 4 ], # 20
      [ 4, 4 ], # 16
      # [ 4, 3 ], # 12
      [ 4, 2 ], # 8
      #[ 3, 2 ], # 6
      [ 2, 2 ], # 4
      [ 2, 1 ], # 2
      [ 1, 1 ]  # 1
      ]

  for microTileSize in listMicroTileSizes:
    if microTileSize[0]*microTileSize[1] <= microTileMaxProduct:
      for workGroupDim in listWorkGroupDims:
        for unroll in listUnroll:
          kernel = GemmOpenCLKernelSource()
          kernel.workGroupNumRows = workGroupDim[0]
          kernel.workGroupNumCols = workGroupDim[1]
          kernel.microTileNumRows = microTileSize[0]
          kernel.microTileNumCols = microTileSize[0]
          kernel.unroll = unroll
          if kernel.kernelParamsValid():
            listTileKernelParameters.append( \
                [workGroupDim[0], workGroupDim[1], \
                microTileSize[0], microTileSize[1], unroll] )
          else:
            print kernel.getkernelName() + " - SKIPPING - "
  listTileKernelParameters.sort(orderTileSizes, reverse=True)
  print( listTileKernelParameters )
  # make list of unique tile sizes
  listMicroTileSizes = []
  for tile in listTileKernelParameters:
    size = tile[2]*tile[3]
    if size not in listMicroTileSizes:
      listMicroTileSizes.append(size)

  kernelSelectionLogic = KernelSelectionLogic(precision, listOrder, listTrans, listBeta, listMicroTileSizes);
  kernelSourceIncludes = KernelSourceIncludes(precision)
  kernelBinaryIncludes = KernelBinaryIncludes(precision)
  clKernelIncludes = ClKernelIncludes(precision)
  kernelSourceBuildOptions = KernelSourceBuildOptions(precision)
  kernelBinaryBuildOptions = KernelBinaryBuildOptions(precision)
  cppKernelEnumeration = CppKernelEnumeration(precision)

  # files to write lists to
  fileSrcClTemplates = open(precision.capitalize() + "gemm_SRC_CL_TEMPLATES.txt", "w")
  fileSrcClTemplatesGen = open(precision.capitalize() + "gemm_SRC_CL_TEMPLATES_GEN.txt", "w")
  fileBinClTemplates = open(precision.capitalize() + "gemm_BIN_CL_TEMPLATES.txt", "w")


  # for each kernel parameter combination
  for order in listOrder:
    kernelSelectionLogic.newOrder(order)
    for trans in listTrans:
      kernelSelectionLogic.newTrans(trans)
      for beta in listBeta:
        kernelSelectionLogic.newBeta(beta)
        for tile in listTileKernelParameters:
          # set kernel parameters
          kernel = GemmOpenCLKernelSource()
          kernel.precision = precision
          kernel.order = order
          kernel.transA = trans[0]
          kernel.transB = trans[1]
          kernel.beta = beta
          kernel.workGroupNumRows = tile[0]
          kernel.workGroupNumCols = tile[1]
          kernel.microTileNumRows = tile[2]
          kernel.microTileNumCols = tile[3]
          kernel.macroTileNumRows = tile[0]*tile[2]
          kernel.macroTileNumCols = tile[1]*tile[3]
          kernel.unroll = tile[4]
          # process kernel parameters
          processKernel( \
              kernel, \
              kernelSelectionLogic, \
              kernelSourceIncludes, \
              kernelBinaryIncludes, \
              clKernelIncludes, \
              kernelSourceBuildOptions, \
              kernelBinaryBuildOptions, \
              fileSrcClTemplates, \
              fileSrcClTemplatesGen, \
              fileBinClTemplates, \
              cppKernelEnumeration )

  # save written files
  kernelSelectionLogic.finish()
  kernelSelectionLogic.writeToFile()
  kernelSourceIncludes.writeToFile()
  kernelBinaryIncludes.writeToFile()
  clKernelIncludes.writeToFile()
  kernelSourceBuildOptions.writeToFile()
  kernelBinaryBuildOptions.writeToFile()
  cppKernelEnumeration.writeToFile()

  fileSrcClTemplates.close()
  fileSrcClTemplatesGen.close()
  fileBinClTemplates.close()



################################################################################
# Main - Order Tile Sizes
# - returns 1 if tileA should come first
# - process tiles largest -> smallest (elements/work-item)
# - for same size tile, choose squarer one
################################################################################
def orderTileSizes(tileA, tileB):
  tileAWorkGroupSize = tileA[0] * tileA[1]
  tileAMicroTileSize = tileA[2] * tileA[3]
  tileASize = tileAWorkGroupSize*tileAMicroTileSize

  tileBWorkGroupSize = tileB[0] * tileB[1]
  tileBMicroTileSize = tileB[2] * tileB[3]
  tileBSize = tileBWorkGroupSize*tileBMicroTileSize
  # choose larger macro tile
  if (tileASize > tileBSize):
    return 1
  elif (tileBSize > tileASize):
    return -1
  else: # macro tile same
    tileANumRows = tileA[0] + tileA[2]
    tileANumCols = tileA[1] + tileA[3]
    tileBNumRows = tileB[0] + tileB[2]
    tileBNumCols = tileB[1] + tileB[3]
    # choose the squarer one
    if (tileANumRows+tileANumCols) < (tileBNumRows+tileBNumCols):
      return 1
    elif (tileBNumRows+tileBNumCols) < (tileANumRows+tileANumCols):
      return -1
    else: #same macro tile dimensions
      # choose larger unroll
      if tileA[4] > tileB[4]:
        return 1
      else:
        return -1


################################################################################
# Main - Process kernel
################################################################################
def processKernel( \
    kernel, \
    kernelSelectionLogic, \
    kernelSourceIncludes, \
    kernelBinaryIncludes, \
    clKernelIncludes, \
    kernelSourceBuildOptions, \
    kernelBinaryBuildOptions, \
    fileSrcClTemplates, \
    fileSrcClTemplatesGen, \
    fileBinClTemplates, \
    cppKernelEnumeration ):
  global totalParameterCombinations, validParameterCombinations

  # check if parameter combination is valid
  totalParameterCombinations += 1
  kernelName = kernel.getKernelName()
  if kernel.kernelParamsValid():
    #print "Processing: " + kernelName
    validParameterCombinations += 1
  else:
    errorString = kernel.ks
    print kernelName + " - SKIPPING - " + errorString
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
  kernelSourceIncludes.addKernel(kernel)
  kernelBinaryIncludes.addKernel(kernel)
  kernelSourceBuildOptions.addKernel(kernel)
  kernelBinaryBuildOptions.addKernel(kernel)
  clKernelIncludes.addKernel(kernel)

  # 6) write cpp kernel parameter enumeration
  cppKernelEnumeration.addKernel(kernel)

  # 7) write kernel to file
  macroTileNumRows = kernel.macroTileNumRows
  macroTileNumCols = kernel.macroTileNumCols
  # row kernel
  kernel.macroTileNumRows = 1
  kernel.writeKernelToFile()
  # col kernel
  kernel.macroTileNumRows = macroTileNumRows
  kernel.macroTileNumCols = 1
  kernel.writeKernelToFile()
  # corner kernel
  kernel.macroTileNumRows = 1
  kernel.macroTileNumCols = 1
  kernel.writeKernelToFile()



################################################################################
# Kernel - Creates a GEMM OpenCL Kernel
################################################################################

# define gemm data types
# "s", "d", "c", "z"
hostDataChar = { "s":"s", "d":"d", "c":"c", "z":"z" }
hostDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }
openclDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }

class GemmOpenCLKernelSource:

  ##############################################################################
  # Kernel - default constructor
  ##############################################################################
  def __init__(self):
    self.precision = "s" # s, d, c, z
    self.order = "clblasColumnMajor" # column, row
    self.transA = "N" # N, T
    self.transB = "N" # N, T
    self.beta = 1
    self.workGroupNumRows = 16
    self.workGroupNumCols = 16
    self.microTileNumRows = 1
    self.microTileNumCols = 1
    self.macroTileNumRows = 1
    self.macroTileNumCols = 1
    self.localRowPad = 0
    self.localColPad = 0
    self.unroll = 8
    self.ks = "haven't called makeKernelString()" # kernel string
    self.el = "\\n\"\n\""


  ##############################################################################
  # Kernel - get multiples
  ##############################################################################
  def getMultipleM(self):
    return (self.workGroupNumRows * self.microTileNumRows)
  def getMultipleN(self):
    return (self.workGroupNumCols * self.microTileNumCols)
  def getMultipleK(self):
    return (self.unroll)

  ##############################################################################
  # Row Kernel
  # - macroTileNumRows = 1
  # - guards around gA -> lA
  # - guards around gC[gRow,:] = rC[row,:]
  ##############################################################################
  def isRowKernel(self):
    if self.workGroupNumRows * self.microTileNumRows == self.macroTileNumRows:
      return False; # normal tile kernel
    else:
      if self.macroTileNumRows == 1:
        return True; # single row kernel
      else:
        printf("ERROR: workGroupNumRows=%u, microTileNumRows=%u and macroTileNumRows=%u doesn't make sense\n" % (self.workGroupNumRows, self.microTileNumRows, self.macroTileNumRows) );
        return False; # ERROR


  ##############################################################################
  # Col Kernel
  # - macroTileNumCols = 1
  # - guards around gB -> lB
  # - guards around gC[:,gCol] = rC[:,col]
  ##############################################################################
  def isColKernel(self):
    if self.workGroupNumCols * self.microTileNumCols == self.macroTileNumCols:
      return False; # normal tile kernel
    else:
      if self.macroTileNumCols == 1:
        return True; # single row kernel
      else:
        printf("ERROR: workGroupNumCols=%u, microTileNumCols=%u and macroTileNumCols=%u doesn't make sense\n" % (self.workGroupNumCols, self.microTileNumCols, self.macroTileNumCols) );
        return False; # ERROR



  ##############################################################################
  # Kernel - get kernel name
  ##############################################################################
  def getKernelName(self):
    kernelName = "%sgemm_%1s%1s_%03d_%03d_%01d_%02dx%02d_%01dx%01d" % (hostDataChar[self.precision], self.transA, self.transB, self.macroTileNumRows, self.macroTileNumCols, self.unroll, self.workGroupNumRows, self.workGroupNumCols, self.microTileNumRows, self.microTileNumCols)
    if (self.order=="clblasColumnMajor"):
      kernelName += "_ColMajor"
    else:
      kernelName += "_RowMajor"
    if (self.beta==1):
      kernelName += "_BETA"
    return kernelName

  def getRowKernelName(self):
    kernelName = "%sgemm_%1s%1s_%03d_%03d_%01d_%02dx%02d_%01dx%01d" % (hostDataChar[self.precision], self.transA, self.transB, 1, self.macroTileNumCols, self.unroll, self.workGroupNumRows, self.workGroupNumCols, self.microTileNumRows, self.microTileNumCols)
    if (self.order=="clblasColumnMajor"):
      kernelName += "_ColMajor"
    else:
      kernelName += "_RowMajor"
    if (self.beta==1):
      kernelName += "_BETA"
    return kernelName

  def getColKernelName(self):
    kernelName = "%sgemm_%1s%1s_%03d_%03d_%01d_%02dx%02d_%01dx%01d" % (hostDataChar[self.precision], self.transA, self.transB, self.macroTileNumRows, 1, self.unroll, self.workGroupNumRows, self.workGroupNumCols, self.microTileNumRows, self.microTileNumCols)
    if (self.order=="clblasColumnMajor"):
      kernelName += "_ColMajor"
    else:
      kernelName += "_RowMajor"
    if (self.beta==1):
      kernelName += "_BETA"
    return kernelName

  def getCornerKernelName(self):
    kernelName = "%sgemm_%1s%1s_%03d_%03d_%01d_%02dx%02d_%01dx%01d" % (hostDataChar[self.precision], self.transA, self.transB, 1, 1, self.unroll, self.workGroupNumRows, self.workGroupNumCols, self.microTileNumRows, self.microTileNumCols)
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
    numALoads = (self.workGroupNumRows*self.microTileNumRows*self.unroll)/(self.workGroupNumRows*self.workGroupNumCols)
    numALoadsR = (self.workGroupNumRows*self.microTileNumRows*self.unroll)%(self.workGroupNumRows*self.workGroupNumCols)
    numBLoads = (self.workGroupNumCols*self.microTileNumCols*self.unroll)/(self.workGroupNumRows*self.workGroupNumCols)
    numBLoadsR = (self.workGroupNumCols*self.microTileNumCols*self.unroll)%(self.workGroupNumRows*self.workGroupNumCols)
    if (numALoads>0 and numALoadsR>0):
      self.ks = "(%2d * %d * %d = %3d) A elements can't be loaded by (%2d * %2d = %3d) threads" % (self.workGroupNumRows,self.microTileNumRows,self.unroll,(self.workGroupNumRows*self.microTileNumRows*self.unroll),self.workGroupNumRows,self.workGroupNumCols,(self.workGroupNumRows*self.workGroupNumCols))
      return False
    elif (numBLoads>0 and numBLoadsR>0):
      self.ks = "(%2d * %d * %d = %3d) B elements can't be loaded by (%2d * %2d = %3d) threads" % (self.workGroupNumCols,self.microTileNumCols,self.unroll,(self.workGroupNumCols*self.microTileNumCols*self.unroll),self.workGroupNumRows,self.workGroupNumCols,(self.workGroupNumRows*self.workGroupNumCols))
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
    self.ks += "#define WG_NUM_ROWS          %d%s" % (self.workGroupNumRows, self.el )
    self.ks += "#define WG_NUM_COLS          %d%s" % (self.workGroupNumCols, self.el )
    self.ks += "#define MICRO_TILE_NUM_ROWS  %d%s" % (self.microTileNumRows, self.el )
    self.ks += "#define MICRO_TILE_NUM_COLS  %d%s" % (self.microTileNumCols, self.el )
    self.ks += "#define MACRO_TILE_NUM_ROWS  %s%s" % ((self.workGroupNumRows * self.microTileNumRows), self.el )
    self.ks += "#define MACRO_TILE_NUM_COLS  %s%s" % ((self.workGroupNumCols * self.microTileNumCols), self.el )
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
          "  /* (2) */ \\\\" + self.el +
          "  REG.s0 = mad(  BETA.s0, DST.s0, REG.s0 ); \\\\" + self.el +
          "  REG.s0 = mad( -BETA.s1, DST.s1, REG.s0 ); \\\\" + self.el +
          "  REG.s1 = mad(  BETA.s1, DST.s0, REG.s1 ); \\\\" + self.el +
          "  REG.s1 = mad(  BETA.s0, DST.s1, REG.s1 ); \\\\" + self.el +
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
    self.ks += "  /* work item indices */" + self.el
    if self.isRowKernel():
      self.ks += "  uint groupRow = M / " + str(self.workGroupNumRows*self.microTileNumRows) + "; // last row" + self.el
    else:
      self.ks += "  uint groupRow = get_group_id(0);" + self.el
    if self.isColKernel():
      self.ks += "  uint groupCol = N / " + str(self.workGroupNumCols*self.microTileNumCols) + "; // last column" + self.el
    else:
      self.ks += "  uint groupCol = get_group_id(1);" + self.el
    self.ks += (
      "  uint localRow = get_local_id(0);" + self.el +
      "  uint localCol = get_local_id(1);" + self.el +
      "  uint localSerial = localRow + localCol*WG_NUM_ROWS;" + self.el )

    ####################################
    # global indices being loaded
    self.ks += self.el
    self.ks += "  /* global indices being loaded */" + self.el
    if (self.order=="clblasColumnMajor")==(self.transA=="T"):
      self.ks += ( # TODO
        "#define globalARow(LID) (groupRow*MACRO_TILE_NUM_ROWS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER)" + self.el +
        "#define globalACol(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER)" + self.el )
    else:
      self.ks += (
        "#define globalARow(LID) (groupRow*MACRO_TILE_NUM_ROWS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_ROWS)" + self.el +
        "#define globalACol(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_ROWS)" + self.el )

    if (self.order=="clblasColumnMajor")==(self.transB=="T"):
      self.ks += ( # TODO
        "#define globalBRow(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_COLS)" + self.el +
        "#define globalBCol(LID) (groupCol*MACRO_TILE_NUM_COLS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_COLS)" + self.el )
    else:
      self.ks += (
        "#define globalBRow(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER)" + self.el +
        "#define globalBCol(LID) (groupCol*MACRO_TILE_NUM_COLS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER)" + self.el )

    #self.ks += (
    #  "  A += GET_GLOBAL_INDEX_A( globalARow, globalACol );" + self.el +
    #  "  B += GET_GLOBAL_INDEX_B( globalBRow, globalBCol );" + self.el )

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
      self.ks += (
        "#define localARow (localSerial / NUM_UNROLL_ITER)" + self.el +
        "#define localACol (localSerial % NUM_UNROLL_ITER)" + self.el +
        "#define localAStride (WG_NUM_ROWS*WG_NUM_COLS/NUM_UNROLL_ITER)" + self.el )
    else:
      self.ks += (
        "#define localARow (localSerial % MACRO_TILE_NUM_ROWS)" + self.el +
        "#define localACol (localSerial / MACRO_TILE_NUM_ROWS)" + self.el +
        "#define localAStride (WG_NUM_ROWS*WG_NUM_COLS)" + self.el )

    if (self.order=="clblasColumnMajor")==(self.transB=="T"):
      self.ks += (
        "#define localBRow ( localSerial / MACRO_TILE_NUM_COLS )" + self.el +
        "#define localBCol ( localSerial % MACRO_TILE_NUM_COLS )" + self.el +
        "#define localBStride  (WG_NUM_ROWS*WG_NUM_COLS)" + self.el )
    else:
      self.ks += (
        "#define localBRow ( localSerial % NUM_UNROLL_ITER )" + self.el +
        "#define localBCol ( localSerial / NUM_UNROLL_ITER )" + self.el +
        "#define localBStride (WG_NUM_ROWS*WG_NUM_COLS/NUM_UNROLL_ITER)" + self.el )


    self.ks += (
      "    __local DATA_TYPE_STR *lA = localA + GET_LOCAL_INDEX_A(localARow, localACol);" + self.el +
      "    __local DATA_TYPE_STR *lB = localB + GET_LOCAL_INDEX_B(localBRow, localBCol);" + self.el +
      "    barrier(CLK_LOCAL_MEM_FENCE);" + self.el )

    ####################################
    # load global -> local
    # threads to do loading = (workGroupNumRows*workGroupNumCols)
    # A elements to be loaded = workGroupNumRows*microTileNumRows*unroll
    # B elements to be loaded = workGroupNumCols*microTileNumCols*unroll
    self.ks += self.el
    self.ks += "    /* load global -> local */" + self.el
    numALoads  = (self.workGroupNumRows*self.microTileNumRows*self.unroll) \
        / (self.workGroupNumRows*self.workGroupNumCols)
    numALoadsR = (self.workGroupNumRows*self.microTileNumRows*self.unroll) \
        % (self.workGroupNumRows*self.workGroupNumCols)
    numBLoads  = (self.workGroupNumCols*self.microTileNumCols*self.unroll) \
        / (self.workGroupNumRows*self.workGroupNumCols)
    numBLoadsR = (self.workGroupNumCols*self.microTileNumCols*self.unroll) \
        % (self.workGroupNumRows*self.workGroupNumCols)

    # TODO - zeroString for real and complex
    if self.precision == "c":
      zeroString = "(float2)(0.f, 0.f)"
    elif self.precision == "z":
      zeroString = "(double2)(0.0, 0.0)"
    else:
      zeroString = "0.0"
    for a in range(0, numALoads):
      self.ks += "    lA[ %d*localAStride ] = " % a
      if self.isRowKernel():
        self.ks += "( globalARow(%d) >= M) ? %s : " % ( a, zeroString )
      self.ks += "A[ GET_GLOBAL_INDEX_A( globalARow(%d), globalACol(%d) ) ];%s" % (a, a, self.el)
    if numALoadsR:
      self.ks += "    if (localSerial < (WG_NUM_ROWS*MICRO_TILE_NUM_ROWS*NUM_UNROLL_ITER) ) {" + self.el
      self.ks += "      lA[ %d*localAStride ] = " % numALoads
      if self.isRowKernel():
        self.ks += "( globalARow(%d) >= M) ? %s : " % ( numALoads, zeroString )
      self.ks += "A[ GET_GLOBAL_INDEX_A( globalARow(%d), globalACol(%d) ) ];%s" % (numALoads, numALoads, self.el)
      self.ks += "    }" + self.el

    for b in range(0, numBLoads):
      self.ks += "    lB[ %d*localBStride ] = " % b
      if self.isColKernel():
        self.ks += "( globalBCol(%d) >= N) ? %s : " % ( b, zeroString )
      self.ks += "B[ GET_GLOBAL_INDEX_B( globalBRow(%d), globalBCol(%d) ) ];%s" % (b, b, self.el)
    if numBLoadsR:
      self.ks += "    if (localSerial < (WG_NUM_COLS*MICRO_TILE_NUM_COLS*NUM_UNROLL_ITER) ) {" + self.el
      self.ks += "      lB[ %d*localBStride ] = " % numBLoads
      if self.isColKernel():
        self.ks += "(globalBCol(%d) >= N) ? %s : " % ( numBLoads, zeroString )
      self.ks += "B[ GET_GLOBAL_INDEX_B( globalBRow(%d), globalBCol(%d) ) ];%s" % (numBLoads, numBLoads, self.el)
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
        if self.isRowKernel():
          self.ks += "  if (globalCRow+%d*WG_NUM_ROWS < M)" % a
        if self.isColKernel():
          self.ks += "  if (globalCCol+%d*WG_NUM_COLS < N)" % b
        if self.isRowKernel() or self.isColKernel():
          self.ks += "{"
        self.ks += "  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+%d*WG_NUM_ROWS, globalCCol+%d*WG_NUM_COLS) ], alpha, rC[%d][%d], beta )" % (a, b, a, b)
        if self.isRowKernel() or self.isColKernel():
          self.ks += "}"
        self.ks += self.el

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
    kernelFileName = self.precision.capitalize() + "gemmKernelSources/" + kernelName+"_src.h"
    kernelFile = open(kernelFileName, "w")
    kernelFile.write("static const char * const %s_src =\"" % (kernelName) )
    kernelFile.write(kernelString)
    kernelFile.write("\";\n")
    kernelFile.close()



################################################################################
# SINC - Kernel Source Includes
################################################################################
class KernelSourceIncludes:

  ##############################################################################
  # SINC - default constructor
  ##############################################################################
  def __init__(self, precision):
    self.fileName = precision.capitalize()+"gemmSourceIncludes.h"
    self.fileStr = "#ifndef " + precision.capitalize() + "gemm_SOURCE_INCLUDES_H\n"
    self.fileStr += "#define " + precision.capitalize() + "gemm_SOURCE_INCLUDES_H\n"
    self.fileStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getKernelName()
    self.fileStr += "#include \"" + kernel.precision.capitalize() + "gemmKernelSources/%s_src.h\"\n" % kernelName
    kernelName = kernel.getRowKernelName()
    self.fileStr += "#include \"" + kernel.precision.capitalize() + "gemmKernelSources/%s_src.h\"\n" % kernelName
    kernelName = kernel.getColKernelName()
    self.fileStr += "#include \"" + kernel.precision.capitalize() + "gemmKernelSources/%s_src.h\"\n" % kernelName
    kernelName = kernel.getCornerKernelName()
    self.fileStr += "#include \"" + kernel.precision.capitalize() + "gemmKernelSources/%s_src.h\"\n" % kernelName

  def writeToFile(self):
    incFile = open(self.fileName, "w")
    incFile.write( self.fileStr )
    incFile.write( "\n#endif\n" )
    incFile.close()


################################################################################
# BINC - Kernel Binary Includes
################################################################################
class KernelBinaryIncludes:

  ##############################################################################
  # BINC - default constructor
  ##############################################################################
  def __init__(self, precision):
    self.incFileName = precision.capitalize()+"gemmBinaryIncludes.h"
    self.incStr = "#ifndef " + precision.capitalize() + "gemm_BINARY_INCLUDES_H\n"
    self.incStr += "#define " + precision.capitalize() + "gemm_BINARY_INCLUDES_H\n"
    self.incStr += "\n"
    self.nullFileName = precision.capitalize()+"gemmBinaryNulls.h"
    self.nullStr = "#ifndef " + precision.capitalize() + "gemm_BINARY_NULLS_H\n"
    self.nullStr += "#define " + precision.capitalize() + "gemm_BINARY_NULLS_H\n"
    self.nullStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getKernelName()
    self.incStr += "#include \"" + kernel.precision.capitalize() + "gemmKernelBinaries/%s_bin.h\"\n" % kernelName
    self.nullStr += "char *%s_bin = NULL;\n" % kernelName
    kernelName = kernel.getRowKernelName()
    self.incStr += "#include \"" + kernel.precision.capitalize() + "gemmKernelBinaries/%s_bin.h\"\n" % kernelName
    self.nullStr += "char *%s_bin = NULL;\n" % kernelName
    kernelName = kernel.getColKernelName()
    self.incStr += "#include \"" + kernel.precision.capitalize() + "gemmKernelBinaries/%s_bin.h\"\n" % kernelName
    self.nullStr += "char *%s_bin = NULL;\n" % kernelName
    kernelName = kernel.getCornerKernelName()
    self.incStr += "#include \"" + kernel.precision.capitalize() + "gemmKernelBinaries/%s_bin.h\"\n" % kernelName
    self.nullStr += "char *%s_bin = NULL;\n" % kernelName

  def writeToFile(self):
    incFile = open(self.incFileName, "w")
    incFile.write( self.incStr )
    incFile.write( "\n#endif\n" )
    incFile.close()
    nullFile = open(self.nullFileName, "w")
    nullFile.write( self.nullStr )
    nullFile.write( "\n#endif\n" )
    nullFile.close()


################################################################################
# CINC - ClKernel Includes
################################################################################
class ClKernelIncludes:

  ##############################################################################
  # CINC - default constructor
  ##############################################################################
  def __init__(self, precision):
    self.fileName = precision.capitalize()+"gemmClKernels.h"
    self.fileStr = "#ifndef " + precision.capitalize() + "gemm_CL_KERNELS_H\n"
    self.fileStr += "#define " + precision.capitalize() + "gemm_CL_KERNELS_H\n"
    self.fileStr += "#include \"CL/cl.h\"\n"
    self.fileStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getKernelName()
    self.fileStr += "cl_kernel %s_clKernel;\n" % kernelName
    kernelName = kernel.getRowKernelName()
    self.fileStr += "cl_kernel %s_clKernel;\n" % kernelName
    kernelName = kernel.getColKernelName()
    self.fileStr += "cl_kernel %s_clKernel;\n" % kernelName
    kernelName = kernel.getCornerKernelName()
    self.fileStr += "cl_kernel %s_clKernel;\n" % kernelName

  def writeToFile(self):
    incFile = open(self.fileName, "w")
    incFile.write( self.fileStr )
    incFile.write( "\n#endif\n" )
    incFile.close()


################################################################################
# KSBO - Kernel Source Build Options
################################################################################
class KernelSourceBuildOptions:

  ##############################################################################
  # KSBO - default constructor
  ##############################################################################
  def __init__(self, precision):
    self.fileName = precision.capitalize()+"gemmKernelSourceBuildOptions.h"
    self.fileStr = "#ifndef " + precision.capitalize() + "gemm_KERNEL_SOURCE_BUILD_OPTIONS_H\n"
    self.fileStr += "#define " + precision.capitalize() + "gemm_KERNEL_SOURCE_BUILD_OPTIONS_H\n"
    self.fileStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getKernelName()
    self.fileStr += "char *%s_srcBuildOptions = \"-cl-std=CL2.0\";\n" % kernelName

  def writeToFile(self):
    incFile = open(self.fileName, "w")
    incFile.write( self.fileStr )
    incFile.write( "\n#endif\n" )
    incFile.close()


################################################################################
# KBSO - Kernel Binary Build Options
################################################################################
class KernelBinaryBuildOptions:

  ##############################################################################
  # KBSO - default constructor
  ##############################################################################
  def __init__(self, precision):
    self.fileName = precision.capitalize()+"gemmKernelBinaryBuildOptions.h"
    self.fileStr = "#ifndef " + precision.capitalize() + "gemm_KERNEL_BINARY_BUILD_OPTIONS_H\n"
    self.fileStr += "#define " + precision.capitalize() + "gemm_KERNEL_BINARY_BUILD_OPTIONS_H\n"
    self.fileStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getKernelName()
    self.fileStr += "char *%s_binBuildOptions = NULL;\n" % kernelName

  def writeToFile(self):
    incFile = open(self.fileName, "w")
    incFile.write( self.fileStr )
    incFile.write( "\n#endif\n" )
    incFile.close()


################################################################################
# CPPKE - Cpp Kernel enumeration
################################################################################
class CppKernelEnumeration:

  ##############################################################################
  # CPPKE - default constructor
  ##############################################################################
  def __init__(self, precision):
    self.fileName = precision.capitalize()+"gemmKernelEnumeration.h"
    self.fileStr = "unsigned int gemmKernelEnumeration[][11] = {\n"
    self.count = 0

  def addKernel(self, kernel):
    # 6) list to add to ktest for automated kernel testing
    for mSpill in range(0, 2):
      for nSpill in range(0, 2):
        self.fileStr += "  { %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u },\n" % ( \
          1 if kernel.order=="clblasColumnMajor" else 0, \
          1 if kernel.transA=="T" else 0, \
          1 if kernel.transB=="T" else 0, \
          1 if kernel.beta>0 else 0, \
          kernel.microTileNumRows, \
          kernel.microTileNumCols, \
          kernel.workGroupNumRows, \
          kernel.workGroupNumCols, \
          kernel.unroll, \
          mSpill, \
          nSpill )
    self.count += 4

  def writeToFile(self):
    incFile = open(self.fileName, "w")
    incFile.write( self.fileStr )
    incFile.write( "};\n" )
    incFile.write( "unsigned int numKernels = %d;\n" % self.count )
    incFile.close()



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
      listMicroTileSizes ):

    self.kernelSelectionFileName = precision.capitalize() + "gemmKernelSelection.h"
    self.listMicroTileSizes = listMicroTileSizes

    self.logic = (
      "#include \"" + precision.capitalize() + "gemmSourceIncludes.h\"\n"
      "#if USE_GEMM_KERNEL_BINARIES\n"
      "#include \"" + precision.capitalize() + "gemmBinaryIncludes.h\"\n"
      "#else\n"
      "#include \"" + precision.capitalize() + "gemmBinaryNulls.h\"\n"
      "#endif\n"
      "#include \"" + precision.capitalize() + "gemmKernelSourceBuildOptions.h\"\n"
      "#include \"" + precision.capitalize() + "gemmKernelBinaryBuildOptions.h\"\n"
      "#include \"" + precision.capitalize() + "gemmClKernels.h\"\n"
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
      "  const char **tileKernelSource,\n"
      "  const char **rowKernelSource,\n"
      "  const char **colKernelSource,\n"
      "  const char **cornerKernelSource,\n"
      "  const char **sourceBuildOptions,\n"
      "  const char **tileKernelBinary,\n"
      "  const char **rowKernelBinary,\n"
      "  const char **colKernelBinary,\n"
      "  const char **cornerKernelBinary,\n"
      "  const char **binaryBuildOptions,\n"
      "  cl_kernel  *tileClKernel,\n"
      "  cl_kernel  *rowClKernel,\n"
      "  cl_kernel  *colClKernel,\n"
      "  cl_kernel  *cornerClKernel,\n"
      "  unsigned int *workGroupNumRows,\n"
      "  unsigned int *workGroupNumCols,\n"
      "  unsigned int *microTileNumRows,\n"
      "  unsigned int *microTileNumCols,\n"
      "  unsigned int *unroll\n"
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
    self.logic += "if ( /*M%%%d == 0 && N%%%d == 0 &&*/ K%%%d == 0) {\n" % (kernel.getMultipleM(), kernel.getMultipleN(), kernel.getMultipleK())

    #self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    #self.logic += "printf(\"selected kernel: " + kernel.getKernelName() + "\\n\");\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*tileKernelSource   = " + kernel.getKernelName()       + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*rowKernelSource    = " + kernel.getRowKernelName()    + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*colKernelSource    = " + kernel.getColKernelName()    + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*cornerKernelSource = " + kernel.getCornerKernelName() + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*sourceBuildOptions = " + kernel.getKernelName() + "_srcBuildOptions;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*tileKernelBinary   = " + kernel.getKernelName()       + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*rowKernelBinary    = " + kernel.getRowKernelName()    + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*colKernelBinary    = " + kernel.getColKernelName()    + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*cornerKernelBinary = " + kernel.getCornerKernelName() + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*binaryBuildOptions = " + kernel.getKernelName() + "_binBuildOptions;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*tileClKernel       = " + kernel.getKernelName()       + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*rowClKernel        = " + kernel.getRowKernelName()    + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*colClKernel        = " + kernel.getColKernelName()    + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*cornerClKernel     = " + kernel.getCornerKernelName() + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*workGroupNumRows   = " + str(kernel.workGroupNumRows) + ";\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*workGroupNumCols   = " + str(kernel.workGroupNumCols) + ";\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*microTileNumRows   = " + str(kernel.microTileNumRows) + ";\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*microTileNumCols   = " + str(kernel.microTileNumCols) + ";\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*unroll             = " + str(kernel.unroll)           + ";\n"

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


#lA[ 0*localAStride ] = A[ GET_GLOBAL_INDEX_A( groupRow*MACRO_TILE_NUM_ROWS+(localSerial+0*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_ROWS, (localSerial+0*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_ROWS) ];
#lA[ 1*localAStride ] = A[ GET_GLOBAL_INDEX_A( groupRow*MACRO_TILE_NUM_ROWS+(localSerial+1*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_ROWS, (localSerial+1*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_ROWS) ];
#lA[ 2*localAStride ] = A[ GET_GLOBAL_INDEX_A( groupRow*MACRO_TILE_NUM_ROWS+(localSerial+2*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_ROWS, (localSerial+2*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_ROWS) ];
#lB[ 0*localBStride ] = B[ GET_GLOBAL_INDEX_B( (localSerial+0*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER, groupCol*MACRO_TILE_NUM_COLS+(localSerial+0*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER) ];
#lB[ 1*localBStride ] = B[ GET_GLOBAL_INDEX_B( (localSerial+1*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER, groupCol*MACRO_TILE_NUM_COLS+(localSerial+1*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER) ];
#lB[ 2*localBStride ] = B[ GET_GLOBAL_INDEX_B( (localSerial+2*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER, groupCol*MACRO_TILE_NUM_COLS+(localSerial+2*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER) ];
