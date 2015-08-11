import os
import sys
import getopt
import Common

################################################################################
# SINC - Kernel Source Includes
################################################################################
class KernelSourceIncludes:

  ##############################################################################
  # SINC - default constructor
  ##############################################################################
  def __init__(self):
    self.fileName = Common.getOutputPath() + "AutoGemmKernelSourceIncludes.h"
    self.fileStr = "#ifndef AUTO_GEMM_KERNEL_SOURCE_INCLUDES_H\n"
    self.fileStr += "#define AUTO_GEMM_KERNEL_SOURCE_INCLUDES_H\n"
    self.fileStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getName()
    self.fileStr += "#include \"AutoGemmKernelSources/%s_src.h\"\n" % kernelName
    kernelName = kernel.getRowName()
    self.fileStr += "#include \"AutoGemmKernelSources/%s_src.h\"\n" % kernelName
    kernelName = kernel.getColName()
    self.fileStr += "#include \"AutoGemmKernelSources/%s_src.h\"\n" % kernelName
    kernelName = kernel.getCornerName()
    self.fileStr += "#include \"AutoGemmKernelSources/%s_src.h\"\n" % kernelName

  def writeToFile(self):
    incFile = open(self.fileName, "w")
    incFile.write( Common.getAutoGemmHeader() )
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
  def __init__(self):
    self.incFileName = Common.getOutputPath() + "AutoGemmKernelBinaryIncludes.h"
    self.incStr = "#ifndef AUTO_GEMM_KERNEL_BINARY_INCLUDES_H\n"
    self.incStr += "#define AUTO_GEMM_KERNEL_BINARY_INCLUDES_H\n"
    self.incStr += "\n"
    self.nullFileName = Common.getOutputPath() + "AutoGemmKernelBinaryNulls.h"
    self.nullStr = "#ifndef AUTO_GEMM_KERNEL_BINARY_NULLS_H\n"
    self.nullStr += "#define AUTO_GEMM_KERNEL_BINARY_NULLS_H\n"
    self.nullStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getName()
    self.incStr += "#include \"AutoGemmKernelBinaries/%s_bin.h\"\n" % kernelName
    self.nullStr += "const unsigned char * const %s_bin = NULL;\n" % kernelName
    kernelName = kernel.getRowName()
    self.incStr += "#include \"AutoGemmKernelBinaries/%s_bin.h\"\n" % kernelName
    self.nullStr += "const unsigned char * const %s_bin = NULL;\n" % kernelName
    kernelName = kernel.getColName()
    self.incStr += "#include \"AutoGemmKernelBinaries/%s_bin.h\"\n" % kernelName
    self.nullStr += "const unsigned char * const %s_bin = NULL;\n" % kernelName
    kernelName = kernel.getCornerName()
    self.incStr += "#include \"AutoGemmKernelBinaries/%s_bin.h\"\n" % kernelName
    self.nullStr += "const unsigned char * const %s_bin = NULL;\n" % kernelName

  def writeToFile(self):
    incFile = open(self.incFileName, "w")
    incFile.write( Common.getAutoGemmHeader() )
    incFile.write( self.incStr )
    incFile.write( "\n#endif\n" )
    incFile.close()
    nullFile = open(self.nullFileName, "w")
    nullFile.write( Common.getAutoGemmHeader() )
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
  def __init__(self):
    self.fileName = Common.getOutputPath() + "AutoGemmClKernels.h"
    self.fileStr = "#ifndef AUTO_GEMM_CL_KERNELS_H\n"
    self.fileStr += "#define AUTO_GEMM_CL_KERNELS_H\n"
    self.fileStr += "#include \"CL/cl.h\"\n"
    self.fileStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getName()
    self.fileStr += "cl_kernel %s_clKernel = NULL;\n" % kernelName
    kernelName = kernel.getRowName()
    self.fileStr += "cl_kernel %s_clKernel = NULL;\n" % kernelName
    kernelName = kernel.getColName()
    self.fileStr += "cl_kernel %s_clKernel = NULL;\n" % kernelName
    kernelName = kernel.getCornerName()
    self.fileStr += "cl_kernel %s_clKernel = NULL;\n" % kernelName

  def writeToFile(self):
    incFile = open(self.fileName, "w")
    incFile.write( Common.getAutoGemmHeader() )
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
  def __init__(self):
    self.fileName = Common.getOutputPath() + "AutoGemmKernelSourceBuildOptions.h"
    self.fileStr = "#ifndef AUTO_GEMM_KERNEL_SOURCE_BUILD_OPTIONS_H\n"
    self.fileStr += "#define AUTO_GEMM_KERNEL_SOURCE_BUILD_OPTIONS_H\n"
    self.fileStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getName()
    self.fileStr += "const char * const %s_srcBuildOptions = \"-cl-std=CL2.0\";\n" \
        % kernelName

  def writeToFile(self):
    incFile = open(self.fileName, "w")
    incFile.write( Common.getAutoGemmHeader() )
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
  def __init__(self):
    self.fileName = Common.getOutputPath() + "AutoGemmKernelBinaryBuildOptions.h"
    self.fileStr = "#ifndef AUTO_GEMM_KERNEL_BINARY_BUILD_OPTIONS_H\n"
    self.fileStr += "#define AUTO_GEMM_KERNEL_BINARY_BUILD_OPTIONS_H\n"
    self.fileStr += "\n"

  def addKernel(self, kernel):
    kernelName = kernel.getName()
    self.fileStr += "const char * const %s_binBuildOptions = NULL;\n" % kernelName

  def writeToFile(self):
    incFile = open(self.fileName, "w")
    incFile.write( Common.getAutoGemmHeader() )
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
  def __init__(self):
    self.fileName = Common.getOutputPath() + "AutoGemmKernelEnumeration.h"
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

