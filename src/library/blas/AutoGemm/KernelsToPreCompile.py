import os
import argparse
import AutoGemmParameters
import Common


################################################################################
# Auto-Gemm
################################################################################

def writeOfflineCompilation(args):
  print("AutoGemm.py: Generating list of kernels to pre-compile.")
  if not os.path.exists( Common.getIncludePath() ):
    os.makedirs( Common.getIncludePath() )

  ocFileName = Common.getIncludePath() + "AutoGemmKernelsToPreCompile.h"
  ocFile = open(ocFileName, "w")
  ocFile.write( Common.getAutoGemmHeader() )

  fileStr = "\n/*precision, order, transA, transB, beta, tileNumRows, tileNumCols, unroll*/\n"
  fileStr += "\nunsigned int gemmPreCompile[][8] = {\n"

  count = 0
  for precision in args.precisions:
    ocFile.write( fileStr )
    fileStr = ""
    validTiles = AutoGemmParameters.getTilesForPrecision(precision)
    for order in args.orders:
      for transpose in args.transposes:
        transA = transpose[0]
        transB = transpose[1]
        if (transA=="C" or transB=="C") and (precision=="s" or precision=="d"):
          # real precision doesn't have conjugate transpose
          continue
        for beta in args.betas:
          for tile in validTiles:
            # print combination
            kernelStr = "  { %1u, %1u, %1u, %1u, %1u, %3u, %3u, %2u },\n" \
                % (
                Common.precisionInt[precision],
                Common.orderInt[order],
                Common.transposeInt[transA],
                Common.transposeInt[transB],
                beta,
                tile.macroTileNumRows,
                tile.macroTileNumCols,
                tile.unroll
                )
            fileStr += kernelStr
            #print kernelStr
            count+=1
  if count is 0:
    fileStr += "  { %1u, %1u, %1u, %1u, %1u, %3u, %3u, %2u },\n" \
        % ( 0, 0, 0, 0, 0, 0, 0, 0 )
  fileStr += "};\n"
  fileStr += "unsigned int gemmPreCompileNum = " + str(count) + ";\n"
  ocFile.write( fileStr )
  ocFile.close()
  count *= 4
  print("AutoGemm.py: %u kernels will be pre-compiled." % count)


################################################################################
# Main
################################################################################
if __name__ == "__main__":

  # parse arguments
  ap = argparse.ArgumentParser(description="Which gemm kernels to compile offline.")
  ap.add_argument("--output-path", dest="output" )
  ap.add_argument("--precisions", dest="precisions", action="store", nargs="+", choices=AutoGemmParameters.precisions )
  ap.add_argument("--orders", dest="orders", action="store", nargs="+", choices=AutoGemmParameters.orders )
  ap.add_argument("--transposes", dest="transposes", action="store", nargs="+", choices=AutoGemmParameters.getTransposeChoices() )
  ap.add_argument("--betas", dest="betas", action="store", nargs="+", type=int, choices=AutoGemmParameters.betas )
  args = ap.parse_args()
  if args.output:
    Common.setOutputPath(args.output)
  else:
    print("Warning: No output path specified; default is working directory.")

  # write offline compilation header
  if args.precisions is None:
    args.precisions = []
  if args.transposes is None:
    args.transposes = []
  if args.orders is None:
    args.orders = []
  if args.betas is None:
    args.betas = []
  writeOfflineCompilation(args)
