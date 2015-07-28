import Common
import KernelParameters

################################################################################
# KSL - Kernel Selection Logic File
################################################################################
class KernelSelection:

  zeroIndent = "  "
  tab = "  "
  ##############################################################################
  # KSL - default constructor
  ##############################################################################
  def __init__(self):

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
    self.precisionInitialized = False
    self.orderInitialized = False
    self.transInitialized = False
    self.betaInitialized = False
    self.previousTileSize = 0

  def newPrecision(self, precision, listMicroTileSizes ):
    self.listMicroTileSizes = listMicroTileSizes
    if self.precisionInitialized:
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab + "}\n" # 3 tabs
      self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
      self.logic += self.zeroIndent+self.tab + "}\n" # 1 tab
      self.logic += self.zeroIndent+"}\n"
      self.logic += "}\n\n"
    else:
      self.logic += self.zeroIndent

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
    self.precisionInitialized = True
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
  def newTrans(self, transA, transB):
    if (self.transInitialized):
      self.logic += self.zeroIndent+self.tab+self.tab+self.tab + "}\n" # 3 tabs
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
    self.logic += "if ( EXACT_MULTIPLES(M%%%d == 0 && N%%%d == 0 &&) K%%%d == 0) {\n" \
        % (kernel.getMultipleM(), kernel.getMultipleN(), kernel.getMultipleK())

    #self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    #self.logic += "printf(\"selected kernel: " + kernel.getName() + "\\n\");\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*tileKernelSource   = " + kernel.getName()       + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*rowKernelSource    = " + kernel.getRowName()    + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*colKernelSource    = " + kernel.getColName()    + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*cornerKernelSource = " + kernel.getCornerName() + "_src;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*sourceBuildOptions = " + kernel.getName() + "_srcBuildOptions;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*tileKernelBinary   = " + kernel.getName()       + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*rowKernelBinary    = " + kernel.getRowName()    + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*colKernelBinary    = " + kernel.getColName()    + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*cornerKernelBinary = " + kernel.getCornerName() + "_bin;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*binaryBuildOptions = " + kernel.getName() + "_binBuildOptions;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*tileClKernel       = &" + kernel.getName()       + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*rowClKernel        = &" + kernel.getRowName()    + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*colClKernel        = &" + kernel.getColName()    + "_clKernel;\n"

    self.logic += self.zeroIndent+self.tab+self.tab+self.tab+self.tab+self.tab # 5 tabs
    self.logic += "*cornerClKernel     = &" + kernel.getCornerName() + "_clKernel;\n"

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



  ##############################################################################
  # KSL - write to file
  ##############################################################################
  def writeToFile(self):
    self.logic += self.zeroIndent+self.tab+self.tab+self.tab + "}\n" # 3 tabs
    self.logic += self.zeroIndent+self.tab+self.tab + "}\n" # 2 tabs
    self.logic += self.zeroIndent+self.tab + "}\n" # 1 tab
    self.logic += self.zeroIndent + "}\n" # 0 tab
    self.logic += "}\n" # close function

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
      "  cl_kernel  **cornerClKernel,\n"
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
      "  size_t M,\n"
      "  size_t N,\n"
      "  size_t K,\n"
      "  bool betaNonZero,\n"
      "  unsigned int workGroupNumRows,\n"
      "  unsigned int workGroupNumCols,\n"
      "  unsigned int microTileNumRows,\n"
      "  unsigned int microTileNumCols,\n"
      "  unsigned int unroll\n"
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

