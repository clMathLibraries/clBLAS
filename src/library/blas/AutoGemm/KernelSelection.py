import os
import sys
import copy

import AutoGemmParameters
import Common
import KernelParameters

def indent(il):
  returnTabs = ""
  for i in range(0, il):
    returnTabs += "  "
  return returnTabs

def tileInRange( tileMin, tileMax, rangeMin, rangeMax):
  if ( tileMax < 0 or (tileMax >= rangeMax and rangeMax>0) ) and tileMin <= rangeMin :
    valid = True
  else:
    valid = False
  #print("Range [%4ux%4u]: [%4u,%4u] is %s b/c" \
  #    % (rangeMin, rangeMax, tileMin, tileMax, "valid" if valid else "INVALID" ))
  #print("if ( %i<0 or (%u >= %u and %u>0) and %u <= %u" \
  #    %( tileMax, tileMax, rangeMax, rangeMax, tileMin, rangeMin ))
  return valid


################################################################################
# KSL - Kernel Selection Logic File
################################################################################
class KernelSelection:



  ##############################################################################
  # KSL - default constructor
  ##############################################################################
  def __init__( \
      self, \
      precisionList, \
      orderList, \
      transDict, \
      betaList, \
      unrollDict, \
      kernelSelectionData):

    self.incFileName = Common.getIncludePath() + "AutoGemmKernelSelection.h"
    self.incFile = open(self.incFileName, "w")
    self.incFile.write( Common.getAutoGemmHeader() )

    self.kernelSelectionFileName = Common.getIncludePath() + "AutoGemmKernelSelection.cpp"
    self.selectionFile = open(self.kernelSelectionFileName, "w")
    self.selectionFile.write( Common.getAutoGemmHeader() )


    self.inc = (
      "#include <clBLAS.h>\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelSources.h\"\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelBinaries.h\"\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelBuildOptionsSource.h\"\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelBuildOptionsBinary.h\"\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmClKernels.h\"\n"
      "\n"
      "#define EXACT_MULTIPLES(MULTIPLE_STR) MULTIPLE_STR\n"
      "\n"
      "// kernel selection logic template\n"
      "template<typename Precision>\n"
      "void gemmSelectKernel(\n"
      "  clblasOrder order,\n"
      "  clblasTranspose transA,\n"
      "  clblasTranspose transB,\n"
      "  size_t M,\n"
      "  size_t N,\n"
      "  size_t K,\n"
      "  bool betaNonZero,\n"
      "  float optimalNumElementsPerWorkItem,\n"
      "  const char **tileKernelSource,\n"
      "  const char **rowKernelSource,\n"
      "  const char **colKernelSource,\n"
      "  const char **cornerKernelSource,\n"
      "  const char **sourceBuildOptions,\n"
      "  const unsigned char **tileKernelBinary,\n"
      "  const unsigned char **rowKernelBinary,\n"
      "  const unsigned char **colKernelBinary,\n"
      "  const unsigned char **cornerKernelBinary,\n"
      "  size_t **tileKernelBinarySize,\n"
      "  size_t **rowKernelBinarySize,\n"
      "  size_t **colKernelBinarySize,\n"
      "  size_t **cornerKernelBinarySize,\n"
      "  const char **binaryBuildOptions,\n"
      "  cl_kernel  **tileClKernel,\n"
      "  cl_kernel  **rowClKernel,\n"
      "  cl_kernel  **colClKernel,\n"
      "  cl_kernel  **cornerClKernel,\n"
      "  unsigned int *workGroupNumRows,\n"
      "  unsigned int *workGroupNumCols,\n"
      "  unsigned int *microTileNumRows,\n"
      "  unsigned int *microTileNumCols,\n"
      "  unsigned int *unroll\n"
      ");\n\n" )

    self.logic = "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelSelection.h\"\n"

    ####################################
    # precision
    kernel = KernelParameters.KernelParameters()
    for precision in precisionList:
      #self.selectionFile.write( self.logic )
      #self.logic = ""
      kernel.precision = precision
      sizeEvents = kernelSelectionData[precision]
      self.logic += (
          "\n// " + precision + "gemm kernel selection logic\n"
          "template<>\n"
          "void gemmSelectKernel<" )
      if precision == "s":
        self.logic += "float"
      elif precision == "d":
        self.logic += "double"
      elif precision == "c":
        self.logic += "FloatComplex"
      else:
        self.logic += "DoubleComplex"

      self.logic += (
          ">(\n"
          "  clblasOrder order,\n"
          "  clblasTranspose transA,\n"
          "  clblasTranspose transB,\n"
          "  size_t M,\n"
          "  size_t N,\n"
          "  size_t K,\n"
          "  bool betaNonZero,\n"
          "  float optimalNumElementsPerWorkItem,\n"
          "  const char **tileKernelSource,\n"
          "  const char **rowKernelSource,\n"
          "  const char **colKernelSource,\n"
          "  const char **cornerKernelSource,\n"
          "  const char **sourceBuildOptions,\n"
          "  const unsigned char **tileKernelBinary,\n"
          "  const unsigned char **rowKernelBinary,\n"
          "  const unsigned char **colKernelBinary,\n"
          "  const unsigned char **cornerKernelBinary,\n"
          "  size_t **tileKernelBinarySize,\n"
          "  size_t **rowKernelBinarySize,\n"
          "  size_t **colKernelBinarySize,\n"
          "  size_t **cornerKernelBinarySize,\n"
          "  const char **binaryBuildOptions,\n"
          "  cl_kernel  **tileClKernel,\n"
          "  cl_kernel  **rowClKernel,\n"
          "  cl_kernel  **colClKernel,\n"
          "  cl_kernel  **cornerClKernel,\n"
          "  unsigned int *workGroupNumRows,\n"
          "  unsigned int *workGroupNumCols,\n"
          "  unsigned int *microTileNumRows,\n"
          "  unsigned int *microTileNumCols,\n"
          "  unsigned int *unroll\n"
          ") {\n" )

      ####################################
      # order
      for order in orderList:
        #print(precision + "gemm" + "_" + order)
        kernel.order = order
        self.logic += indent(1) + "if (order == " + order + ") {\n"
        transList = transDict[precision]

        ####################################
        # transA
        for transA in transList:
          #print(precision + "gemm" + "_" + order + "_" + transA)
          kernel.transA = transA
          self.logic += indent(2) + "if (transA == "
          if transA == "N":
            self.logic += "clblasNoTrans"
          elif transA == "T":
            self.logic += "clblasTrans"
          else:
            self.logic += "clblasConjTrans"
          self.logic += ") {\n"

          ####################################
          # transB
          for transB in transList:
            kernel.transB = transB
            self.logic += indent(3) + "if (transB == "
            if transB == "N":
              self.logic += "clblasNoTrans"
            elif transB == "T":
              self.logic += "clblasTrans"
            else:
              self.logic += "clblasConjTrans"
            self.logic += ") {\n"

            ####################################
            # beta
            for beta in betaList:
              #print(precision + "gemm" + "_" + order + "_" + transA + "_" + transB + "_B" + str(beta))
              kernel.beta = beta
              self.logic += indent(4) + "if ( "
              if beta == 0:
                self.logic += "!betaNonZero"
              else:
                self.logic += "betaNonZero"
              self.logic += " ) {\n"

              ####################################
              # if size event
              for sizeEvent in sizeEvents:
                self.selectionFile.write( self.logic )
                self.logic = ""
                sizeMin = sizeEvent[0]
                fallbackTile = sizeEvent[1]
                validTiles = sizeEvent[2]
                self.logic += indent(5)+"if ( M*N >= "+str(sizeMin)+"*"+str(sizeMin) + ") {\n"
                #print(precision + "gemm" + "_" + order + "_" + transA + "_" + transB + "_B" + str(beta) + "_" + str(sizeMin) + "->" + str(sizeMax))

                ####################################
                # valid tiles
                self.logic += indent(6)+"// valid tiles\n"
                for tileParams in validTiles:
                  kernel.workGroupNumRows = tileParams[0]
                  kernel.workGroupNumCols = tileParams[1]
                  kernel.microTileNumRows = tileParams[2]
                  kernel.microTileNumCols = tileParams[3]
                  kernel.macroTileNumRows = kernel.workGroupNumRows*kernel.microTileNumRows
                  kernel.macroTileNumCols = kernel.workGroupNumCols*kernel.microTileNumCols
                  for unroll in unrollDict[precision]:
                    kernel.unroll = unroll
                    self.logic += indent(6)+"if ( M%%%d == 0 && N%%%d == 0 && K%%%d == 0) {\n" \
                        % (kernel.getMultipleM(), kernel.getMultipleN(), kernel.getMultipleK())
                    self.addBodyForKernel( kernel )
                    self.logic += indent(6) + "}\n"

                ####################################
                # fallback tile - TODO all tiles begin added
                self.logic += indent(6)+"// fallback tile\n"
                #print("\nFallback[%i, %i]"%(sizeMin, sizeMax))
                kernel.workGroupNumRows = fallbackTile[0]
                kernel.workGroupNumCols = fallbackTile[1]
                kernel.microTileNumRows = fallbackTile[2]
                kernel.microTileNumCols = fallbackTile[3]
                kernel.macroTileNumRows = kernel.workGroupNumRows*kernel.microTileNumRows
                kernel.macroTileNumCols = kernel.workGroupNumCols*kernel.microTileNumCols
                for unroll in unrollDict[precision]:
                  kernel.unroll = unroll
                  self.logic += indent(6)+"if ( K%%%d == 0 ) {\n" \
                      % (kernel.getMultipleK())
                  self.addBodyForKernel( kernel )
                  self.logic += indent(6) + "}\n"

                ####################################
                # end size event
                self.logic += indent(5) + "} // end size\n"

              ####################################
              # end beta
              self.logic += indent(4) + "} // end beta\n"

            ####################################
            # end transB
            self.logic += indent(3) + "} // end transB\n"

          ####################################
          # end transA
          self.logic += indent(2) + "} // end transA\n"

        ####################################
        # end order
        self.logic += indent(1) + "} // end order\n"

      ####################################
      # end precision
      self.logic += indent(0) + "} // end precision function\n"
    # write last precision
    self.selectionFile.write( self.logic )
    self.selectionFile.write( "\n" )



  def addBodyForKernel( self, kernel ):
    #self.logic += indent(7) + "printf(\"selected kernel: " + kernel.getName() + "\\n\");\n"
    self.logic += indent(7) + "*tileKernelSource       =  " + kernel.getName()       + "_src;\n"
    self.logic += indent(7) + "*rowKernelSource        =  " + kernel.getRowName()    + "_src;\n"
    self.logic += indent(7) + "*colKernelSource        =  " + kernel.getColName()    + "_src;\n"
    self.logic += indent(7) + "*cornerKernelSource     =  " + kernel.getCornerName() + "_src;\n"
    self.logic += indent(7) + "*sourceBuildOptions     =  " + kernel.getName()       + "_srcBuildOptions;\n"
    self.logic += indent(7) + "*tileKernelBinary       =  " + kernel.getName()       + "_bin;\n"
    self.logic += indent(7) + "*rowKernelBinary        =  " + kernel.getRowName()    + "_bin;\n"
    self.logic += indent(7) + "*colKernelBinary        =  " + kernel.getColName()    + "_bin;\n"
    self.logic += indent(7) + "*cornerKernelBinary     =  " + kernel.getCornerName() + "_bin;\n"
    self.logic += indent(7) + "*tileKernelBinarySize   = &" + kernel.getName()       + "_binSize;\n"
    self.logic += indent(7) + "*rowKernelBinarySize    = &" + kernel.getRowName()    + "_binSize;\n"
    self.logic += indent(7) + "*colKernelBinarySize    = &" + kernel.getColName()    + "_binSize;\n"
    self.logic += indent(7) + "*cornerKernelBinarySize = &" + kernel.getCornerName() + "_binSize;\n"
    self.logic += indent(7) + "*binaryBuildOptions     =  " + kernel.getName()       + "_binBuildOptions;\n"
    self.logic += indent(7) + "*tileClKernel           = &" + kernel.getName()       + "_clKernel;\n"
    self.logic += indent(7) + "*rowClKernel            = &" + kernel.getRowName()    + "_clKernel;\n"
    self.logic += indent(7) + "*colClKernel            = &" + kernel.getColName()    + "_clKernel;\n"
    self.logic += indent(7) + "*cornerClKernel         = &" + kernel.getCornerName() + "_clKernel;\n"
    self.logic += indent(7) + "*workGroupNumRows       =  " + kernel.getName()       + "_workGroupNumRows;\n"
    self.logic += indent(7) + "*workGroupNumCols       =  " + kernel.getName()       + "_workGroupNumCols;\n"
    self.logic += indent(7) + "*microTileNumRows       =  " + kernel.getName()       + "_microTileNumRows;\n"
    self.logic += indent(7) + "*microTileNumCols       =  " + kernel.getName()       + "_microTileNumRows;\n"
    self.logic += indent(7) + "*unroll                 =  " + kernel.getName()       + "_unroll;\n"
    self.logic += indent(7) + "return;\n"



  ##############################################################################
  # KSL - write to file
  ##############################################################################
  def writeToFile(self):
    self.selectionFile.close()

    self.incFile.write( self.inc )
    self.incFile.close()




################################################################################
# KSM - Kernel Selection Manual/Specific File
################################################################################
class KernelSelectionSpecific:

  zeroIndent = "  "
  tab = "  "
  ##############################################################################
  # KSL - default constructor
  ##############################################################################
  def __init__(self):

    self.incFileName = Common.getIncludePath() + "AutoGemmKernelSelectionSpecific.h"
    self.incFile = open(self.incFileName, "w")
    self.incFile.write( Common.getAutoGemmHeader() )

    self.kernelSelectionFileName = Common.getIncludePath() + "AutoGemmKernelSelectionSpecific.cpp"
    self.selectionFile = open(self.kernelSelectionFileName, "w")
    self.selectionFile.write( Common.getAutoGemmHeader() )

    self.inc = (
      "#include <clBLAS.h>\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelSources.h\"\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelBinaries.h\"\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelBuildOptionsSource.h\"\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelBuildOptionsBinary.h\"\n"
      "#include \"" + Common.getRelativeIncludePath() + "AutoGemmClKernels.h\"\n"
      "\n"
      "// kernel selection specific template\n"
      "template<typename Precision>\n"
      "bool gemmSelectKernelSpecific(\n"
      "  clblasOrder order,\n"
      "  clblasTranspose transA,\n"
      "  clblasTranspose transB,\n"
      "  bool betaNonZero,\n"
      "  unsigned int macroTileNumRows,\n"
      "  unsigned int macroTileNumCols,\n"
      "  unsigned int unroll,\n"
      "  const char **tileKernelSource,\n"
      "  const char **rowKernelSource,\n"
      "  const char **colKernelSource,\n"
      "  const char **cornerKernelSource,\n"
      "  const char **sourceBuildOptions,\n"
      "  const unsigned char **tileKernelBinary,\n"
      "  const unsigned char **rowKernelBinary,\n"
      "  const unsigned char **colKernelBinary,\n"
      "  const unsigned char **cornerKernelBinary,\n"
      "  size_t **tileKernelBinarySize,\n"
      "  size_t **rowKernelBinarySize,\n"
      "  size_t **colKernelBinarySize,\n"
      "  size_t **cornerKernelBinarySize,\n"
      "  const char **binaryBuildOptions,\n"
      "  cl_kernel  **tileClKernel,\n"
      "  cl_kernel  **rowClKernel,\n"
      "  cl_kernel  **colClKernel,\n"
      "  cl_kernel  **cornerClKernel,\n"
      "  unsigned int *workGroupNumRows,\n"
      "  unsigned int *workGroupNumCols,\n"
      "  unsigned int *microTileNumRows,\n"
      "  unsigned int *microTileNumCols\n"
      ");\n\n" )

    self.logic = "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelSelectionSpecific.h\"\n"
    self.precisionInitialized = False
    self.orderInitialized = False
    self.transInitialized = False
    self.betaInitialized = False

  def newPrecision(self, precision ):
    #print("KernelSelectionSpecific: " + precision + "gemm")
    if self.precisionInitialized:
      self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
      self.logic += self.zeroIndent+self.tab + "}\n" # 1 tab
      self.logic += self.zeroIndent+"}\n"
      self.logic += self.zeroIndent + "return false; // didn't find a match\n"
      self.logic += "}\n\n"
    else:
      self.logic += self.zeroIndent

    self.logic += (
      "\n// " + precision + "gemm kernel selection specific\n"
      "template<>\n"
      "bool gemmSelectKernelSpecific<" )
    if precision == "s":
      self.logic += "float"
    elif precision == "d":
      self.logic += "double"
    elif precision == "c":
      self.logic += "FloatComplex"
    else:
      self.logic += "DoubleComplex"

    self.logic += (
      ">(\n"
      "  clblasOrder order,\n"
      "  clblasTranspose transA,\n"
      "  clblasTranspose transB,\n"
      "  bool betaNonZero,\n"
      "  unsigned int macroTileNumRows,\n"
      "  unsigned int macroTileNumCols,\n"
      "  unsigned int unroll,\n"
      "  const char **tileKernelSource,\n"
      "  const char **rowKernelSource,\n"
      "  const char **colKernelSource,\n"
      "  const char **cornerKernelSource,\n"
      "  const char **sourceBuildOptions,\n"
      "  const unsigned char **tileKernelBinary,\n"
      "  const unsigned char **rowKernelBinary,\n"
      "  const unsigned char **colKernelBinary,\n"
      "  const unsigned char **cornerKernelBinary,\n"
      "  size_t **tileKernelBinarySize,\n"
      "  size_t **rowKernelBinarySize,\n"
      "  size_t **colKernelBinarySize,\n"
      "  size_t **cornerKernelBinarySize,\n"
      "  const char **binaryBuildOptions,\n"
      "  cl_kernel  **tileClKernel,\n"
      "  cl_kernel  **rowClKernel,\n"
      "  cl_kernel  **colClKernel,\n"
      "  cl_kernel  **cornerClKernel,\n"
      "  unsigned int *workGroupNumRows,\n"
      "  unsigned int *workGroupNumCols,\n"
      "  unsigned int *microTileNumRows,\n"
      "  unsigned int *microTileNumCols\n"
      ") {\n" )
    self.precisionInitialized = True
    self.orderInitialized = False
    self.transInitialized = False
    self.betaInitialized = False


  ####################################
  # KSL - new order
  def newOrder(self, order):
    if (self.orderInitialized):
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


  ####################################
  # KSL - new trans
  def newTrans(self, transA, transB):
    if (self.transInitialized):
      self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
      self.logic += self.zeroIndent+self.tab # 1 tab
      self.logic += "} else "
    else:
      self.logic += self.zeroIndent+self.tab # 1 tabs
    self.logic += "if (transA == "
    if transA == "N":
      self.logic += "clblasNoTrans"
    elif transA == "T":
      self.logic += "clblasTrans"
    else:
      self.logic += "clblasConjTrans"
    self.logic += " && transB == "
    if transB == "N":
      self.logic += "clblasNoTrans"
    elif transB == "T":
      self.logic += "clblasTrans"
    else:
      self.logic += "clblasConjTrans"
    self.logic += ") {\n"
    self.transInitialized = True
    self.betaInitialized = False

  ####################################
  # KSL - new beta
  def newBeta(self, beta):
    if (self.betaInitialized):
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


  ##############################################################################
  # KSL - add new kernel
  ##############################################################################
  def newKernel(self, kernel):

    # new kernel
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab # 3 tabs
    self.logic += ("if ( macroTileNumRows == %u && macroTileNumCols == %u "
        "&& unroll == %u) {\n") \
        % ( kernel.macroTileNumRows, kernel.macroTileNumCols, kernel.unroll )

    #self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    #self.logic += "printf(\"selected kernel: " + kernel.getName() + "\\n\");\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*tileKernelSource   =  " + kernel.getName()       + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*rowKernelSource    =  " + kernel.getRowName()    + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*colKernelSource    =  " + kernel.getColName()    + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*cornerKernelSource =  " + kernel.getCornerName() + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*sourceBuildOptions =  " + kernel.getName() + "_srcBuildOptions;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*tileKernelBinary   =  " + kernel.getName()       + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*rowKernelBinary    =  " + kernel.getRowName()    + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*colKernelBinary    =  " + kernel.getColName()    + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*cornerKernelBinary =  " + kernel.getCornerName() + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*tileKernelBinarySize   = &" + kernel.getName()       + "_binSize;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*rowKernelBinarySize    = &" + kernel.getRowName()    + "_binSize;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*colKernelBinarySize    = &" + kernel.getColName()    + "_binSize;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*cornerKernelBinarySize = &" + kernel.getCornerName() + "_binSize;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*binaryBuildOptions =  " + kernel.getName() + "_binBuildOptions;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*tileClKernel       = &" + kernel.getName()       + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*rowClKernel        = &" + kernel.getRowName()    + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*colClKernel        = &" + kernel.getColName()    + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*cornerClKernel     = &" + kernel.getCornerName() + "_clKernel;\n"
    # dims
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*workGroupNumRows   =  " + kernel.getName() + "_workGroupNumRows;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*workGroupNumCols   =  " + kernel.getName() + "_workGroupNumCols;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*microTileNumRows   =  " + kernel.getName() + "_microTileNumRows;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*microTileNumCols   =  " + kernel.getName() + "_microTileNumCols;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "return true;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab # 3 tabs
    self.logic += "}\n"

    self.selectionFile.write( self.logic )
    self.logic = ""


  ##############################################################################
  # KSL - write to file
  ##############################################################################
  def writeToFile(self):
    self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
    self.logic += self.zeroIndent+self.tab + "}\n" # 1 tab
    self.logic += self.zeroIndent + "}\n" # 0 tab
    self.logic += self.zeroIndent + "return false; // didn't find a match\n"
    self.logic += "}\n" # close function

    self.selectionFile.write(self.logic)
    self.selectionFile.write("\n")
    self.selectionFile.close()

    self.incFile.write(self.inc)
    self.incFile.write("\n")
    self.incFile.close()


################################################################################
# Main
################################################################################
def writeKernelSelection():
  print("AutoGemm.py: Generating kernel selection.")
  if not os.path.exists( Common.getIncludePath() ):
    os.makedirs( Common.getIncludePath() )

  ########################################
  # kernel selection specific
  kss = KernelSelectionSpecific()

  # for each precision
  kernel = KernelParameters.KernelParameters()
  for precision in AutoGemmParameters.precisions:
    kernel.precision = precision
    kss.newPrecision(precision)

    # valid tiles for this precision
    tiles = AutoGemmParameters.getTilesForPrecision(precision)

    # for non tile parameters
    for order in AutoGemmParameters.orders:
      kernel.order = order
      kss.newOrder(order)
      for transA in AutoGemmParameters.transposes[precision]:
        kernel.transA = transA
        for transB in AutoGemmParameters.transposes[precision]:
          kernel.transB = transB
          kss.newTrans(transA, transB)
          for beta in AutoGemmParameters.betas:
            kernel.beta = beta
            kss.newBeta(beta)

            # for tile parameters
            for tile in tiles:
              kernel.useTile(tile)
              kss.newKernel(kernel)

  kss.writeToFile()

  ########################################
  # kernel selection
  ks = KernelSelection( \
      AutoGemmParameters.precisions, \
      AutoGemmParameters.orders, \
      AutoGemmParameters.transposes, \
      AutoGemmParameters.betas, \
      AutoGemmParameters.unrolls, \
      AutoGemmParameters.kernelSelectionData )
  ks.writeToFile()



################################################################################
# Main
################################################################################
if __name__ == "__main__":
  if len(sys.argv) == 3:
    Common.setOutputPath(sys.argv[1])
    AutoGemmParameters.setArchitecture(sys.argv[2])
    writeKernelSelection()
  else:
    print("USAGE: python KernelSelection.py output_path architecture")
