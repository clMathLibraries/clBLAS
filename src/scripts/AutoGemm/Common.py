################################################################################
# Auto-Gemm
################################################################################

def getOutputPath():
  return "output/"

def getKernelSourcePath():
  return getOutputPath() + "GemmKernelSources/"

def getKernelBinaryPath():
  return getOutputPath() + "GemmKernelBinaries/"

def getAutoGemmHeader():
  return (
      "/*******************************************************************************\n"
      " * This file was auto-generated using the auto-gemm.py python script.\n"
      " * NO NOT modify this file! Instead, make changes to\n"
      " *   clBLAS/src/scripts/auto-gemm/auto-gemm.py then re-generate files\n"
      " *   (otherwise local changes will be lost after re-generation).\n"
      " * - David Tanner\n"
      " ******************************************************************************/\n\n"
      )

hostDataChar = { "s":"s", "d":"d", "c":"c", "z":"z" }
hostDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }
openclDataType = { "s":"float", "d":"double", "c":"float2", "z":"double2" }


