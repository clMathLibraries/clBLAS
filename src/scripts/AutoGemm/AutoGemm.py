################################################################################
# Auto-Gemm
# - Automatically generate gemm kernels based on tile parameters
# - This script generates the following to ease integration into clBLAS:
#   - generate all the kernel files
#   - kernel selection logic
#   - include files for kernel strings
#
# TODO Now
# - 8x8 kernel for smallest matrices
# - 4 queues
# - more micro tile dimensions (single kernel much faster than multiple kernels)
# - logic to choose small microtile over large partial tile
# - offline compilation
# TODO Future
# - fuse together unroll=8 and unroll=1 in same kernel ?
#     functionally works fine, but lowers performance by ~10%
################################################################################

kernelSelectionData = {
# prec, tile, fallback range, valid range
    "S":[
      [ [6, 6], [4096,   -1], [864,   -1] ],
      [ [2,10], [  -1,   -1], [800, 3040] ],
      [ [4, 4], [  48, 5424], [640,   -1] ],
      [ [2, 2], [  32, 1376], [288, 1952] ],
      [ [1, 1], [   0,  304], [ 16,  784] ],
      ],
    "d":[
      ],
    "c":[
      ],
    "z":[
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
totalParameterCombinations = 0
validParameterCombinations = 0


################################################################################
# Main
################################################################################
def main(argv):
  global totalParameterCombinations, validParameterCombinations

  # create output directories if needed
  if not os.path.exists( Common.getOutputPath() ):
    os.makedirs( Common.getOutputPath() )
  if not os.path.exists( Common.getKernelSourcePath() ):
    os.makedirs( Common.getKernelSourcePath() )
  if not os.path.exists( Common.getKernelBinaryPath() ):
    os.makedirs( Common.getKernelBinaryPath() )

  processAllKernelParameterCombinations(argv)
  print "%d / %d kernels valid" % (validParameterCombinations, totalParameterCombinations)



################################################################################
# Main - Process all kernel parameter combinations
################################################################################
def processAllKernelParameterCombinations(argv):

  # non-tile parameters
  listPrecision = ["s", "d", "c", "z"]
  listOrder = [ "clblasColumnMajor" ]
  dictTrans = { "s":["N", "T"], "d":["N", "T"], \
      "c":["N", "T", "C"], "z":["N", "T", "C"] }
  listBeta = [ 0, 1 ]

  # tile parameters
  microTileMaxProductDict = { "s":(6*6), "d":(6*6), "c":(3*6), "z":(3*3) }
  microTileMaxEdgeLengthDict = { "s":12, "d":12, "c":12, "z":12 }
  listUnroll = [ 8 ]
  listWorkGroupDims = [ [16, 16] ]
  listTileKernelParameters = []
  listEdgeKernelParameters = []
  # list all valid tile parameter combinations
  #listMicroTileDims = [
  #    [ 6, 6 ], # 36
  #    [ 8, 4 ], # 32
  #    [ 6, 4 ], # 24
  #    [ 4, 4 ], # 16
  #    [ 4, 2 ], # 8
  #    [ 2, 2 ], # 4
  #    [ 2, 1 ], # 2
  #    [ 1, 1 ]  # 1
  #    ]

  kernelSelectionLogic     = KernelSelection.KernelSelection();
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

    # exhaustive micro tiles
    listMicroTileDims = []
    for numRows in range(1, microTileMaxEdgeLengthDict[precision]):
      for numCols in range(1, microTileMaxEdgeLengthDict[precision]):
        if numRows*numCols <= microTileMaxProductDict:
          listMicroTileDims.append( [numRows, numCols] )
    print listMicroTileDims

    # valid tiles for this precision
    microTileMaxProduct = microTileMaxProductDict[ precision ]
    microTileMaxEdgeLength = microTileMaxEdgeLengthDict[ precision ]
    listTileKernelParameters = []
    for microTileSize in listMicroTileDims:
      print microTileSize
      if microTileSize[0]*microTileSize[1] <= microTileMaxProduct:
        for workGroupDim in listWorkGroupDims:
          for unroll in listUnroll:
            tile = KernelParameters.TileParameters()
            tile.workGroupNumRows = workGroupDim[0]
            tile.workGroupNumCols = workGroupDim[1]
            tile.microTileNumRows = microTileSize[0]
            tile.microTileNumCols = microTileSize[1]
            tile.macroTileNumRows = workGroupDim[0]*microTileSize[0]
            tile.macroTileNumCols = workGroupDim[1]*microTileSize[1]
            tile.unroll = unroll
            if tile.isValid():
              listTileKernelParameters.append( tile )
            else:
              print tile.getName() + " - SKIPPING - "
    listTileKernelParameters.sort(orderTileSizes, reverse=True)
    print( listTileKernelParameters )
    # make list of unique tile sizes
    listMicroTileSizes = []
    for tile in listTileKernelParameters:
      microTileSize = tile.microTileNumRows*tile.microTileNumCols
      if microTileSize not in listMicroTileSizes:
        listMicroTileSizes.append( microTileSize )
    kernelSelectionLogic.newPrecision(precision, listMicroTileSizes)
    kernelSelectionSpecific.newPrecision(precision)

    listTrans = dictTrans[precision]

    # add tiles for this precision to Cpp
    for tile in listTileKernelParameters:
      cppKernelEnumeration.addTile(tile)

    # for non tile parameters
    for order in listOrder:
      kernel.order = order
      kernelSelectionLogic.newOrder(order)
      kernelSelectionSpecific.newOrder(order)
      for transA in listTrans:
        kernel.transA = transA
        for transB in listTrans:
          kernel.transB = transB
          kernelSelectionLogic.newTrans(transA, transB)
          kernelSelectionSpecific.newTrans(transA, transB)
          for beta in listBeta:
            kernel.beta = beta
            kernelSelectionLogic.newBeta(beta)
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
              kernelSelectionLogic.newKernel(kernel)
              kernelSelectionSpecific.newKernel(kernel)

  # save written files
  kernelSelectionLogic.writeToFile()
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
  global totalParameterCombinations, validParameterCombinations

  ############################################################
  # check if parameter combination is valid
  totalParameterCombinations += 4
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

