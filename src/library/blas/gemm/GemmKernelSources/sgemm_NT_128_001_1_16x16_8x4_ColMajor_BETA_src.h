/*******************************************************************************
 * This file was auto-generated using the auto-gemm.py python script.
 * NO NOT modify this file! Instead, make changes to
 *   clBLAS/src/scripts/auto-gemm/auto-gemm.py then re-generate files
 *   (otherwise local changes will be lost after re-generation).
 * - David Tanner
 ******************************************************************************/

#ifndef SGEMM_NT_128_001_1_16X16_8X4_COLMAJOR_BETA_SRC_H
#define SGEMM_NT_128_001_1_16X16_8X4_COLMAJOR_BETA_SRC_H

static const char * const sgemm_NT_128_001_1_16x16_8x4_ColMajor_BETA_src ="\n"
"/* sgemm_NT_128_001_1_16x16_8x4_ColMajor_BETA */\n"
"\n"
"/* kernel parameters */\n"
"#define COLUMN_MAJOR          1\n"
"#define TRANSPOSE_A           0\n"
"#define TRANSPOSE_B           1\n"
"\n"
"#define WG_NUM_ROWS          16\n"
"#define WG_NUM_COLS          16\n"
"#define MICRO_TILE_NUM_ROWS  8\n"
"#define MICRO_TILE_NUM_COLS  4\n"
"#define MACRO_TILE_NUM_ROWS  128\n"
"#define MACRO_TILE_NUM_COLS  64\n"
"#define NUM_UNROLL_ITER      1\n"
"\n"
"#define LOCAL_ROW_PAD        0\n"
"#define LOCAL_COL_PAD        0\n"
"\n"
"/* global memory indices */\n"
"#define GET_GLOBAL_INDEX_A(ROW,COL) ((COL)*lda+(ROW))\n"
"#define GET_GLOBAL_INDEX_B(ROW,COL) ((ROW)*ldb+(COL))\n"
"#define GET_GLOBAL_INDEX_C(ROW,COL) ((COL)*ldc+(ROW))\n"
"\n"
"/* local memory indices */\n"
"#define GET_LOCAL_INDEX_A(ROW,COL) ((ROW) + (COL)*((MACRO_TILE_NUM_ROWS)+(LOCAL_COL_PAD)) )\n"
"#define GET_LOCAL_INDEX_B(ROW,COL) ((COL) + (ROW)*((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) )\n"
"\n"
"/* data types */\n"
"#define DATA_TYPE_STR float\n"
"#define TYPE_MAD(MULA,MULB,DST) DST = mad(MULA,MULB,DST);\n"
"#define TYPE_MAD_WRITE(DST,ALPHA,REG,BETA) DST = (ALPHA)*(REG) + (BETA)*(DST);\n"
"\n"
"/* 8x4 micro-tile */\n"
"#define MICRO_TILE \\\n"
"  rA[0] = localA[offA + 0*WG_NUM_ROWS]; \\\n"
"  rA[1] = localA[offA + 1*WG_NUM_ROWS]; \\\n"
"  rA[2] = localA[offA + 2*WG_NUM_ROWS]; \\\n"
"  rA[3] = localA[offA + 3*WG_NUM_ROWS]; \\\n"
"  rA[4] = localA[offA + 4*WG_NUM_ROWS]; \\\n"
"  rA[5] = localA[offA + 5*WG_NUM_ROWS]; \\\n"
"  rA[6] = localA[offA + 6*WG_NUM_ROWS]; \\\n"
"  rA[7] = localA[offA + 7*WG_NUM_ROWS]; \\\n"
"  rB[0] = localB[offB + 0*WG_NUM_COLS]; \\\n"
"  rB[1] = localB[offB + 1*WG_NUM_COLS]; \\\n"
"  rB[2] = localB[offB + 2*WG_NUM_COLS]; \\\n"
"  rB[3] = localB[offB + 3*WG_NUM_COLS]; \\\n"
"  offA += (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD); \\\n"
"  offB += (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD); \\\n"
"  TYPE_MAD(rA[0],rB[0],rC[0][0]); \\\n"
"  TYPE_MAD(rA[0],rB[1],rC[0][1]); \\\n"
"  TYPE_MAD(rA[0],rB[2],rC[0][2]); \\\n"
"  TYPE_MAD(rA[0],rB[3],rC[0][3]); \\\n"
"  TYPE_MAD(rA[1],rB[0],rC[1][0]); \\\n"
"  TYPE_MAD(rA[1],rB[1],rC[1][1]); \\\n"
"  TYPE_MAD(rA[1],rB[2],rC[1][2]); \\\n"
"  TYPE_MAD(rA[1],rB[3],rC[1][3]); \\\n"
"  TYPE_MAD(rA[2],rB[0],rC[2][0]); \\\n"
"  TYPE_MAD(rA[2],rB[1],rC[2][1]); \\\n"
"  TYPE_MAD(rA[2],rB[2],rC[2][2]); \\\n"
"  TYPE_MAD(rA[2],rB[3],rC[2][3]); \\\n"
"  TYPE_MAD(rA[3],rB[0],rC[3][0]); \\\n"
"  TYPE_MAD(rA[3],rB[1],rC[3][1]); \\\n"
"  TYPE_MAD(rA[3],rB[2],rC[3][2]); \\\n"
"  TYPE_MAD(rA[3],rB[3],rC[3][3]); \\\n"
"  TYPE_MAD(rA[4],rB[0],rC[4][0]); \\\n"
"  TYPE_MAD(rA[4],rB[1],rC[4][1]); \\\n"
"  TYPE_MAD(rA[4],rB[2],rC[4][2]); \\\n"
"  TYPE_MAD(rA[4],rB[3],rC[4][3]); \\\n"
"  TYPE_MAD(rA[5],rB[0],rC[5][0]); \\\n"
"  TYPE_MAD(rA[5],rB[1],rC[5][1]); \\\n"
"  TYPE_MAD(rA[5],rB[2],rC[5][2]); \\\n"
"  TYPE_MAD(rA[5],rB[3],rC[5][3]); \\\n"
"  TYPE_MAD(rA[6],rB[0],rC[6][0]); \\\n"
"  TYPE_MAD(rA[6],rB[1],rC[6][1]); \\\n"
"  TYPE_MAD(rA[6],rB[2],rC[6][2]); \\\n"
"  TYPE_MAD(rA[6],rB[3],rC[6][3]); \\\n"
"  TYPE_MAD(rA[7],rB[0],rC[7][0]); \\\n"
"  TYPE_MAD(rA[7],rB[1],rC[7][1]); \\\n"
"  TYPE_MAD(rA[7],rB[2],rC[7][2]); \\\n"
"  TYPE_MAD(rA[7],rB[3],rC[7][3]); \\\n"
"  mem_fence(CLK_LOCAL_MEM_FENCE);\n"
"\n"
"__attribute__((reqd_work_group_size(WG_NUM_COLS,WG_NUM_ROWS,1)))\n"
"__kernel void sgemm_NT_128_001_1_16x16_8x4_ColMajor_BETA(\n"
"  uint const M,\n"
"  uint const N,\n"
"  uint const K,\n"
"  DATA_TYPE_STR const alpha,\n"
"  DATA_TYPE_STR const beta,\n"
"  __global DATA_TYPE_STR const * restrict A,\n"
"  __global DATA_TYPE_STR const * restrict B,\n"
"  __global DATA_TYPE_STR       *          C,\n"
"  uint const lda,\n"
"  uint const ldb,\n"
"  uint const ldc,\n"
"  uint const offsetA,\n"
"  uint const offsetB,\n"
"  uint const offsetC\n"
") {\n"
"\n"
"  /* apply offsets */\n"
"  A += offsetA;\n"
"  B += offsetB;\n"
"  C += offsetC;\n"
"\n"
"  /* allocate registers */\n"
"  DATA_TYPE_STR rC[MICRO_TILE_NUM_ROWS][MICRO_TILE_NUM_COLS] = {0};\n"
"  DATA_TYPE_STR rA[MICRO_TILE_NUM_ROWS];\n"
"  DATA_TYPE_STR rB[MICRO_TILE_NUM_COLS];\n"
"\n"
"  /* allocate local memory */\n"
"  __local DATA_TYPE_STR localA[NUM_UNROLL_ITER*(MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD)];\n"
"  __local DATA_TYPE_STR localB[NUM_UNROLL_ITER*(MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD)];\n"
"\n"
"  /* work item indices */\n"
"  uint groupRow = get_group_id(0);\n"
"  uint groupCol = N / 64; // last column\n"
"  uint localRow = get_local_id(0);\n"
"  uint localCol = get_local_id(1);\n"
"  uint localSerial = localRow + localCol*WG_NUM_ROWS;\n"
"\n"
"  /* global indices being loaded */\n"
"#define globalARow(LID) (groupRow*MACRO_TILE_NUM_ROWS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_ROWS)\n"
"#define globalACol(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_ROWS)\n"
"#define globalBRow(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_COLS)\n"
"#define globalBCol(LID) (groupCol*MACRO_TILE_NUM_COLS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_COLS)\n"
"\n"
"  /* loop over k */\n"
"  uint block_k = K / NUM_UNROLL_ITER;\n"
"  do {\n"
"\n"
"    /* local indices being written */\n"
"#define localARow (localSerial % MACRO_TILE_NUM_ROWS)\n"
"#define localACol (localSerial / MACRO_TILE_NUM_ROWS)\n"
"#define localAStride (WG_NUM_ROWS*WG_NUM_COLS)\n"
"#define localBRow ( localSerial / MACRO_TILE_NUM_COLS )\n"
"#define localBCol ( localSerial % MACRO_TILE_NUM_COLS )\n"
"#define localBStride  (WG_NUM_ROWS*WG_NUM_COLS)\n"
"    __local DATA_TYPE_STR *lA = localA + GET_LOCAL_INDEX_A(localARow, localACol);\n"
"    __local DATA_TYPE_STR *lB = localB + GET_LOCAL_INDEX_B(localBRow, localBCol);\n"
"    barrier(CLK_LOCAL_MEM_FENCE);\n"
"\n"
"    /* load global -> local */\n"
"    if (localSerial < (WG_NUM_ROWS*MICRO_TILE_NUM_ROWS*NUM_UNROLL_ITER) ) {\n"
"      lA[ 0*localAStride ] = A[ GET_GLOBAL_INDEX_A( globalARow(0), globalACol(0) ) ];\n"
"    }\n"
"    if (localSerial < (WG_NUM_COLS*MICRO_TILE_NUM_COLS*NUM_UNROLL_ITER) ) {\n"
"      lB[ 0*localBStride ] = (globalBCol(0) >= N) ? 0.0 : B[ GET_GLOBAL_INDEX_B( globalBRow(0), globalBCol(0) ) ];\n"
"    }\n"
"    barrier(CLK_LOCAL_MEM_FENCE);\n"
"    uint offA = localRow;\n"
"    uint offB = localCol;\n"
"\n"
"    /* do mads */\n"
"    MICRO_TILE\n"
"\n"
"    /* shift to next k block */\n"
"    A += lda*NUM_UNROLL_ITER;\n"
"    B += ldb*NUM_UNROLL_ITER;\n"
"\n"
"  } while (--block_k > 0);\n"
"\n"
"\n"
"  /* which global Cij index */\n"
"  uint globalCRow = groupRow * MACRO_TILE_NUM_ROWS + localRow;\n"
"  uint globalCCol = groupCol * MACRO_TILE_NUM_COLS + localCol;\n"
"\n"
"  /* write global Cij */\n"
"  if (globalCCol+0*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[0][0], beta )}\n"
"  if (globalCCol+1*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[0][1], beta )}\n"
"  if (globalCCol+2*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[0][2], beta )}\n"
"  if (globalCCol+3*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[0][3], beta )}\n"
"  if (globalCCol+0*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[1][0], beta )}\n"
"  if (globalCCol+1*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[1][1], beta )}\n"
"  if (globalCCol+2*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[1][2], beta )}\n"
"  if (globalCCol+3*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[1][3], beta )}\n"
"  if (globalCCol+0*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+2*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[2][0], beta )}\n"
"  if (globalCCol+1*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+2*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[2][1], beta )}\n"
"  if (globalCCol+2*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+2*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[2][2], beta )}\n"
"  if (globalCCol+3*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+2*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[2][3], beta )}\n"
"  if (globalCCol+0*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+3*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[3][0], beta )}\n"
"  if (globalCCol+1*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+3*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[3][1], beta )}\n"
"  if (globalCCol+2*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+3*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[3][2], beta )}\n"
"  if (globalCCol+3*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+3*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[3][3], beta )}\n"
"  if (globalCCol+0*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+4*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[4][0], beta )}\n"
"  if (globalCCol+1*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+4*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[4][1], beta )}\n"
"  if (globalCCol+2*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+4*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[4][2], beta )}\n"
"  if (globalCCol+3*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+4*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[4][3], beta )}\n"
"  if (globalCCol+0*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+5*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[5][0], beta )}\n"
"  if (globalCCol+1*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+5*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[5][1], beta )}\n"
"  if (globalCCol+2*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+5*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[5][2], beta )}\n"
"  if (globalCCol+3*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+5*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[5][3], beta )}\n"
"  if (globalCCol+0*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+6*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[6][0], beta )}\n"
"  if (globalCCol+1*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+6*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[6][1], beta )}\n"
"  if (globalCCol+2*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+6*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[6][2], beta )}\n"
"  if (globalCCol+3*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+6*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[6][3], beta )}\n"
"  if (globalCCol+0*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+7*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[7][0], beta )}\n"
"  if (globalCCol+1*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+7*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[7][1], beta )}\n"
"  if (globalCCol+2*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+7*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[7][2], beta )}\n"
"  if (globalCCol+3*WG_NUM_COLS < N){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+7*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[7][3], beta )}\n"
"\n"
"}\n"
"";

#endif
