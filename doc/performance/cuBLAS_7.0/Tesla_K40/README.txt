################################
#                              #
#   Benchmarking Methodology   #
#                              #
################################

############
# Hardware #
############
Tesla K40

############
# Software #
############
openSUSE 13.2
cuBLAS 7.0
driver 346.47

############
# Settings #
############
gpu clocks: set to boost level using nvidia-smi
cuBLAS:
  m=n=k=lda=ldb=ldc (for simplicity)
  alpha=beta=1
  gemms were column-major, op(A,B)=N,T

############
# Sampling #
############
For each data point, we took 10 samples. Each sample consists of 10 gemm calls with a wait afterward. Outlying samples beyond 1 standard deviation were removed (rarely if ever did this actually need to happen). Before running the 10 samples, one warm-up sample was executed (but not included in the stastics).

GFlop/s was calculated as
(2*m*n*k flops) / (host time for 10 kernels / 10) // real data
(8*m*n*k flops) / (host time for 10 kernels / 10) // complex data
