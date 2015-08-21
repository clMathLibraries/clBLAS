import argparse
import AutoGemmParameters
import Common


################################################################################
# Auto-Gemm
################################################################################

def writeOfflineCompilation(args):
  print "AutoGemm: Kernels To PreCompile"
  ocFileName = Common.getIncludePath() + "AutoGemmKernelsToPreCompile.h"
  ocFile = open(ocFileName, "w")
  ocFile.write( Common.getAutoGemmHeader() )

  fileStr = "\n/*precision, order, transA, transB, beta, tileNumRows, tileNumCols, unroll*/\n"
  fileStr += "\nunsigned int gemmPreCompile[][8] = {\n"

  count = 0
  for precision in args.precisions:
    ocFile.write( fileStr )
    fileStr = ""
    for order in args.orders:
      for transpose in args.transposes:
        transA = transpose[0]
        transB = transpose[1]
        if (transA=="C" or transB=="C") and (precision=="s" or precision=="d"):
          # real precision doesn't have conjugate transpose
          continue
        for beta in args.betas:
          for tile in args.tiles:
            tileNumRows = int( tile[:tile.find("x")] )
            tileNumCols = int( tile[tile.find("x")+1:] )
            for unroll in AutoGemmParameters.unrolls[precision]:
              if args.nonMultiples or (unroll > 1 and len(AutoGemmParameters.unrolls[precision]) > 1):
                # print combination
                kernelStr = "  { %1u, %1u, %1u, %1u, %1u, %3u, %3u, %2u },\n" \
                    % (
                    Common.precisionInt[precision],
                    Common.orderInt[order],
                    Common.transposeInt[transA],
                    Common.transposeInt[transB],
                    beta,
                    tileNumRows,
                    tileNumCols,
                    unroll
                    )
                fileStr += kernelStr
                #print kernelStr
                count+=1
  fileStr += "};\n"
  fileStr += "unsigned int gemmPreCompileNum = " + str(count) + ";\n"
  if args.nonMultiples:
    fileStr += "bool gemmPreCompileNonMultiples = true;\n"
  else:
    fileStr += "bool gemmPreCompileNonMultiples = false;\n"
  ocFile.write( fileStr )
  ocFile.close()
  if args.nonMultiples:
    count *= 4
  print "AutoGemm: Pre-Compile %u kernels" % count


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
  ap.add_argument("--tiles", dest="tiles", action="store", nargs="+", choices=AutoGemmParameters.getTileChoices() )
  ap.add_argument("--non-multiples", dest="nonMultiples", action="store_true" )
  args = ap.parse_args()
  if args.output:
    Common.setOutputPath(args.output)
  else:
    print "Warning: No output path specified; default is working directory."

  # write offline compilation header
  writeOfflineCompilation(args)

