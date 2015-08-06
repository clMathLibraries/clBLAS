/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_ZGEMM_COL_NT_B1_MX032_NX064_KX08_SRC_H
#define KERNEL_ZGEMM_COL_NT_B1_MX032_NX064_KX08_SRC_H

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

const unsigned int zgemm_Col_NT_B1_MX032_NX064_KX08_workGroupNumRows = 16;
const unsigned int zgemm_Col_NT_B1_MX032_NX064_KX08_workGroupNumCols = 16;
const unsigned int zgemm_Col_NT_B1_MX032_NX064_KX08_microTileNumRows = 4;
const unsigned int zgemm_Col_NT_B1_MX032_NX064_KX08_microTileNumCols = 2;
const unsigned int zgemm_Col_NT_B1_MX032_NX064_KX08_unroll = 8;

static const char * const sgemm_Col_NT_B1_MX032_NX064_KX08_src = STRINGIFY(

// convert preprocs to ints for comparison
\n
#define _S_ 1\n
#define _D_ 2\n
#define _C_ 3\n
#define _Z_ 4\n

/*******************************************************************************
 * Pre-Processor "Strings"
 ******************************************************************************/
\n
#define COLUMN_MAJOR_STR      ColMajor\n
#define ROW_MAJOR_STR         RowMajor\n

/*******************************************************************************
 * Kernel PreProcessor Definitions
 ******************************************************************************/
\n
#define WG_NUM_ROWS           16\n
#define WG_NUM_COLS           16\n
#define MICRO_TILE_NUM_ROWS   2\n
#define MICRO_TILE_NUM_COLS   4\n
#define NUM_UNROLL_ITER       8\n
#define ORDER                 ColMajor\n
#define TRANSPOSE_A           N\n
#define TRANSPOSE_B           T\n
#define DATA_TYPE             _Z_\n
\n
#define MACRO_TILE_NUM_ROWS   32\n
#define MACRO_TILE_NUM_COLS   64\n
#define LOCAL_ROW_PAD         1\n
#define LOCAL_COL_PAD         1\n


/*******************************************************************************
 * Global Memory Indices
 * Note: (a==b)==(c==d) means if both are true or neither is true
 ******************************************************************************/

/* col-major non-transposed
 * row-major transposed */
\n
#define GET_GLOBAL_INDEX_N(ROW,COL,STRIDE) ((COL)*(STRIDE)+(ROW))\n

/* col-major transposed
 * row-major non-transposed */
\n
#define GET_GLOBAL_INDEX_T(ROW,COL,STRIDE) ((ROW)*(STRIDE)+(COL))\n

// global A
\n
#if (ORDER==COLUMN_MAJOR_STR) == (TRANSPOSE_A==N)\n
#define GET_GLOBAL_INDEX_A(ROW,COL) GET_GLOBAL_INDEX_N((ROW),(COL),(lda))\n
#else\n
#define GET_GLOBAL_INDEX_A(ROW,COL) GET_GLOBAL_INDEX_T((ROW),(COL),(lda))\n
#endif\n

// global B
\n
#if (ORDER==COLUMN_MAJOR_STR) == (TRANSPOSE_B==N)\n
#define GET_GLOBAL_INDEX_B(ROW,COL) GET_GLOBAL_INDEX_T((ROW),(COL),(ldb))\n
#else\n
#define GET_GLOBAL_INDEX_B(ROW,COL) GET_GLOBAL_INDEX_N((ROW),(COL),(ldb))\n
#endif\n

// global C
#if (ORDER==COLUMN_MAJOR_STR)\n
#define GET_GLOBAL_INDEX_C(ROW,COL) GET_GLOBAL_INDEX_N((ROW),(COL),(ldc))\n
#else\n
#define GET_GLOBAL_INDEX_C(ROW,COL) GET_GLOBAL_INDEX_T((ROW),(COL),(ldc))\n
#endif\n

/*******************************************************************************
 * Local Memory Indices
 ******************************************************************************/

// localA - rotated 90 degrees from B but use same accessor unless slow
\n
#define GET_LOCAL_INDEX_A(ROW,COL) (ROW + COL*(MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD) )\n
#define GET_LOCAL_STEP_A ( ((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) \
    * ((WG_NUM_ROWS)*(WG_NUM_COLS)/(MACRO_TILE_NUM_COLS)))\n

// localB
\n
#define GET_LOCAL_INDEX_B(ROW,COL) ((COL) + (ROW)*((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) )\n
#define GET_LOCAL_STEP_B ( ((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) \
    * ((WG_NUM_ROWS)*(WG_NUM_COLS)/(MACRO_TILE_NUM_COLS)))\n

/*******************************************************************************
 * Data Types
 ******************************************************************************/

// single precision
#if DATA_TYPE==_S_\n
#define DATA_TYPE_STR         float\n
#define DATA_TYPE_CHAR        s\n
#define TYPE_MAD(MUL0,MUL1,DST) DST = mad(MUL0,MUL1,DST);\n
#define TYPE_MAD2( DST, ALPHA, REG, BETA ) DST = (ALPHA)*(REG) + (BETA)*(DST);\n

// double precision
#elif DATA_TYPE==_D_\n
#define DATA_TYPE_STR         double\n
#define DATA_TYPE_CHAR        d\n
#define TYPE_MAD(MUL0,MUL1,DST) DST = mad(MUL0,MUL1,DST);\n
#define TYPE_MAD2( DST, ALPHA, REG, BETA ) DST = (ALPHA)*(REG) + (BETA)*(DST);\n

// complex single precision
#elif DATA_TYPE==_C_\n
#define DATA_TYPE_STR         float2\n
#define DATA_TYPE_CHAR        c\n
#define TYPE_MAD(MUL0,MUL1,DST) \
  DST.s0 = mad(  MUL0.s0, MUL1.s0, DST.s0 ); \
  DST.s0 = mad( -MUL0.s1, MUL1.s1, DST.s0 ); \
  DST.s1 = mad(  MUL0.s0, MUL1.s1, DST.s1 ); \
  DST.s1 = mad(  MUL0.s1, MUL1.s0, DST.s1 );\n
#define TYPE_MAD2( DST, ALPHA, REG, BETA ) \
  /* (1) */ \
  type_mad2_tmp = REG.s0; \
  REG.s0 *= ALPHA.s0; \
  REG.s0 = mad( -ALPHA.s1, REG.s1, REG.s0 ); \
  REG.s1 *= ALPHA.s0; \
  REG.s1 = mad(  ALPHA.s1, type_mad2_tmp, REG.s1 ); \
  /* (2) */ \
  REG.s0 = mad(  BETA.s0, DST.s0, REG.s0 ); \
  REG.s0 = mad( -BETA.s1, DST.s1, REG.s0 ); \
  REG.s1 = mad(  BETA.s1, DST.s0, REG.s1 ); \
  REG.s1 = mad(  BETA.s0, DST.s1, REG.s1 ); \
  /* (3) */ \
  DST = REG;\n

// complex double precision
#else\n
#define DATA_TYPE_STR         double2\n
#define DATA_TYPE_CHAR        z\n
#define TYPE_MAD(MUL0,MUL1,DST) \
  DST.s0 = mad(  MUL0.s0, MUL1.s0, DST.s0 ); \
  DST.s0 = mad( -MUL0.s1, MUL1.s1, DST.s0 ); \
  DST.s1 = mad(  MUL0.s0, MUL1.s1, DST.s1 ); \
  DST.s1 = mad(  MUL0.s1, MUL1.s0, DST.s1 );\n
#define TYPE_MAD2( DST, ALPHA, REG, BETA ) \
  /* (1) */ \
  type_mad2_tmp = REG.s0; \
  REG.s0 *= ALPHA.s0; \
  REG.s0 = mad( -ALPHA.s1, REG.s1, REG.s0 ); \
  REG.s1 *= ALPHA.s0; \
  REG.s1 = mad(  ALPHA.s1, type_mad2_tmp, REG.s1 ); \
  /* (2) */ \
  REG.s0 = mad(  BETA.s0, DST.s0, REG.s0 ); \
  REG.s0 = mad( -BETA.s1, DST.s1, REG.s0 ); \
  REG.s1 = mad(  BETA.s1, DST.s0, REG.s1 ); \
  REG.s1 = mad(  BETA.s0, DST.s1, REG.s1 ); \
  /* (3) */ \
  DST = REG;\n
\n
#endif\n

/*******************************************************************************
 * 2x4 micro tile
 ******************************************************************************/
#define MAD2x4 \
  rA[0] = localA[offA + 0*WG_NUM_ROWS]; \
  rA[1] = localA[offA + 1*WG_NUM_ROWS]; \
  rB[0] = localB[offB + 0*WG_NUM_COLS]; \
  rB[1] = localB[offB + 1*WG_NUM_COLS]; \
  rB[2] = localB[offB + 2*WG_NUM_COLS]; \
  rB[3] = localB[offB + 3*WG_NUM_COLS]; \
  offA += (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD); \
  offB += (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD); \
  TYPE_MAD(rA[0],rB[0],rC[0][0]); \
  TYPE_MAD(rA[1],rB[0],rC[1][0]); \
  TYPE_MAD(rA[0],rB[1],rC[0][1]); \
  TYPE_MAD(rA[1],rB[1],rC[1][1]); \
  TYPE_MAD(rA[0],rB[2],rC[0][2]); \
  TYPE_MAD(rA[1],rB[2],rC[1][2]); \
  TYPE_MAD(rA[0],rB[3],rC[0][3]); \
  TYPE_MAD(rA[1],rB[3],rC[1][3]); \
  mem_fence(CLK_LOCAL_MEM_FENCE);\n

// concatenate kernel name
// zgemm_NT_64_32_8_16x16_2x4__ALPHABETA
#define CONCAT_NAME(DT,TA,TB,TILE_COLS,TILE_ROWS,NUI,WGR,WGC,MTR,MTC) \
  DT ## gemm_ ## TA ## TB ## _ ## TILE_COLS ## _ ## TILE_ROWS ## _ ## NUI ## _ ## WGR ## x ## WGC ## _ ## MTR ## x ## MTC ## __ALPHABETA\n
#define KERNEL_NAME(DT,TA,TB,TILE_COLS,TILE_ROWS,NUI,WGR,WGC,MTR,MTC) CONCAT_NAME(DT,TA,TB,TILE_COLS,TILE_ROWS,NUI,WGR,WGC,MTR,MTC)\n

/*******************************************************************************
 * Kernel
 ******************************************************************************/
__attribute__((reqd_work_group_size(WG_NUM_COLS,WG_NUM_ROWS,1)))
__kernel void KERNEL_NAME(DATA_TYPE_CHAR,TRANSPOSE_A,TRANSPOSE_B,MACRO_TILE_NUM_COLS,MACRO_TILE_NUM_ROWS,NUM_UNROLL_ITER,WG_NUM_ROWS,WG_NUM_COLS,MICRO_TILE_NUM_ROWS,MICRO_TILE_NUM_COLS) ( 
  uint const M,
  uint const N,
  uint const K,
  DATA_TYPE_STR const alpha,
  DATA_TYPE_STR const beta,
  __global DATA_TYPE_STR const * restrict A,
  __global DATA_TYPE_STR const * restrict B,
  __global DATA_TYPE_STR       *          C,
  uint const lda,
  uint const ldb,
  uint const ldc,
  uint const offsetA,
  uint const offsetB,
  uint const offsetC )
{
  // apply offsets
  A += offsetA;
  B += offsetB;
  C += offsetC;

  // registers
  DATA_TYPE_STR rC[MICRO_TILE_NUM_ROWS][MICRO_TILE_NUM_COLS]  = {0};
  DATA_TYPE_STR rA[MICRO_TILE_NUM_ROWS];
  DATA_TYPE_STR rB[MICRO_TILE_NUM_COLS];
    
  // local memory
  __local DATA_TYPE_STR localA[NUM_UNROLL_ITER*(MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD)];
  __local DATA_TYPE_STR localB[NUM_UNROLL_ITER*(MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD)];

/*  
 * for coalesced C writing
 * if column major, id(0) is row
 * if row major, id(0) is col
 */
  uint groupRow = get_group_id(0);
  uint groupCol = get_group_id(1);
  uint localRow = get_local_id(0);
  uint localCol = get_local_id(1);
  uint localSerial = localRow + localCol*WG_NUM_ROWS;

  /*****************************************************************************
   * global indices being loaded
   ****************************************************************************/
  // which gAij is this thread responsible for loading?
\n
#define globalARow (groupRow*MACRO_TILE_NUM_ROWS + localSerial%MACRO_TILE_NUM_ROWS)\n
#define globalACol (localSerial/MACRO_TILE_NUM_ROWS)\n
#define globalAIdx (GET_GLOBAL_INDEX_A( globalARow, globalACol ) )\n
  A += globalAIdx;
  // which gBij is this thread responsible for loading?
#define globalBRow (localSerial/MACRO_TILE_NUM_COLS)\n
#define globalBCol (groupCol*MACRO_TILE_NUM_COLS + localSerial%MACRO_TILE_NUM_COLS)\n
#define globalBIdx (GET_GLOBAL_INDEX_B( globalBRow, globalBCol ) )\n
  B += globalBIdx;

  uint block_k = K / NUM_UNROLL_ITER;
#pragma nounroll
  do {

    /***************************************************************************
     * local indices being written
     **************************************************************************/
    // which lAij is this thread responsible for writing?
\n
#define localARow (localSerial % MACRO_TILE_NUM_ROWS)\n
#define localACol (localSerial / MACRO_TILE_NUM_ROWS)\n
#define localAStride ( (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD) * (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_ROWS) )\n
#define globalAStride ( GET_GLOBAL_INDEX_A(0, (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_ROWS) ) )\n
#define localAIdx ( GET_LOCAL_INDEX_A(localARow, localACol) )\n
    __local DATA_TYPE_STR *lA = localA + localAIdx;
    // which lBij is this thread responsible for writing?
\n
#define localBRow ( localSerial / MACRO_TILE_NUM_COLS )\n
#define localBCol ( localSerial % MACRO_TILE_NUM_COLS )\n
#define localBIdx ( GET_LOCAL_INDEX_B(localBRow, localBCol) )\n
#define localBStride  ( (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD) * (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_COLS) )\n
#define globalBStride ( GET_GLOBAL_INDEX_B( (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_COLS), 0 ) )\n
    __local DATA_TYPE_STR *lB = localB + localBIdx;
    barrier(CLK_LOCAL_MEM_FENCE);

    /***************************************************************************
     * Load global -> local
     * num loads = num threads / total loads
     **************************************************************************/
    // 2x4 uTile x 8unroll
    lA[ 0*localAStride ] = A[ 0*globalAStride ];
    lB[ 0*localBStride ] = B[ 0*globalBStride ];
    lB[ 1*localBStride ] = B[ 1*globalBStride ];
    barrier(CLK_LOCAL_MEM_FENCE);

    uint offA = localRow;
    uint offB = localCol;

    /***************************************************************************
     * do mads in registers
     **************************************************************************/
    MAD2x4
    MAD2x4
    MAD2x4
    MAD2x4
    MAD2x4
    MAD2x4
    MAD2x4
    MAD2x4

    // fully shift
    A += lda*NUM_UNROLL_ITER; // b/c N
    B += ldb*NUM_UNROLL_ITER; // b/c T

  } while (--block_k > 0);

  // which global Cij is this thread responsible for computing?
  uint globalCRow = groupRow * MACRO_TILE_NUM_ROWS + localRow;
  uint globalCCol = groupCol * MACRO_TILE_NUM_COLS + localCol;

  /***************************************************************************
   * write data
   **************************************************************************/
  double type_mad2_tmp; // used in TYPE_MAD2
  TYPE_MAD2( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[0][0], beta )
  TYPE_MAD2( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[0][1], beta )
  TYPE_MAD2( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[0][2], beta )
  TYPE_MAD2( C[ GET_GLOBAL_INDEX_C( globalCRow+0*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[0][3], beta )
  TYPE_MAD2( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+0*WG_NUM_COLS) ], alpha, rC[1][0], beta )
  TYPE_MAD2( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+1*WG_NUM_COLS) ], alpha, rC[1][1], beta )
  TYPE_MAD2( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+2*WG_NUM_COLS) ], alpha, rC[1][2], beta )
  TYPE_MAD2( C[ GET_GLOBAL_INDEX_C( globalCRow+1*WG_NUM_ROWS, globalCCol+3*WG_NUM_COLS) ], alpha, rC[1][3], beta )
   
}

);
