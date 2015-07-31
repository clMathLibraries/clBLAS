import Common
import KernelParameters

kernelSelectionData = [
# prec, tile, fallback range, valid range
    ["s",
      [ [6, 6], [4096,   -1], [864,   -1] ],
      [ [2,10], [  -1,   -1], [800, 3040] ],
      [ [4, 4], [  48, 5424], [640,   -1] ],
      [ [2, 2], [  32, 1376], [288, 1952] ],
      [ [1, 1], [   0,  304], [ 16,  784] ],
      ],
    ["d",
      [ [6, 6], [4096,   -1], [864,   -1] ],
      [ [2,10], [  -1,   -1], [800, 3040] ],
      [ [4, 4], [  48, 5424], [640,   -1] ],
      [ [2, 2], [  32, 1376], [288, 1952] ],
      [ [1, 1], [   0,  304], [ 16,  784] ],
      ],
    ["c",
      [ [6, 6], [4096,   -1], [864,   -1] ],
      [ [2,10], [  -1,   -1], [800, 3040] ],
      [ [4, 4], [  48, 5424], [640,   -1] ],
      [ [2, 2], [  32, 1376], [288, 1952] ],
      [ [1, 1], [   0,  304], [ 16,  784] ],
      ],
    ["z",
      [ [6, 6], [4096,   -1], [864,   -1] ],
      [ [2,10], [  -1,   -1], [800, 3040] ],
      [ [4, 4], [  48, 5424], [640,   -1] ],
      [ [2, 2], [  32, 1376], [288, 1952] ],
      [ [1, 1], [   0,  304], [ 16,  784] ],
      ],
    ]

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
  #print "Range [%4ux%4u]: [%4u,%4u] is %s b/c" \
  #    % (rangeMin, rangeMax, tileMin, tileMax, "valid" if valid else "INVALID" )
  #print "if ( %i<0 or (%u >= %u and %u>0) and %u <= %u" \
  #    %( tileMax, tileMax, rangeMax, rangeMax, tileMin, rangeMin )
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
      unrollList, \
      kernelSelectionData):
    self.kernelSelectionFileName = Common.getOutputPath() + "GemmKernelSelection.h"

    self.logic = (
      "#include \"GemmSourceIncludes.h\"\n"
      "#if USE_GEMM_KERNEL_BINARIES\n"
      "#include \"GemmBinaryIncludes.h\"\n"
      "#else\n"
      "#include \"GemmBinaryNulls.h\"\n"
      "#endif\n"
      "#include \"GemmKernelSourceBuildOptions.h\"\n"
      "#include \"GemmKernelBinaryBuildOptions.h\"\n"
      "#include \"GemmClKernels.h\"\n"
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

    ####################################
    # precision
    kernel = KernelParameters.KernelParameters()
    for precision in precisionList:
      #print precision + "gemm"
      kernel.precision = precision
      tilesForPrecision = kernelSelectionData[precision]
      self.logic += (
          "// " + precision + "gemm kernel selection logic\n"
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
        #print precision + "gemm" + "_" + order
        kernel.order = order
        self.logic += indent(1) + "if (order == " + order + ") {\n"
        transList = transDict[precision]

        ####################################
        # transA
        for transA in transList:
          #print precision + "gemm" + "_" + order + "_" + transA
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
            #print precision + "gemm" + "_" + order + "_" + transA + "_" + transB
            kernel.transB = transB
            self.logic += indent(3) + "if (transB == "
            if transA == "N":
              self.logic += "clblasNoTrans"
            elif transA == "T":
              self.logic += "clblasTrans"
            else:
              self.logic += "clblasConjTrans"
            self.logic += ") {\n"

            ####################################
            # beta
            for beta in betaList:
              #print precision + "gemm" + "_" + order + "_" + transA + "_" + transB + "_B" + str(beta)
              kernel.beta = beta
              self.logic += indent(4) + "if ( "
              if beta == 0:
                self.logic += "!betaNonZero"
              else:
                self.logic += "betaNonZero"
              self.logic += " ) {\n"


              ####################################
              # list the size events
              sizeEvents = []
              for tileData in tilesForPrecision:
                fallbackRange = tileData[1]
                validRange = tileData[2]
                sizeEvents.append(fallbackRange[0])
                sizeEvents.append(fallbackRange[1])
                sizeEvents.append(validRange[0])
                sizeEvents.append(validRange[1])
              sizeEvents = list(set( sizeEvents )) # unique
              sizeEvents.sort(reverse=True) # largest to smallest
              sizeEvents.remove(-1)
              sizeEvents.insert(0, -1)
              print precision + "gemm sizeEvents: " + sizeEvents
              # remove -1 from beginiing of list and ? append to end

              ####################################
              # if size event
              numSizeEvents = len(sizeEvents)
              for eventIdx in range(0, numSizeEvents-1):
                sizeMax = sizeEvents[eventIdx]
                sizeMin = sizeEvents[eventIdx+1]
                self.logic += indent(5) + "if ( M*N >= " + str(sizeMin) + "*" + str(sizeMin)
                if sizeMax > 0:
                  self.logic += " && M*N <= " + str(sizeMax) + "*" + str(sizeMax)
                self.logic += ") {\n"
                #print precision + "gemm" + "_" + order + "_" + transA + "_" + transB + "_B" + str(beta) + "_" + str(sizeMin) + "->" + str(sizeMax)

                ####################################
                # valid tiles
                self.logic += indent(6)+"// valid tiles\n"
                #print "\nValid [%i, %i]"%(sizeMin, sizeMax)
                for tileData in tilesForPrecision:
                  tileParams = tileData[0]
                  #tileFallbackRange = tileData[1]
                  tileValidRange = tileData[2]
                  tileValidRangeMin = tileValidRange[0]
                  tileValidRangeMax = tileValidRange[1]
                  if tileInRange(tileValidRangeMin, tileValidRangeMax, sizeMin, sizeMax ):
                    # this tile is valid for this size range
                    kernel.workGroupNumRows = tileParams[0]
                    kernel.workGroupNumCols = tileParams[1]
                    kernel.microTileNumRows = tileParams[2]
                    kernel.microTileNumCols = tileParams[3]
                    kernel.macroTileNumRows = tileParams[0]*tileParams[2]
                    kernel.macroTileNumCols = tileParams[1]*tileParams[3]
                    for unroll in unrollList:
                      kernel.unroll = unroll
                      self.logic += indent(6)+"if ( M%%%d == 0 && N%%%d == 0 && K%%%d == 0) {\n" \
                          % (kernel.getMultipleM(), kernel.getMultipleN(), kernel.getMultipleK())
                      self.addBodyForKernel( kernel )
                      self.logic += indent(6) + "}\n"

                ####################################
                # fallback tile - TODO all tiles begin added
                self.logic += indent(6)+"// fallback tile\n"
                #print "\nFallback[%i, %i]"%(sizeMin, sizeMax)
                for tileData in tilesForPrecision:
                  tileParams = tileData[0]
                  tileFallbackRange = tileData[1]
                  #tileValidRange = tileData[2]
                  tileFallbackRangeMin = tileFallbackRange[0]
                  tileFallbackRangeMax = tileFallbackRange[1]
                  if tileInRange(tileFallbackRangeMin, tileFallbackRangeMax, sizeMin, sizeMax):
                    # this is the fallback tile
                    kernel.workGroupNumRows = tileParams[0]
                    kernel.workGroupNumCols = tileParams[1]
                    kernel.microTileNumRows = tileParams[2]
                    kernel.microTileNumRows = tileParams[3]
                    kernel.macroTileNumRows = tileParams[0]*tileParams[2]
                    kernel.macroTileNumCols = tileParams[1]*tileParams[3]
                    for unroll in unrollList:
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



  def addBodyForKernel( self, kernel ):
    #self.logic += indent(7) + "printf(\"selected kernel: " + kernel.getName() + "\\n\");\n"
    self.logic += indent(7) + "*tileKernelSource   = " + kernel.getName()       + "_src;\n"
    self.logic += indent(7) + "*rowKernelSource    = " + kernel.getRowName()    + "_src;\n"
    self.logic += indent(7) + "*colKernelSource    = " + kernel.getColName()    + "_src;\n"
    self.logic += indent(7) + "*cornerKernelSource = " + kernel.getCornerName() + "_src;\n"
    self.logic += indent(7) + "*sourceBuildOptions = " + kernel.getName() + "_srcBuildOptions;\n"
    self.logic += indent(7) + "*tileKernelBinary   = " + kernel.getName()       + "_bin;\n"
    self.logic += indent(7) + "*rowKernelBinary    = " + kernel.getRowName()    + "_bin;\n"
    self.logic += indent(7) + "*colKernelBinary    = " + kernel.getColName()    + "_bin;\n"
    self.logic += indent(7) + "*cornerKernelBinary = " + kernel.getCornerName() + "_bin;\n"
    self.logic += indent(7) + "*binaryBuildOptions = " + kernel.getName() + "_binBuildOptions;\n"
    self.logic += indent(7) + "*tileClKernel       = &" + kernel.getName()       + "_clKernel;\n"
    self.logic += indent(7) + "*rowClKernel        = &" + kernel.getRowName()    + "_clKernel;\n"
    self.logic += indent(7) + "*colClKernel        = &" + kernel.getColName()    + "_clKernel;\n"
    self.logic += indent(7) + "*cornerClKernel     = &" + kernel.getCornerName() + "_clKernel;\n"
    self.logic += indent(7) + "*workGroupNumRows   = " + str(kernel.workGroupNumRows) + ";\n"
    self.logic += indent(7) + "*workGroupNumCols   = " + str(kernel.workGroupNumCols) + ";\n"
    self.logic += indent(7) + "*microTileNumRows   = " + str(kernel.microTileNumRows) + ";\n"
    self.logic += indent(7) + "*microTileNumCols   = " + str(kernel.microTileNumCols) + ";\n"
    self.logic += indent(7) + "*unroll             = " + str(kernel.unroll)           + ";\n"
    self.logic += indent(7) + "return;\n"



  ##############################################################################
  # KSL - write to file
  ##############################################################################
  def writeToFile(self):
    selectionFile = open(self.kernelSelectionFileName, "w")
    selectionFile.write( Common.getAutoGemmHeader() )
    selectionFile.write(self.logic)
    selectionFile.write("\n")
    selectionFile.close()




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

    self.kernelSelectionFileName = Common.getOutputPath() + "GemmKernelSelectionSpecific.h"

    self.logic = (
      "#include \"GemmSourceIncludes.h\"\n"
      "#if USE_GEMM_KERNEL_BINARIES\n"
      "#include \"GemmBinaryIncludes.h\"\n"
      "#else\n"
      "#include \"GemmBinaryNulls.h\"\n"
      "#endif\n"
      "#include \"GemmKernelSourceBuildOptions.h\"\n"
      "#include \"GemmKernelBinaryBuildOptions.h\"\n"
      "#include \"GemmClKernels.h\"\n"
      "\n"
      "// kernel selection specific template\n"
      "template<typename Precision>\n"
      "bool gemmSelectKernelSpecific(\n"
      "  clblasOrder order,\n"
      "  clblasTranspose transA,\n"
      "  clblasTranspose transB,\n"
      "  bool betaNonZero,\n"
      "  unsigned int workGroupNumRows,\n"
      "  unsigned int workGroupNumCols,\n"
      "  unsigned int microTileNumRows,\n"
      "  unsigned int microTileNumCols,\n"
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
      "  const char **binaryBuildOptions,\n"
      "  cl_kernel  **tileClKernel,\n"
      "  cl_kernel  **rowClKernel,\n"
      "  cl_kernel  **colClKernel,\n"
      "  cl_kernel  **cornerClKernel\n"
      ");\n\n" )
    self.precisionInitialized = False
    self.orderInitialized = False
    self.transInitialized = False
    self.betaInitialized = False

  def newPrecision(self, precision ):
    if self.precisionInitialized:
      self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
      self.logic += self.zeroIndent+self.tab + "}\n" # 1 tab
      self.logic += self.zeroIndent+"}\n"
      self.logic += self.zeroIndent + "return false; // didn't find a match\n"
      self.logic += "}\n\n"
    else:
      self.logic += self.zeroIndent

    self.logic += (
      "// " + precision + "gemm kernel selection specific\n"
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
      "  unsigned int workGroupNumRows,\n"
      "  unsigned int workGroupNumCols,\n"
      "  unsigned int microTileNumRows,\n"
      "  unsigned int microTileNumCols,\n"
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
      "  const char **binaryBuildOptions,\n"
      "  cl_kernel  **tileClKernel,\n"
      "  cl_kernel  **rowClKernel,\n"
      "  cl_kernel  **colClKernel,\n"
      "  cl_kernel  **cornerClKernel\n"
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
    self.logic += ("if ( workGroupNumRows == %u && workGroupNumCols == %u "
        "&& microTileNumRows == %u && microTileNumCols == %u "
        "&& unroll == %u) {\n") \
        % (kernel.workGroupNumRows, kernel.workGroupNumCols, \
        kernel.microTileNumRows, kernel.microTileNumCols, kernel.unroll )

    #self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    #self.logic += "printf(\"selected kernel: " + kernel.getName() + "\\n\");\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*tileKernelSource   = " + kernel.getName()       + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*rowKernelSource    = " + kernel.getRowName()    + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*colKernelSource    = " + kernel.getColName()    + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*cornerKernelSource = " + kernel.getCornerName() + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*sourceBuildOptions = " + kernel.getName() + "_srcBuildOptions;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*tileKernelBinary   = " + kernel.getName()       + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*rowKernelBinary    = " + kernel.getRowName()    + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*colKernelBinary    = " + kernel.getColName()    + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*cornerKernelBinary = " + kernel.getCornerName() + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*binaryBuildOptions = " + kernel.getName() + "_binBuildOptions;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*tileClKernel       = &" + kernel.getName()       + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*rowClKernel        = &" + kernel.getRowName()    + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*colClKernel        = &" + kernel.getColName()    + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "*cornerClKernel     = &" + kernel.getCornerName() + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab # 4 tabs
    self.logic += "return true;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab # 3 tabs
    self.logic += "}\n"


  ##############################################################################
  # KSL - write to file
  ##############################################################################
  def writeToFile(self):
    self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
    self.logic += self.zeroIndent+self.tab + "}\n" # 1 tab
    self.logic += self.zeroIndent + "}\n" # 0 tab
    self.logic += self.zeroIndent + "return false; // didn't find a match\n"
    self.logic += "}\n" # close function

    selectionFile = open(self.kernelSelectionFileName, "w")
    selectionFile.write( Common.getAutoGemmHeader() )
    selectionFile.write(self.logic)
    selectionFile.write("\n")
    selectionFile.close()

