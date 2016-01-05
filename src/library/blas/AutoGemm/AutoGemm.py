################################################################################
# AutoGemm
# - Automatically generate gemm kernels based on tile parameters
# - This script generates the following to ease integration into clBLAS:
#   - generate all the kernel files
#   - kernel selection logic
#   - include files for kernel strings
#
# TODO Now
# - offline compilation
# TODO Future
# - fuse together unroll=8 and unroll=1 in same kernel ?
#     functionally works fine, but lowers performance by ~10%
################################################################################

import os
import sys
import argparse
import getopt

import Common
import Includes
import KernelSelection
import AutoGemmParameters
import KernelOpenCL


################################################################################
# Main
################################################################################
if __name__ == "__main__":
  # parse arguments
  ap = argparse.ArgumentParser(description="AutoGemm")
  ap.add_argument("--output-path", dest="output" )
  ap.add_argument("--opencl-compiler-version", dest="clCompilerVersion", action="store", choices=["1.1", "1.2", "2.0" ])
  ap.add_argument("--architecture", dest="architecture", action="store", choices=["Hawaii", "Fiji" ])
  args = ap.parse_args()
  if args.output:
    Common.setOutputPath(args.output)
  else:
    print("AutoGemm.py: Warning: No output path specified; default is working directory.")

  print("AutoGemm.py: using OpenCL " + args.clCompilerVersion + " compiler")
  Common.setClCompilerVersion(args.clCompilerVersion)
  AutoGemmParameters.setArchitecture(args.architecture)

  KernelOpenCL.writeOpenCLKernels()
  KernelSelection.writeKernelSelection()
  Includes.writeIncludes()
