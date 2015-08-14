################################################################################
# Auto-Gemm
################################################################################

outputPath = ""
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
      " * DO NOT modify this file! Instead, make changes to\n"
      " *   clBLAS/src/library/blas/AutoGemm/*.py then re-generate files\n"
      " *   (otherwise local changes will be lost after re-generation).\n"
      " * - David Tanner\n"
      " ******************************************************************************/\n\n"
      )

hostDataChar = { "s":"s", "d":"d", "c":"c", "z":"z" }
hostDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }
openclDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }


