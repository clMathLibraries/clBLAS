#ifndef DGEMM_NT_001_016_8_16X16_1X1_ROWMAJOR_BETA_SRC_H
#define DGEMM_NT_001_016_8_16X16_1X1_ROWMAJOR_BETA_SRC_H

static const char * const dgemm_NT_001_016_8_16x16_1x1_RowMajor_BETA_src ="\n"
"/* dgemm_NT_001_016_8_16x16_1x1_RowMajor_BETA */\n"
"\n"
"/* kernel parameters */\n"
"#define COLUMN_MAJOR          0\n"
"#define TRANSPOSE_A           0\n"
"#define TRANSPOSE_B           1\n"
"\n"
"#define WG_NUM_ROWS          16\n"
"#define WG_NUM_COLS          16\n"
"#define MICRO_TILE_NUM_ROWS  1\n"
"#define MICRO_TILE_NUM_COLS  1\n"
"#define MACRO_TILE_NUM_ROWS  16\n"
"#define MACRO_TILE_NUM_COLS  16\n"
"#define NUM_UNROLL_ITER      8\n"
"\n"
"#define LOCAL_ROW_PAD        0\n"
"#define LOCAL_COL_PAD        0\n"
"\n"
"/* global memory indices */\n"
"#define GET_GLOBAL_INDEX_A(ROW,COL) ((ROW)*lda+(COL))\n"
"#define GET_GLOBAL_INDEX_B(ROW,COL) ((COL)*ldb+(ROW))\n"
"#define GET_GLOBAL_INDEX_C(ROW,COL) ((ROW)*ldc+(COL))\n"
"\n"
"/* local memory indices */\n"
"#define GET_LOCAL_INDEX_A(ROW,COL) ((ROW) + (COL)*((MACRO_TILE_NUM_ROWS)+(LOCAL_COL_PAD)) )\n"
"#define GET_LOCAL_INDEX_B(ROW,COL) ((COL) + (ROW)*((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) )\n"
"\n"
"/* data types */\n"
"#define DATA_TYPE_STR double\n"
"#define TYPE_MAD(MULA,MULB,DST) DST = mad(MULA,MULB,DST);\n"
"#define TYPE_MAD_WRITE(DST,ALPHA,REG,BETA) DST = (ALPHA)*(REG) + (BETA)*(DST);\n"
"\n"
"/* 1x1 micro-tile */\n"
"#define MICRO_TILE \\\n"
"  rA[0] = localA[offA + 0*WG_NUM_ROWS]; \\\n"
"  rB[0] = localB[offB + 0*WG_NUM_COLS]; \\\n"
"  offA += (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD); \\\n"
"  offB += (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD); \\\n"
"  TYPE_MAD(rA[0],rB[0],rC[0][0]); \\\n"
"  mem_fence(CLK_LOCAL_MEM_FENCE);\n"
"\n"
"__attribute__((reqd_work_group_size(WG_NUM_COLS,WG_NUM_ROWS,1)))\n"
"__kernel void dgemm_NT_001_016_8_16x16_1x1_RowMajor_BETA(\n"
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
"  uint groupRow = M / 16; // last row\n"
"  uint groupCol = get_group_id(1);\n"
"  uint localRow = get_local_id(0);\n"
"  uint localCol = get_local_id(1);\n"
"  uint localSerial = localRow + localCol*WG_NUM_ROWS;\n"
"\n"
"  /* global indices being loaded */\n"
"#define globalARow(LID) (groupRow*MACRO_TILE_NUM_ROWS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER)\n"
"#define globalACol(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER)\n"
"#define globalBRow(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER)\n"
"#define globalBCol(LID) (groupCol*MACRO_TILE_NUM_COLS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER)\n"
"\n"
"  /* loop over k */\n"
"  uint block_k = K / NUM_UNROLL_ITER;\n"
"  do {\n"
"\n"
"    /* local indices being written */\n"
"#define localARow (localSerial / NUM_UNROLL_ITER)\n"
"#define localACol (localSerial % NUM_UNROLL_ITER)\n"
"#define localAStride (WG_NUM_ROWS*WG_NUM_COLS/NUM_UNROLL_ITER)\n"
"#define localBRow ( localSerial % NUM_UNROLL_ITER )\n"
"#define localBCol ( localSerial / NUM_UNROLL_ITER )\n"
"#define localBStride (WG_NUM_ROWS*WG_NUM_COLS/NUM_UNROLL_ITER)\n"
"    __local DATA_TYPE_STR *lA = localA + GET_LOCAL_INDEX_A(localARow, localACol);\n"
"    __local DATA_TYPE_STR *lB = localB + GET_LOCAL_INDEX_B(localBRow, localBCol);\n"
"    barrier(CLK_LOCAL_MEM_FENCE);\n"
"\n"
"    /* load global -> local */\n"
"    if (localSerial < (WG_NUM_ROWS*MICRO_TILE_NUM_ROWS*NUM_UNROLL_ITER) ) {\n"
"      lA[ 0*localAStride ] = ( globalARow(0) >= M) ? 0.0 : A[ GET_GLOBAL_INDEX_A( globalARow(0), globalACol(0) ) ];\n"
"    }\n"
"    if (localSerial < (WG_NUM_COLS*MICRO_TILE_NUM_COLS*NUM_UNROLL_ITER) ) {\n"
"      lB[ 0*localBStride ] = B[ GET_GLOBAL_INDEX_B( globalBRow(0), globalBCol(0) ) ];\n"
"    }\n"
"    barrier(CLK_LOCAL_MEM_FENCE);\n"
"    uint offA = localRow;\n"
"    uint offB = localCol;\n"
"\n"
"    /* do mads */\n"
"    MICRO_TILE\n"
"    MICRO_TILE\n"
"    MICRO_TILE\n"
"    MICRO_TILE\n"
"    MICRO_TILE\n"
"    MICRO_TILE\n"
"    MICRO_TILE\n"
"    MICRO_TILE\n"
"\n"
"    /* shift to next k block */\n"
"    A += NUM_UNROLL_ITER;\n"
"    B += NUM_UNROLL_ITER;\n"
"\n"
"  } while (--block_k > 0);\n"
"\n"
"\n"
"  /* which global Cij index */\n"
"  uint globalCRow = groupRow * MACRO_TILE_NUM_ROWS + localRow;\n"
"  uint globalCCol = groupCol * MACRO_TILE_NUM_COLS + localCol;\n"
"\n"
"  /* write global Cij */\n"
"  if (globalCRow+0*WG_NUM_ROWS < M){  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[0][0], beta )}\n"
"\n"
"}\n"
"";

#endif
