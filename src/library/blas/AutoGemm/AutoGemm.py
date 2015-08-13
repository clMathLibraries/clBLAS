################################################################################
# Auto-Gemm
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
import getopt

import Includes
import KernelSelection
import KernelOpenCL



################################################################################
# Main
################################################################################
if __name__ == "__main__":
  KernelSelection.writeKernelSelection()
  KernelOpenCL.writeOpenCLKernels()
  Includes.writeIncludes()

