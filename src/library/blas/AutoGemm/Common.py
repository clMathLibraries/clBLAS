################################################################################
# Auto-Gemm
################################################################################

outputPath = ""
clCompilerVersion = "2.0"

def setClCompilerVersion(version):
  global clCompilerVersion
  clCompilerVersion = version

def getClCompilerVersion():
  global clCompilerVersion
  return clCompilerVersion

def setOutputPath(path):
  global outputPath
  outputPath = path + "/"

def getOutputPath():
  global outputPath
  return outputPath

def getRelativeKernelSourcePath():
  return "AutoGemmKernelSources/"

def getRelativeKernelBinaryPath():
  return "AutoGemmKernelBinaries/"

def getRelativeIncludePath():
  return "AutoGemmIncludes/"

def getKernelSourcePath():
  return getOutputPath() + getRelativeKernelSourcePath()

def getKernelBinaryPath():
  return getOutputPath() + getRelativeKernelBinaryPath()

def getIncludePath():
  return getOutputPath() + getRelativeIncludePath()

def getAutoGemmHeader():
  return (
      "/*******************************************************************************\n"
      " * This file was auto-generated using the AutoGemm.py python script.\n"
      " * DO NOT modify this file! Instead, make changes to scripts in\n"
      " *   clBLAS/src/library/blas/AutoGemm/ then re-generate files\n"
      " *   (otherwise local changes will be lost after re-generation).\n"
      " ******************************************************************************/\n\n"
      )

hostDataChar = { "s":"s", "d":"d", "c":"c", "z":"z" }
hostDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }
openclDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }

precisionInt = { "s":0, "d":1, "c":2, "z":3 }
orderInt = { "clblasRowMajor":0, "clblasColumnMajor":1 }
transposeInt = { "N":0, "T":1, "C":2 }


