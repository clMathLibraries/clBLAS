
# sgemm AMD vs NVIDIA
python ../../../../src/scripts/perf/plotPerformance.py \
  -d peak_sp.csv \
  -d ../../cuBLAS_7.0/Tesla_K40/peak_sp.csv \
  -d sgemm_32.csv \
  -d ../../cuBLAS_7.0/Tesla_K40/sgemm.csv \
  -x sizem --x_axis_label "m,n,k" \
  -y gflops --y_axis_label "GFlop/s" \
  --x_axis_scale linear \
  --plot label \
  --title "sgemm S9150 vs K40" --outputfile sgemm_S9150_K40.png

# sgemm AMD only
python ../../../../src/scripts/perf/plotPerformance.py \
  -d peak_sp.csv \
  -d sgemm_32.csv \
  -x sizem --x_axis_label "m,n,k" \
  -y gflops --y_axis_label "GFlop/s" \
  --x_axis_scale linear \
  --plot label \
  --title "sgemm S9150" --outputfile sgemm_S9150.png


# dgemm AMD vs NVIDIA
python ../../../../src/scripts/perf/plotPerformance.py \
  -d peak_dp.csv \
  -d ../../cuBLAS_7.0/Tesla_K40/peak_dp.csv \
  -d dgemm_96.csv \
  -d ../../cuBLAS_7.0/Tesla_K40/dgemm.csv \
  -x sizem --x_axis_label "m,n,k" \
  -y gflops --y_axis_label "GFlop/s" \
  --x_axis_scale linear \
  --plot label \
  --title "dgemm S9150 vs K40" --outputfile dgemm_S9150_K40.png

# dgemm AMD only
python ../../../../src/scripts/perf/plotPerformance.py \
  -d peak_dp.csv \
  -d dgemm_96.csv \
  -x sizem --x_axis_label "m,n,k" \
  -y gflops --y_axis_label "GFlop/s" \
  --x_axis_scale linear \
  --plot label \
  --title "dgemm S9150" --outputfile dgemm_S9150.png


# zgemm AMD vs NVIDIA
python ../../../../src/scripts/perf/plotPerformance.py \
  -d peak_dp.csv \
  -d ../../cuBLAS_7.0/Tesla_K40/peak_dp.csv \
  -d zgemm_64.csv \
  -d ../../cuBLAS_7.0/Tesla_K40/zgemm.csv \
  -x sizem --x_axis_label "m,n,k" \
  -y gflops --y_axis_label "GFlop/s" \
  --x_axis_scale linear \
  --plot label \
  --title "zgemm S9150 vs K40" --outputfile zgemm_S9150_K40.png

# zgemm AMD only
python ../../../../src/scripts/perf/plotPerformance.py \
  -d peak_dp.csv \
  -d zgemm_64.csv \
  -x sizem --x_axis_label "m,n,k" \
  -y gflops --y_axis_label "GFlop/s" \
  --x_axis_scale linear \
  --plot label \
  --title "zgemm S9150" --outputfile zgemm_S9150.png


# dtrsm AMD vs NVIDIA
python ../../../../src/scripts/perf/plotPerformance.py \
  -d peak_dp.csv \
  -d ../../cuBLAS_7.0/Tesla_K40/peak_dp.csv \
  -d dtrsm_192.csv \
  -d ../../cuBLAS_7.0/Tesla_K40/dtrsm.csv \
  -x sizem --x_axis_label "m,n,k" \
  -y gflops --y_axis_label "GFlop/s" \
  --x_axis_scale linear \
  --plot label \
  --title "dtrsm S9150 vs K40" --outputfile dtrsm_S9150_K40.png

# dtrsm AMD only
python ../../../../src/scripts/perf/plotPerformance.py \
  -d peak_dp.csv \
  -d dtrsm_192.csv \
  -x sizem --x_axis_label "m,n,k" \
  -y gflops --y_axis_label "GFlop/s" \
  --x_axis_scale linear \
  --plot label \
  --title "dtrsm S9150" --outputfile dtrsm_S9150.png

