/*******************************************************************************
 * This file was auto-generated using the auto-gemm.py python script.
 * NO NOT modify this file! Instead, make changes to
 *   clBLAS/src/scripts/auto-gemm/auto-gemm.py then re-generate files
 *   (otherwise local changes will be lost after re-generation).
 * - David Tanner
 ******************************************************************************/

#ifndef ZGEMM_NN_032_032_1_16X16_2X2_COLMAJOR_SRC_H
#define ZGEMM_NN_032_032_1_16X16_2X2_COLMAJOR_SRC_H

static const char * const zgemm_NN_032_032_1_16x16_2x2_ColMajor_src ="\n"
"/* zgemm_NN_032_032_1_16x16_2x2_ColMajor */\n"
"\n"
"/* kernel parameters */\n"
"#define COLUMN_MAJOR          1\n"
"#define TRANSPOSE_A           0\n"
"#define TRANSPOSE_B           0\n"
"\n"
"#define WG_NUM_ROWS          16\n"
"#define WG_NUM_COLS          16\n"
"#define MICRO_TILE_NUM_ROWS  2\n"
"#define MICRO_TILE_NUM_COLS  2\n"
"#define MACRO_TILE_NUM_ROWS  32\n"
"#define MACRO_TILE_NUM_COLS  32\n"
"#define NUM_UNROLL_ITER      1\n"
"\n"
"#define LOCAL_ROW_PAD        0\n"
"#define LOCAL_COL_PAD        0\n"
"\n"
"/* global memory indices */\n"
"#define GET_GLOBAL_INDEX_A(ROW,COL) ((COL)*lda+(ROW))\n"
"#define GET_GLOBAL_INDEX_B(ROW,COL) ((COL)*ldb+(ROW))\n"
"#define GET_GLOBAL_INDEX_C(ROW,COL) ((COL)*ldc+(ROW))\n"
"\n"
"/* local memory indices */\n"
"#define GET_LOCAL_INDEX_A(ROW,COL) ((ROW) + (COL)*((MACRO_TILE_NUM_ROWS)+(LOCAL_COL_PAD)) )\n"
"#define GET_LOCAL_INDEX_B(ROW,COL) ((COL) + (ROW)*((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) )\n"
"\n"
"/* data types */\n"
"#define DATA_TYPE_STR double2\n"
"#define TYPE_MAD(MULA,MULB,DST) \\\n"
"  DST.s0 = mad(  MULA.s0, MULB.s0, DST.s0 ); \\\n"
"  DST.s0 = mad( -MULA.s1, MULB.s1, DST.s0 ); \\\n"
"  DST.s1 = mad(  MULA.s0, MULB.s1, DST.s1 ); \\\n"
"  DST.s1 = mad(  MULA.s1, MULB.s0, DST.s1 );\n"
"#define TYPE_MAD_WRITE( DST, ALPHA, REG, BETA ) \\\n"
"  /* (1) */ \\\n"
"  type_mad_tmp = REG.s0; \\\n"
"  REG.s0 *= ALPHA.s0; \\\n"
"  REG.s0 = mad( -ALPHA.s1, REG.s1, REG.s0 ); \\\n"
"  REG.s1 *= ALPHA.s0; \\\n"
"  REG.s1 = mad(  ALPHA.s1, type_mad_tmp, REG.s1 ); \\\n"
"  /* (2) */ \\\n"
"  REG.s0 = mad(  BETA.s0, DST.s0, REG.s0 ); \\\n"
"  REG.s0 = mad( -BETA.s1, DST.s1, REG.s0 ); \\\n"
"  REG.s1 = mad(  BETA.s1, DST.s0, REG.s1 ); \\\n"
"  REG.s1 = mad(  BETA.s0, DST.s1, REG.s1 ); \\\n"
"  /* (3) */ \\\n"
"  DST = REG;\n"
"\n"
"/* 2x2 micro-tile */\n"
"#define MICRO_TILE \\\n"
"  rA[0] = localA[offA + 0*WG_NUM_ROWS]; \\\n"
"  rA[1] = localA[offA + 1*WG_NUM_ROWS]; \\\n"
"  rB[0] = localB[offB + 0*WG_NUM_COLS]; \\\n"
"  rB[1] = localB[offB + 1*WG_NUM_COLS]; \\\n"
"  offA += (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD); \\\n"
"  offB += (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD); \\\n"
"  TYPE_MAD(rA[0],rB[0],rC[0][0]); \\\n"
"  TYPE_MAD(rA[0],rB[1],rC[0][1]); \\\n"
"  TYPE_MAD(rA[1],rB[0],rC[1][0]); \\\n"
"  TYPE_MAD(rA[1],rB[1],rC[1][1]); \\\n"
"  mem_fence(CLK_LOCAL_MEM_FENCE);\n"
"\n"
"__attribute__((reqd_work_group_size(WG_NUM_COLS,WG_NUM_ROWS,1)))\n"
"__kernel void zgemm_NN_032_032_1_16x16_2x2_ColMajor(\n"
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
"  uint groupCol = get_group_id(1);\n"
"  uint localRow = get_local_id(0);\n"
"  uint localCol = get_local_id(1);\n"
"  uint localSerial = localRow + localCol*WG_NUM_ROWS;\n"
"\n"
"  /* global indices being loaded */\n"
"#define globalARow(LID) (groupRow*MACRO_TILE_NUM_ROWS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%MACRO_TILE_NUM_ROWS)\n"
"#define globalACol(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/MACRO_TILE_NUM_ROWS)\n"
"#define globalBRow(LID) ((localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)%NUM_UNROLL_ITER)\n"
"#define globalBCol(LID) (groupCol*MACRO_TILE_NUM_COLS + (localSerial+(LID)*WG_NUM_ROWS*WG_NUM_COLS)/NUM_UNROLL_ITER)\n"
"\n"
"  /* loop over k */\n"
"  uint block_k = K / NUM_UNROLL_ITER;\n"
"  do {\n"
"\n"
"    /* local indices being written */\n"
"#define localARow (localSerial % MACRO_TILE_NUM_ROWS)\n"
"#define localACol (localSerial / MACRO_TILE_NUM_ROWS)\n"
"#define localAStride (WG_NUM_ROWS*WG_NUM_COLS)\n"
"#define localBRow ( localSerial % NUM_UNROLL_ITER )\n"
"#define localBCol ( localSerial / NUM_UNROLL_ITER )\n"
"#define localBStride (WG_NUM_ROWS*WG_NUM_COLS/NUM_UNROLL_ITER)\n"
"    __local DATA_TYPE_STR *lA = localA + GET_LOCAL_INDEX_A(localARow, localACol);\n"
"    __local DATA_TYPE_STR *lB = localB + GET_LOCAL_INDEX_B(localBRow, localBCol);\n"
"    barrier(CLK_LOCAL_MEM_FENCE);\n"
"\n"
"    /* load global -> local */\n"
"    if (localSerial < (WG_NUM_ROWS*MICRO_TILE_NUM_ROWS*NUM_UNROLL_ITER) ) {\n"
"      lA[ 0*localAStride ] = A[ GET_GLOBAL_INDEX_A( globalARow(0), globalACol(0) ) ];\n"
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
"\n"
"    /* shift to next k block */\n"
"    A += lda*NUM_UNROLL_ITER;\n"
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
"  double type_mad_tmp;\n"
"  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[0][0], beta )\n"
"  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[0][1], beta )\n"
"  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[1][0], beta )\n"
"  TYPE_MAD_WRITE( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[1][1], beta )\n"
"\n"
"}\n"
"";

#endif
