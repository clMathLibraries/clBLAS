################################################################################
# Auto-Gemm
# - Automatically generate gemm kernels based on tile parameters
# - This script generates the following to ease integration into clBLAS:
#   - generate all the kernel files
#   - kernel selection logic
#   - include files for kernel strings
#
# TODO Now
# - profiler to spit out data to be refined by hand
# - offline compilation
# TODO Future
# - fuse together unroll=8 and unroll=1 in same kernel ?
#     functionally works fine, but lowers performance by ~10%
################################################################################

"""
real sgemm ksd
    [ 7104, [ 16, 16,  6,  6], [ [ 16, 16,  6,  6], [ 16, 16,  7,  7] ] ],
    [ 4080, [ 16, 16,  6,  6], [ [ 16, 16,  6,  6], [ 16, 16,  4,  4], [ 16, 16,  7,  7] ] ],
    [ 2592, [ 16, 16,  4,  4], [ [ 16, 16,  6,  6], [ 16, 16,  4,  4], [ 16, 16,  7,  7], [ 16, 16,  5,  5] ] ],
    [ 1984, [ 16, 16,  4,  4], [ [ 16, 16,  6,  6], [ 16, 16,  4,  4], [ 16, 16,  5,  5], [ 16, 16,  7,  7], [ 16, 16,  3,  3] ] ],
    [ 1424, [ 16, 16,  4,  4], [ [ 16, 16,  6,  6], [ 16, 16,  4,  4], [ 16, 16,  5,  5], [ 16, 16,  7,  7], [ 16, 16,  3,  3], [ 16, 16,  2,  2] ] ],
    [  896, [ 16, 16,  2,  2], [ [ 16, 16,  4,  4], [ 16, 16,  6,  6], [ 16, 16,  7,  7], [ 16, 16,  5,  5], [ 16, 16,  3,  3], [ 16, 16,  2,  2] ] ],
    [  304, [ 16, 16,  2,  2], [ [ 16, 16,  3,  3], [ 16, 16,  2,  2], [ 16, 16,  1,  1] ] ],
    [    0, [ 16, 16,  1,  1], [ [ 16, 16,  1,  1] ] ],
"""

"""
for testing all micro-tile sizes
    [  128, [ 16, 16,  8,  8], [ [ 16, 16,  8,  8] ] ],
    [  112, [ 16, 16,  7,  7], [ [ 16, 16,  7,  7] ] ],
    [   96, [ 16, 16,  6,  6], [ [ 16, 16,  6,  6] ] ],
    [   80, [ 16, 16,  5,  5], [ [ 16, 16,  5,  5] ] ],
    [   64, [ 16, 16,  4,  4], [ [ 16, 16,  4,  4] ] ],
    [   48, [ 16, 16,  3,  3], [ [ 16, 16,  3,  3] ] ],
    [   32, [ 16, 16,  2,  2], [ [ 16, 16,  2,  2] ] ],
    [    0, [ 16, 16,  1,  1], [ [ 16, 16,  1,  1] ] ],
"""

kernelSelectionData = {
# [ size, [ valid tiles ], fallback tile],
  "s":[
    [ 7104, [ 16, 16,  6,  6], [ [ 16, 16,  6,  6] ] ],
    [ 4080, [ 16, 16,  6,  6], [ [ 16, 16,  6,  6], [ 16, 16,  8,  8], [ 16, 16,  4,  4] ] ],
    [ 2592, [ 16, 16,  4,  4], [ [ 16, 16,  6,  6], [ 16, 16,  4,  4], [ 16, 16,  5,  5] ] ],
    [ 1984, [ 16, 16,  4,  4], [ [ 16, 16,  6,  6], [ 16, 16,  4,  4], [ 16, 16,  5,  5], [ 16, 16,  3,  3], [ 16, 16,  7,  7] ] ],
    [ 1424, [ 16, 16,  4,  4], [ [ 16, 16,  6,  6], [ 16, 16,  4,  4], [ 16, 16,  5,  5], [ 16, 16,  3,  3], [ 16, 16,  7,  7], [ 16, 16,  2,  2] ] ],
    [  896, [ 16, 16,  2,  2], [ [ 16, 16,  4,  4], [ 16, 16,  6,  6], [ 16, 16,  5,  5], [ 16, 16,  3,  3], [ 16, 16,  2,  2] ] ],
    [  304, [ 16, 16,  2,  2], [ [ 16, 16,  3,  3], [ 16, 16,  2,  2], [ 16, 16,  1,  1] ] ],
    [    0, [ 16, 16,  1,  1], [ [ 16, 16,  1,  1] ] ],
    ],
  "d":[
    [ 4880, [ 16, 16,  6,  6], [ [ 16, 16,  6,  6], [ 16, 16,  4,  4] ] ],
    [ 2800, [ 16, 16,  4,  4], [ [ 16, 16,  4,  4], [ 16, 16,  6,  6] ] ],
    [ 1536, [ 16, 16,  4,  4], [ [ 16, 16,  4,  4], [ 16, 16,  6,  6], [ 16, 16,  3,  3], [ 16, 16,  5,  5] ] ],
    [  768, [ 16, 16,  4,  4], [ [ 16, 16,  4,  4], [ 16, 16,  6,  6], [ 16, 16,  3,  3], [ 16, 16,  5,  5], [ 16, 16,  2,  2] ] ],
    [  512, [ 16, 16,  2,  2], [ [ 16, 16,  4,  4], [ 16, 16,  3,  3], [ 16, 16,  5,  5], [ 16, 16,  2,  2], [ 16, 16,  1,  1] ] ],
    [  256, [ 16, 16,  2,  2], [ [ 16, 16,  3,  3], [ 16, 16,  2,  2], [ 16, 16,  1,  1] ] ],
    [    0, [ 16, 16,  1,  1], [ [ 16, 16,  1,  1] ] ],
    ],
  "c":[
    [ 4720, [ 16, 16,  4,  4], [ [ 16, 16,  4,  4] ] ],
    [ 3840, [ 16, 16,  4,  4], [ [ 16, 16,  4,  4], [ 16, 16,  6,  6] ] ],
    [ 3072, [ 16, 16,  4,  4], [ [ 16, 16,  4,  4], [ 16, 16,  6,  6], [ 16, 16,  3,  3] ] ],
    [ 2256, [ 16, 16,  4,  4], [ [ 16, 16,  4,  4], [ 16, 16,  6,  6], [ 16, 16,  3,  3], [ 16, 16,  2,  2] ] ],
    [ 2112, [ 16, 16,  4,  4], [ [ 16, 16,  4,  4], [ 16, 16,  6,  6], [ 16, 16,  3,  3], [ 16, 16,  2,  2], [ 16, 16,  5,  5] ] ],
    [ 1408, [ 16, 16,  2,  2], [ [ 16, 16,  4,  4], [ 16, 16,  3,  3], [ 16, 16,  2,  2], [ 16, 16,  5,  5] ] ],
    [  880, [ 16, 16,  2,  2], [ [ 16, 16,  2,  2], [ 16, 16,  3,  3], [ 16, 16,  5,  5] ] ],
    [  432, [ 16, 16,  2,  2], [ [ 16, 16,  2,  2], [ 16, 16,  3,  3], [ 16, 16,  1,  1] ] ],
    [  288, [ 16, 16,  1,  1], [ [ 16, 16,  2,  2], [ 16, 16,  1,  1] ] ],
    [    0, [ 16, 16,  1,  1], [ [ 16, 16,  1,  1] ] ],
    ],
  "z":[
    [ 3920, [ 16, 16,  3,  3], [ [ 16, 16,  3,  3] ] ],
    [ 1728, [ 16, 16,  3,  3], [ [ 16, 16,  3,  3], [ 16, 16,  4,  4] ] ],
    [ 1264, [ 16, 16,  3,  3], [ [ 16, 16,  3,  3], [ 16, 16,  4,  4], [ 16, 16,  2,  2] ] ],
    [  832, [ 16, 16,  2,  2], [ [ 16, 16,  3,  3], [ 16, 16,  4,  4], [ 16, 16,  2,  2] ] ],
    [  576, [ 16, 16,  2,  2], [ [ 16, 16,  3,  3], [ 16, 16,  2,  2] ] ],
    [  336, [ 16, 16,  2,  2], [ [ 16, 16,  3,  3], [ 16, 16,  2,  2], [ 16, 16,  1,  1] ] ],
    [  192, [ 16, 16,  1,  1], [ [ 16, 16,  2,  2], [ 16, 16,  1,  1] ] ],
    [    0, [ 16, 16,  1,  1], [ [ 16, 16,  1,  1] ] ],

    ],
  }


import os
import sys
import getopt
import copy

import Includes
import Common
import KernelSelection
import KernelParameters
import KernelOpenCL



# global variables
validParameterCombinations = 0


################################################################################
# Main
################################################################################
def main(argv):
  global validParameterCombinations

  # create output directories if needed
  if not os.path.exists( Common.getOutputPath() ):
    os.makedirs( Common.getOutputPath() )
  if not os.path.exists( Common.getKernelSourcePath() ):
    os.makedirs( Common.getKernelSourcePath() )
  if not os.path.exists( Common.getKernelBinaryPath() ):
    os.makedirs( Common.getKernelBinaryPath() )

  processAllKernelParameterCombinations(argv)
  print "Kernels Used: %d" % (validParameterCombinations)



################################################################################
# Main - Process all kernel parameter combinations
################################################################################
def processAllKernelParameterCombinations(argv):
  global kernelSelectionData

  # non-tile parameters
  listPrecision = ["s", "d", "c", "z"]
  listOrder = [ "clblasColumnMajor" ]
  dictTrans = { "s":["N", "T"], "d":["N", "T"], \
      "c":["N", "T", "C"], "z":["N", "T", "C"] }
  dictUnroll = { "s":[16], "d":[8], "c":[8], "z":[8] }
  listBeta = [ 0, 1 ]

  # tile parameters
  microTileMaxProductDict = { "s":(6*6), "d":(6*6), "c":(3*6), "z":(3*3) }
  microTileMaxEdgeLengthDict = { "s":12, "d":12, "c":12, "z":12 }
  #listWorkGroupDims = [ [16, 16] ]
  listTileKernelParameters = []
  listEdgeKernelParameters = []

  kernelSelectionLogic = KernelSelection.KernelSelection( \
      listPrecision, \
      listOrder, \
      dictTrans, \
      listBeta, \
      dictUnroll, \
      kernelSelectionData )
  kernelSelectionLogic.writeToFile()

  kernelSelectionSpecific  = KernelSelection.KernelSelectionSpecific();
  kernelSourceIncludes     = Includes.KernelSourceIncludes()
  kernelBinaryIncludes     = Includes.KernelBinaryIncludes()
  clKernelIncludes         = Includes.ClKernelIncludes()
  kernelSourceBuildOptions = Includes.KernelSourceBuildOptions()
  kernelBinaryBuildOptions = Includes.KernelBinaryBuildOptions()
  cppKernelEnumeration     = Includes.CppKernelEnumeration()


  # for each precision
  kernel = KernelParameters.KernelParameters()
  for precision in listPrecision:
    kernel.precision = precision
    cppKernelEnumeration.newPrecision(precision)
    kernelSelectionSpecific.newPrecision(precision)
    listTrans = dictTrans[precision]

    # valid tiles for this precision
    listTileKernelParameters = []
    tile = KernelParameters.TileParameters()
    for sizeData in kernelSelectionData[precision]:
      fallbackTile = sizeData[1]
      validTiles = sizeData[2]
      # add valid tiles
      for tileParams in validTiles:
        #print tileParams
        tile.workGroupNumRows = tileParams[0]
        tile.workGroupNumCols = tileParams[1]
        tile.microTileNumRows = tileParams[2]
        tile.microTileNumCols = tileParams[3]
        tile.macroTileNumRows = tile.workGroupNumRows*tile.microTileNumRows
        tile.macroTileNumCols = tile.workGroupNumCols*tile.microTileNumCols
        #print tile.getName()
        for unroll in dictUnroll[precision]:
          tile.unroll = unroll
          if tile.isValid():
            listTileKernelParameters.append( copy.copy(tile) )
          else:
            print tile.getName() + " - SKIPPING - "

      # add fallback tile
      tile.workGroupNumRows = fallbackTile[0]
      tile.workGroupNumCols = fallbackTile[1]
      tile.microTileNumRows = fallbackTile[2]
      tile.microTileNumCols = fallbackTile[3]
      tile.macroTileNumRows = tile.workGroupNumRows*tile.microTileNumRows
      tile.macroTileNumCols = tile.workGroupNumCols*tile.microTileNumCols
      for unroll in dictUnroll[precision]:
        tile.unroll = unroll
        if tile.isValid():
          listTileKernelParameters.append( copy.copy(tile) )
        else:
          print tile.getName() + " - SKIPPING - "

    print "\n"
    setTileKernelParameters = set(listTileKernelParameters)
    print setTileKernelParameters
    listTileKernelParameters = list( setTileKernelParameters )
    listTileKernelParameters.sort()
    print listTileKernelParameters

    # add tiles for this precision to Cpp
    for tile in listTileKernelParameters:
      print tile.getName() + " %ux%u, %ux%u, %ux%u, %u" % ( \
          tile.workGroupNumRows, \
          tile.workGroupNumCols, \
          tile.microTileNumRows, \
          tile.microTileNumCols, \
          tile.macroTileNumRows, \
          tile.macroTileNumCols, \
          tile.unroll )
      cppKernelEnumeration.addTile(tile)

    # for non tile parameters
    for order in listOrder:
      kernel.order = order
      kernelSelectionSpecific.newOrder(order)
      for transA in listTrans:
        kernel.transA = transA
        for transB in listTrans:
          kernel.transB = transB
          kernelSelectionSpecific.newTrans(transA, transB)
          for beta in listBeta:
            kernel.beta = beta
            kernelSelectionSpecific.newBeta(beta)

            # add this nonTile combo for this precision to Cpp
            cppKernelEnumeration.addNonTile(kernel)

            # for tile parameters
            for tile in listTileKernelParameters:
              kernel.useTile(tile)
              # process kernel parameters
              processKernel( \
                  kernel, \
                  kernelSourceIncludes, \
                  kernelBinaryIncludes, \
                  clKernelIncludes, \
                  kernelSourceBuildOptions, \
                  kernelBinaryBuildOptions, \
                  cppKernelEnumeration )
              kernelSelectionSpecific.newKernel(kernel)

  # save written files
  kernelSelectionSpecific.writeToFile()
  kernelSourceIncludes.writeToFile()
  kernelBinaryIncludes.writeToFile()
  clKernelIncludes.writeToFile()
  kernelSourceBuildOptions.writeToFile()
  kernelBinaryBuildOptions.writeToFile()
  cppKernelEnumeration.writeToFile()




################################################################################
# Main - Order Tile Sizes
# - returns 1 if tileA should come first
# - process tiles largest -> smallest (elements/work-item)
# - for same size tile, choose squarer one
################################################################################
def orderTileSizes(tileA, tileB):
  tileAWorkGroupSize = tileA.workGroupNumRows * tileA.workGroupNumCols
  tileAMicroTileSize = tileA.microTileNumRows * tileA.microTileNumCols
  tileASize = tileAWorkGroupSize*tileAMicroTileSize

  tileBWorkGroupSize = tileB.workGroupNumRows * tileB.workGroupNumCols
  tileBMicroTileSize = tileB.microTileNumRows * tileB.microTileNumCols
  tileBSize = tileBWorkGroupSize*tileBMicroTileSize
  # choose larger macro tile
  if (tileASize > tileBSize):
    return 1
  elif (tileBSize > tileASize):
    return -1
  else: # macro tile same
    tileANumRows = tileA.workGroupNumRows + tileA.microTileNumRows
    tileANumCols = tileA.workGroupNumCols + tileA.microTileNumCols
    tileBNumRows = tileB.workGroupNumRows + tileB.microTileNumRows
    tileBNumCols = tileB.workGroupNumCols + tileB.microTileNumCols
    # choose the squarer one
    if (tileANumRows+tileANumCols) < (tileBNumRows+tileBNumCols):
      return 1
    elif (tileBNumRows+tileBNumCols) < (tileANumRows+tileANumCols):
      return -1
    else: #same macro tile dimensions
      # choose larger unroll
      if tileA.unroll > tileB.unroll:
        return 1
      else:
        return -1



################################################################################
# Main - Process kernel
################################################################################
def processKernel( \
    kernel, \
    kernelSourceIncludes, \
    kernelBinaryIncludes, \
    clKernelIncludes, \
    kernelSourceBuildOptions, \
    kernelBinaryBuildOptions, \
    cppKernelEnumeration ):
  global validParameterCombinations

  ############################################################
  # check if parameter combination is valid
  kernelName = kernel.getName()
  if kernel.isValid():
    #print "Processing: " + kernelName
    validParameterCombinations += 4
  else:
    print kernelName + " - SKIPPING - " + kernel.error
    return

  print "%s: s = %3d" % (kernelName, kernel.microTileNumRows*kernel.microTileNumCols)


  ############################################################
  # add kernel to include files
  kernelSourceIncludes.addKernel(kernel)
  kernelBinaryIncludes.addKernel(kernel)
  kernelSourceBuildOptions.addKernel(kernel)
  kernelBinaryBuildOptions.addKernel(kernel)
  clKernelIncludes.addKernel(kernel)
  cppKernelEnumeration.addKernel(kernel)

  ############################################################
  # write kernels to file
  KernelOpenCL.writeOpenCLKernelToFile(kernel)
  # row kernel
  rowKernel = copy.copy(kernel)
  rowKernel.macroTileNumRows = 1
  KernelOpenCL.writeOpenCLKernelToFile(rowKernel)
  # col kernel
  colKernel = copy.copy(kernel)
  colKernel.macroTileNumCols = 1
  KernelOpenCL.writeOpenCLKernelToFile(colKernel)
  # corner kernel
  cornerKernel = copy.copy(kernel)
  cornerKernel.macroTileNumRows = 1
  cornerKernel.macroTileNumCols = 1
  KernelOpenCL.writeOpenCLKernelToFile(cornerKernel)



################################################################################
# Call Main
################################################################################
if __name__ == "__main__":
  main(sys.argv[1:])

