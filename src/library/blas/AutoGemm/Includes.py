import os
import sys
import getopt
import Common
import AutoGemmParameters
import KernelParameters

################################################################################
# SINC - Kernel Source Includes
################################################################################
class KernelSourceIncludes:

  ##############################################################################
  # SINC - default constructor
  ##############################################################################
  def __init__(self):
    self.incFileName = Common.getIncludePath() + "AutoGemmKernelSources.h"
    self.incFile = open(self.incFileName, "w")
    self.incFile.write( Common.getAutoGemmHeader() )
    self.incStr = "#ifndef AUTOGEMM_KERNEL_SOURCE_INCLUDES_H\n"
    self.incStr += "#define AUTOGEMM_KERNEL_SOURCE_INCLUDES_H\n"
    self.incStr += "\n"

    self.cppFileName = Common.getIncludePath() + "AutoGemmKernelSources.cpp"
    self.cppFile = open(self.cppFileName, "w")
    self.cppFile.write( Common.getAutoGemmHeader() )
    self.cppStr  = "\n"
    self.cppStr += "#include \"%sAutoGemmKernelSources.h\"\n" % Common.getRelativeIncludePath()
    self.cppStr += "#include \"UserGemmKernelSources/UserGemmKernelSourceIncludes.cpp\"\n"
	#self.cppStr += "#include \"UserGemmKernelSources/UserGemmKernelSources.cpp\"\n"

  def addKernel(self, kernel):
    kernelName = kernel.getName()
    self.incStr += "extern const unsigned int %s_workGroupNumRows;\n" % kernelName
    self.incStr += "extern const unsigned int %s_workGroupNumCols;\n" % kernelName
    self.incStr += "extern const unsigned int %s_microTileNumRows;\n" % kernelName
    self.incStr += "extern const unsigned int %s_microTileNumCols;\n" % kernelName
    self.incStr += "extern const unsigned int %s_unroll;\n" % kernelName
    self.incStr += "extern const char * const %s_src;\n" % kernelName
    self.cppStr += "#include \"%s%s_src.cpp\"\n" % (Common.getRelativeKernelSourcePath(), kernelName)
    kernelName = kernel.getRowName()
    self.incStr += "extern const unsigned int %s_workGroupNumRows;\n" % kernelName
    self.incStr += "extern const unsigned int %s_workGroupNumCols;\n" % kernelName
    self.incStr += "extern const unsigned int %s_microTileNumRows;\n" % kernelName
    self.incStr += "extern const unsigned int %s_microTileNumCols;\n" % kernelName
    self.incStr += "extern const unsigned int %s_unroll;\n" % kernelName
    self.incStr += "extern const char * const %s_src;\n" % kernelName
    self.cppStr += "#include \"%s%s_src.cpp\"\n" % (Common.getRelativeKernelSourcePath(), kernelName )
    kernelName = kernel.getColName()
    self.incStr += "extern const unsigned int %s_workGroupNumRows;\n" % kernelName
    self.incStr += "extern const unsigned int %s_workGroupNumCols;\n" % kernelName
    self.incStr += "extern const unsigned int %s_microTileNumRows;\n" % kernelName
    self.incStr += "extern const unsigned int %s_microTileNumCols;\n" % kernelName
    self.incStr += "extern const unsigned int %s_unroll;\n" % kernelName
    self.incStr += "extern const char * const %s_src;\n" % kernelName
    self.cppStr += "#include \"%s%s_src.cpp\"\n" % (Common.getRelativeKernelSourcePath(), kernelName)
    kernelName = kernel.getCornerName()
    self.incStr += "extern const unsigned int %s_workGroupNumRows;\n" % kernelName
    self.incStr += "extern const unsigned int %s_workGroupNumCols;\n" % kernelName
    self.incStr += "extern const unsigned int %s_microTileNumRows;\n" % kernelName
    self.incStr += "extern const unsigned int %s_microTileNumCols;\n" % kernelName
    self.incStr += "extern const unsigned int %s_unroll;\n" % kernelName
    self.incStr += "extern const char * const %s_src;\n" % kernelName
    self.cppStr += "#include \"%s%s_src.cpp\"\n" % (Common.getRelativeKernelSourcePath(), kernelName)

    self.incFile.write( self.incStr )
    self.incStr = ""
    self.cppFile.write( self.cppStr )
    self.cppStr = ""

  def writeToFile(self):
    self.incFile.write( self.incStr )
    self.incFile.write( "\n#endif\n" )
    self.incFile.close()
    self.cppFile.write( self.cppStr )
    self.cppFile.close()


################################################################################
# BINC - Kernel Binary Includes
################################################################################
class KernelBinaryIncludes:

  ##############################################################################
  # BINC - default constructor
  ##############################################################################
  def __init__(self):
    self.incFileName = Common.getIncludePath() + "AutoGemmKernelBinaries.h"
    self.incFile = open(self.incFileName, "w")
    self.incFile.write( Common.getAutoGemmHeader() )
    self.incStr = ""
    self.incStr += "#include <cstddef>\n"
    self.incStr += "\n#ifndef AUTOGEMM_KERNEL_BINARIES_H\n"
    self.incStr += "#define AUTOGEMM_KERNEL_BINARIES_H\n"
    self.incStr += "\n"

    self.cppFileName = Common.getIncludePath() + "AutoGemmKernelBinaries.cpp"
    self.cppFile = open(self.cppFileName, "w")
    self.cppFile.write( Common.getAutoGemmHeader() )
    self.cppStr = ""
    self.cppStr += "#include \"%sAutoGemmKernelBinaries.h\"\n" % Common.getRelativeIncludePath()
    self.cppStr += "\n"
    self.cppStr += "#ifdef AUTOGEMM_USE_PRE_COMPILED_KERNELS\n"
    self.cppStr += "#include \"%sAutoGemmKernelBinariesPreCompiled.h\"\n" % Common.getRelativeKernelBinaryPath()
    self.cppStr += "#endif\n"
    self.cppStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getName()
    self.incStr += "extern unsigned char *%s_bin;\n" % kernelName
    self.incStr += "extern         size_t %s_binSize;\n" % kernelName
    self.cppStr += "#ifndef KERNEL_" + kernelName.upper() + "_BIN_CPP\n"
    self.cppStr += "unsigned char *%s_bin = 0;\n" % kernelName
    self.cppStr += "        size_t %s_binSize = 0;\n" % kernelName
    self.cppStr += "#else\n"
    # self.cppStr += "#pragma message(\"AutoGemmKernelBinaries.cpp: %s was pre-compiled.\")\n" % kernelName
    self.cppStr += "#endif\n"

    kernelName = kernel.getRowName()
    self.incStr += "extern unsigned char *%s_bin;\n" % kernelName
    self.incStr += "extern         size_t %s_binSize;\n" % kernelName
    self.cppStr += "#ifndef KERNEL_" + kernelName.upper() + "_BIN_CPP\n"
    self.cppStr += "unsigned char *%s_bin = 0;\n" % kernelName
    self.cppStr += "        size_t %s_binSize = 0;\n" % kernelName
    self.cppStr += "#else\n"
    # self.cppStr += "#pragma message(\"AutoGemmKernelBinaries.cpp: %s was pre-compiled.\")\n" % kernelName
    self.cppStr += "#endif\n"

    kernelName = kernel.getColName()
    self.incStr += "extern unsigned char *%s_bin;\n" % kernelName
    self.incStr += "extern         size_t %s_binSize;\n" % kernelName
    self.cppStr += "#ifndef KERNEL_" + kernelName.upper() + "_BIN_CPP\n"
    self.cppStr += "unsigned char *%s_bin = 0;\n" % kernelName
    self.cppStr += "        size_t %s_binSize = 0;\n" % kernelName
    self.cppStr += "#else\n"
    # self.cppStr += "#pragma message(\"AutoGemmKernelBinaries.cpp: %s was pre-compiled.\")\n" % kernelName
    self.cppStr += "#endif\n"

    kernelName = kernel.getCornerName()
    self.incStr += "extern unsigned char *%s_bin;\n" % kernelName
    self.incStr += "extern         size_t %s_binSize;\n" % kernelName
    self.cppStr += "#ifndef KERNEL_" + kernelName.upper() + "_BIN_CPP\n"
    self.cppStr += "unsigned char *%s_bin = 0;\n" % kernelName
    self.cppStr += "        size_t %s_binSize = 0;\n" % kernelName
    self.cppStr += "#else\n"
    # self.cppStr += "#pragma message(\"AutoGemmKernelBinaries.cpp: %s was pre-compiled.\")\n" % kernelName
    self.cppStr += "#endif\n"

    self.incFile.write( self.incStr )
    self.incStr = ""
    self.cppFile.write( self.cppStr )
    self.cppStr = ""

  def writeToFile(self):
    self.incFile.write( self.incStr )
    self.incFile.write( "\n#endif\n" )
    self.incFile.close()
    self.cppFile.write( self.cppStr )
    self.cppFile.close()


################################################################################
# CINC - ClKernel Includes
################################################################################
class ClKernelIncludes:

  ##############################################################################
  # CINC - default constructor
  ##############################################################################
  def __init__(self):
    self.incName = Common.getIncludePath() + "AutoGemmClKernels.h"
    self.incFile = open(self.incName, "w")
    self.incFile.write( Common.getAutoGemmHeader() )
    self.incStr = "#ifndef AUTOGEMM_CL_KERNELS_H\n"
    self.incStr += "#define AUTOGEMM_CL_KERNELS_H\n"
    self.incStr += "#if defined( __APPLE__ ) || defined( __MACOSX )\n"
    self.incStr += "#include <OpenCL/cl.h>\n"
    self.incStr += "#else\n"
    self.incStr += "#include <CL/cl.h>\n"
    self.incStr += "#endif\n"
    self.incStr += "\n"
    self.incStr += "#ifdef __cplusplus\n"
    self.incStr += "extern \"C\" {\n"
    self.incStr += "#endif\n"
    self.incStr += "    void initAutoGemmClKernels(void);\n";
    self.incStr += "#ifdef __cplusplus\n"
    self.incStr += "}\n";
    self.incStr += "#endif\n"
    self.incStr += "\n";

    self.cppName = Common.getIncludePath() + "AutoGemmClKernels.cpp"
    self.cppFile = open(self.cppName, "w")
    self.cppFile.write( Common.getAutoGemmHeader() )
    self.cppStr = "#if defined( __APPLE__ ) || defined( __MACOSX )\n"
    self.cppStr += "#include <OpenCL/cl.h>\n"
    self.cppStr += "#else\n"
    self.cppStr += "#include <CL/cl.h>\n"
    self.cppStr += "#endif\n"
    self.cppStr += "\n"


    self.initFunction = "";
    self.initFunction += "extern \"C\" {\n";
    self.initFunction += "    void initAutoGemmClKernels(void);\n";
    self.initFunction += "}\n";
    self.initFunction += "\n";
    self.initFunction += "void initAutoGemmClKernels(void) {\n";
    self.defines = "";

  def addKernel(self, kernel):
    kernelNames = [
      kernel.getName(),
      kernel.getRowName(),
      kernel.getColName(),
      kernel.getCornerName()
    ]
    for kernelName in kernelNames:
      self.incStr += "extern cl_kernel %s_clKernel;\n" % kernelName

      self.defines += "cl_kernel %s_clKernel = NULL;\n" % kernelName

      self.initFunction += "    if(%s_clKernel != NULL) {\n" % kernelName
      self.initFunction += "        clReleaseKernel(%s_clKernel);\n" % kernelName
      self.initFunction += "        %s_clKernel = NULL;\n" % kernelName
      self.initFunction += "    }\n"

    self.incFile.write( self.incStr )
    self.incStr = ""
#   self.cppFile.write( self.cppStr )
#   self.cppStr = ""

  def writeToFile(self):
    self.incFile.write( self.incStr )
    self.incFile.write( "\n#endif\n" )
    self.incFile.close()

    self.initFunction += "}\n";
    self.cppStr += self.defines + "\n";
    self.defines = "";
    self.cppStr += self.initFunction + "\n";
    self.initFunction = "";

#    self.cppStr += "\n";
#    self.cppStr += "initAutoGemmClKernels();\n";
    self.cppFile.write( self.cppStr )
    self.cppFile.close()


################################################################################
# KSBO - Kernel Source Build Options
################################################################################
class KernelSourceBuildOptions:

  ##############################################################################
  # KSBO - default constructor
  ##############################################################################
  def __init__(self):
    self.incName = Common.getIncludePath() + "AutoGemmKernelBuildOptionsSource.h"
    self.incFile = open(self.incName, "w")
    self.incFile.write( Common.getAutoGemmHeader() )
    self.incStr = "#ifndef AUTOGEMM_KERNEL_SOURCE_BUILD_OPTIONS_H\n"
    self.incStr += "#define AUTOGEMM_KERNEL_SOURCE_BUILD_OPTIONS_H\n"
    self.incStr += "\n"

    self.cppName = Common.getIncludePath() + "AutoGemmKernelBuildOptionsSource.cpp"
    self.cppFile = open(self.cppName, "w")
    self.cppFile.write( Common.getAutoGemmHeader() )
    self.cppStr  = ""
    self.cppStr += "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelBuildOptionsSource.h\"\n"

  def addKernel(self, kernel):
    kernelName = kernel.getName()
    self.incStr += "extern const char * const %s_srcBuildOptions;\n" \
        % kernelName
    self.cppStr += "const char * const %s_srcBuildOptions = \"-cl-std=CL%s\";\n" \
        % (kernelName, Common.getClCompilerVersion() )

    self.incFile.write( self.incStr )
    self.incStr = ""
    self.cppFile.write( self.cppStr )
    self.cppStr = ""

  def writeToFile(self):
    self.incFile.write( self.incStr )
    self.incFile.write( "\n#endif\n" )
    self.incFile.close()

    self.cppFile.write( self.cppStr )
    self.cppFile.close()


################################################################################
# KBSO - Kernel Binary Build Options
################################################################################
class KernelBinaryBuildOptions:

  ##############################################################################
  # KBSO - default constructor
  ##############################################################################
  def __init__(self):
    self.incName = Common.getIncludePath() + "AutoGemmKernelBuildOptionsBinary.h"
    self.incFile = open(self.incName, "w")
    self.incFile.write( Common.getAutoGemmHeader() )
    self.incStr = "#ifndef AUTOGEMM_KERNEL_BINARY_BUILD_OPTIONS_H\n"
    self.incStr += "#define AUTOGEMM_KERNEL_BINARY_BUILD_OPTIONS_H\n"
    self.incStr += "\n"

    self.cppName = Common.getIncludePath() + "AutoGemmKernelBuildOptionsBinary.cpp"
    self.cppFile = open(self.cppName, "w")
    self.cppFile.write( Common.getAutoGemmHeader() )
    self.cppStr = ""
    self.cppStr += "#include \"" + Common.getRelativeIncludePath() + "AutoGemmKernelBuildOptionsBinary.h\"\n"

  def addKernel(self, kernel):
    kernelName = kernel.getName()
    self.incStr += "extern const char * const %s_binBuildOptions;\n" % kernelName
    self.cppStr += "const char * const %s_binBuildOptions = \"-cl-std=CL%s\";\n" % (kernelName, Common.getClCompilerVersion() )

    self.incFile.write( self.incStr )
    self.incStr = ""
    self.cppFile.write( self.cppStr )
    self.cppStr = ""

  def writeToFile(self):
    self.incFile.write( self.incStr )
    self.incFile.write( "\n#endif\n" )
    self.incFile.close()
    self.cppFile.write( self.cppStr )
    self.cppFile.close()


################################################################################
# CPPKE - Cpp Kernel enumeration
################################################################################
class CppKernelEnumeration:

  ##############################################################################
  # CPPKE - default constructor
  ##############################################################################
  def __init__(self):
    self.fileName = Common.getIncludePath() + "AutoGemmKernelEnumeration.h"
    self.kernelStr = ""
    self.tileStr = ""
    self.nonTileStr = ""
    self.kernelCount = 0
    self.tileCount = 0
    self.nonTileCount = 0
    self.precision = ""
    self.precisionInitialized = False

  def newPrecision(self, precision):
    if self.precisionInitialized:
      self.kernelStr += "};\n"
      self.kernelStr += "const unsigned int %sgemmNumKernels = %d;\n\n" \
          % (self.precision, self.kernelCount)
      self.tileStr += "};\n"
      self.tileStr += "const unsigned int %sgemmNumTiles = %d;\n\n" \
          % (self.precision, self.tileCount)
      self.nonTileStr += "};\n"
      self.nonTileStr += "const unsigned int %sgemmNumNonTiles = %d;\n\n" \
          % (self.precision, self.nonTileCount)
    self.precisionInitialized = True
    self.precision = precision

    self.kernelStr += "// order, transA, transB, beta, macroTileNumRows, macroTileNumCols, unroll, mSpill, nSpill\n"
    self.kernelStr += "unsigned int " + precision + "gemmKernelEnumeration[][9] = {\n"

    self.tileStr += "// macroTileNumRows, macroTileNumCols, unroll\n"
    self.tileStr += "unsigned int " + precision + "gemmTileEnumeration[][3] = {\n"

    self.nonTileStr += "// order, transA, transB, beta\n"
    self.nonTileStr += "unsigned int " + precision + "gemmNonTileEnumeration[][4] = {\n"
    self.tileCount = 0
    self.nonTileCount = 0
    self.kernelCount = 0

  def addTile(self, tile):
    self.tileStr += "  { %3u, %3u, %1u },\n" % ( \
        tile.macroTileNumRows, \
        tile.macroTileNumCols, \
        tile.unroll )
    self.tileCount += 1

  def addNonTile(self, nonTile):
    self.nonTileStr += "  { %1u, %1u, %1u, %1u },\n" % ( \
        1 if nonTile.order=="clblasColumnMajor" else 0, \
        0 if nonTile.transA=="N" else 1 if nonTile.transA=="T" else 2 , \
        0 if nonTile.transB=="N" else 1 if nonTile.transB=="T" else 2, \
        1 if nonTile.beta>0 else 0 )
    self.nonTileCount += 1

  def addKernel(self, kernel):
    # 6) list to add to ktest for automated kernel testing
    for mSpill in range(0, 2):
      for nSpill in range(0, 2):
        self.kernelStr += "  { %1u, %1u, %1u, %1u, %3u, %3u, %2u, %1u, %1u },\n" % ( \
          1 if kernel.order=="clblasColumnMajor" else 0, \
          0 if kernel.transA=="N" else 1 if kernel.transA=="T" else 2 , \
          0 if kernel.transB=="N" else 1 if kernel.transB=="T" else 2, \
          1 if kernel.beta>0 else 0, \
          kernel.macroTileNumRows, \
          kernel.macroTileNumCols, \
          kernel.unroll, \
          mSpill, \
          nSpill )
    self.kernelCount += 4

  def writeToFile(self):
    self.kernelStr += "};\n"
    self.kernelStr += "const unsigned int %sgemmNumKernels = %d;\n" % (self.precision, self.kernelCount)
    self.tileStr += "};\n"
    self.tileStr += "const unsigned int %sgemmNumTiles = %d;\n" % (self.precision, self.tileCount)
    self.nonTileStr += "};\n"
    self.nonTileStr += "const unsigned int %sgemmNumNonTiles = %d;\n" % (self.precision, self.nonTileCount)
    incFile = open(self.fileName, "w")
    incFile.write( Common.getAutoGemmHeader() )
    incFile.write( self.tileStr )
    incFile.write( "\n\n" )
    incFile.write( self.nonTileStr )
    incFile.write( "\n\n" )
    incFile.write( self.kernelStr )
    incFile.close()

################################################################################
# Write Includes
################################################################################
def writeIncludes():
  print("AutoGemm.py: Generating include files.")
  if not os.path.exists( Common.getIncludePath() ):
    os.makedirs( Common.getIncludePath() )

  kernelSourceIncludes     = KernelSourceIncludes()
  kernelBinaryIncludes     = KernelBinaryIncludes()
  clKernelIncludes         = ClKernelIncludes()
  kernelSourceBuildOptions = KernelSourceBuildOptions()
  kernelBinaryBuildOptions = KernelBinaryBuildOptions()
  cppKernelEnumeration     = CppKernelEnumeration()


  # for each precision
  kernel = KernelParameters.KernelParameters()
  for precision in AutoGemmParameters.precisions:
    kernel.precision = precision
    cppKernelEnumeration.newPrecision(precision)

    # valid tiles for this precision
    tiles = AutoGemmParameters.getTilesForPrecision(precision)

    # add tiles for this precision to Cpp
    for tile in tiles:
      cppKernelEnumeration.addTile(tile)

    # for non tile parameters
    for order in AutoGemmParameters.orders:
      kernel.order = order
      for transA in AutoGemmParameters.transposes[precision]:
        kernel.transA = transA
        for transB in AutoGemmParameters.transposes[precision]:
          kernel.transB = transB
          for beta in AutoGemmParameters.betas:
            kernel.beta = beta

            # add this nonTile combo for this precision to Cpp
            cppKernelEnumeration.addNonTile(kernel)

            # for tile parameters
            for tile in tiles:
              kernel.useTile(tile)
              kernelSourceIncludes.addKernel(kernel)
              kernelBinaryIncludes.addKernel(kernel)
              kernelSourceBuildOptions.addKernel(kernel)
              kernelBinaryBuildOptions.addKernel(kernel)
              clKernelIncludes.addKernel(kernel)
              cppKernelEnumeration.addKernel(kernel)

  # save written files
  kernelSourceIncludes.writeToFile()
  kernelBinaryIncludes.writeToFile()
  clKernelIncludes.writeToFile()
  kernelSourceBuildOptions.writeToFile()
  kernelBinaryBuildOptions.writeToFile()
  cppKernelEnumeration.writeToFile()



################################################################################
# Main
################################################################################
if __name__ == "__main__":
  if len(sys.argv) == 2:
    Common.setOutputPath(sys.argv[1])
  else:
    print("Warning: No output path specified; default is working directory.")
  writeIncludes()
