/*******************************************************************************
 * Notes:
 * for column major, id(0) is row so C data is coalesced
 * for row major, id(0) is col
 ******************************************************************************/

static const char * zgemm_NT_64_32_8_16x16_2x4__ALPHABETA = "


// convert preprocs to ints for comparison
#define _S_ 1
#define _D_ 2
#define _C_ 3
#define _Z_ 4

/*******************************************************************************
 * Pre-Processor "Strings"
 ******************************************************************************/
#define COLUMN_MAJOR_STR      ColMajor
#define ROW_MAJOR_STR         RowMajor

/*******************************************************************************
 * Kernel PreProcessor Definitions
 ******************************************************************************/
#define WG_NUM_ROWS           16
#define WG_NUM_COLS           16
#define MICRO_TILE_NUM_ROWS   2
#define MICRO_TILE_NUM_COLS   4
#define NUM_UNROLL_ITER       8
#define ORDER                 ColMajor
#define TRANSPOSE_A           N
#define TRANSPOSE_B           T
#define DATA_TYPE             _Z_

#define MACRO_TILE_NUM_ROWS   32
#define MACRO_TILE_NUM_COLS   64
// each row lengthened by this ammount
#define LOCAL_ROW_PAD         1
// each col lengthened by this ammount
#define LOCAL_COL_PAD         1


/*******************************************************************************
 * Global Memory Indices
 * Note: (a==b)==(c==d) means if both are true or neither is true
 ******************************************************************************/

/* col-major non-transposed
 * row-major transposed */
#define GET_GLOBAL_INDEX_N(ROW,COL,STRIDE) ((COL)*(STRIDE)+(ROW))

/* col-major transposed
 * row-major non-transposed */
#define GET_GLOBAL_INDEX_T(ROW,COL,STRIDE) ((ROW)*(STRIDE)+(COL))

// global A
#if (ORDER==COLUMN_MAJOR_STR) == (TRANSPOSE_A==N)
#define GET_GLOBAL_INDEX_A(ROW,COL) GET_GLOBAL_INDEX_N((ROW),(COL),(lda))
#else
#define GET_GLOBAL_INDEX_A(ROW,COL) GET_GLOBAL_INDEX_T((ROW),(COL),(lda))
#endif

// global B
#if (ORDER==COLUMN_MAJOR_STR) == (TRANSPOSE_B==N)
#define GET_GLOBAL_INDEX_B(ROW,COL) GET_GLOBAL_INDEX_T((ROW),(COL),(ldb))
#else
#define GET_GLOBAL_INDEX_B(ROW,COL) GET_GLOBAL_INDEX_N((ROW),(COL),(ldb))
#endif

// global C
#if (ORDER==COLUMN_MAJOR_STR)
#define GET_GLOBAL_INDEX_C(ROW,COL) GET_GLOBAL_INDEX_N((ROW),(COL),(ldc))
#else
#define GET_GLOBAL_INDEX_C(ROW,COL) GET_GLOBAL_INDEX_T((ROW),(COL),(ldc))
#endif

/*******************************************************************************
 * Local Memory Indices
 ******************************************************************************/

// localA - rotated 90 degrees from B but use same accessor unless slow
#define GET_LOCAL_INDEX_A(ROW,COL) (ROW + COL*(MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD) )
#define GET_LOCAL_STEP_A ( ((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) \
    * ((WG_NUM_ROWS)*(WG_NUM_COLS)/(MACRO_TILE_NUM_COLS))

// localB
#define GET_LOCAL_INDEX_B(ROW,COL) ((COL) + (ROW)*((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) )
#define GET_LOCAL_STEP_B ( ((MACRO_TILE_NUM_COLS)+(LOCAL_ROW_PAD)) \
    * ((WG_NUM_ROWS)*(WG_NUM_COLS)/(MACRO_TILE_NUM_COLS))

/*******************************************************************************
 * Data Types
 ******************************************************************************/

// single precision
#if DATA_TYPE==_S_
#define DATA_TYPE_STR         float
#define DATA_TYPE_CHAR        s
#define TYPE_MAD(MUL0,MUL1,DST) DST = mad(MUL0,MUL1,DST);
#define TYPE_MAD2( DST, ALPHA, REG, BETA ) DST = (ALPHA)*(REG) + (BETA)*(DST);

// double precision
#elif DATA_TYPE==_D_
#define DATA_TYPE_STR         double
#define DATA_TYPE_CHAR        d
#define TYPE_MAD(MUL0,MUL1,DST) DST = mad(MUL0,MUL1,DST);
#define TYPE_MAD2( DST, ALPHA, REG, BETA ) DST = (ALPHA)*(REG) + (BETA)*(DST);

// complex single precision
#elif DATA_TYPE==_C_
#define DATA_TYPE_STR         float2
#define DATA_TYPE_CHAR        c
#define TYPE_MAD(MUL0,MUL1,DST) \
  DST.s0 = mad(  MUL0.s0, MUL1.s0, DST.s0 ); \
  DST.s0 = mad( -MUL0.s1, MUL1.s1, DST.s0 ); \
  DST.s1 = mad(  MUL0.s0, MUL1.s1, DST.s1 ); \
  DST.s1 = mad(  MUL0.s1, MUL1.s0, DST.s1 );
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
  DST = REG;

// complex double precision
#else
#define DATA_TYPE_STR         double2
#define DATA_TYPE_CHAR        z
#define TYPE_MAD(MUL0,MUL1,DST) \
  DST.s0 = mad(  MUL0.s0, MUL1.s0, DST.s0 ); \
  DST.s0 = mad( -MUL0.s1, MUL1.s1, DST.s0 ); \
  DST.s1 = mad(  MUL0.s0, MUL1.s1, DST.s1 ); \
  DST.s1 = mad(  MUL0.s1, MUL1.s0, DST.s1 );
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
  DST = REG;

#endif

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
  mem_fence(CLK_LOCAL_MEM_FENCE);

// concatenate kernel name
// zgemm_NT_64_32_8_16x16_2x4__ALPHABETA
#define CONCAT_NAME(DT,TA,TB,TILE_COLS,TILE_ROWS,NUI,WGR,WGC,MTR,MTC) \
  DT ## gemm_ ## TA ## TB ## _ ## TILE_COLS ## _ ## TILE_ROWS ## _ ## NUI ## _ ## WGR ## x ## WGC ## _ ## MTR ## x ## MTC ## __ALPHABETA
#define KERNEL_NAME(DT,TA,TB,TILE_COLS,TILE_ROWS,NUI,WGR,WGC,MTR,MTC) CONCAT_NAME(DT,TA,TB,TILE_COLS,TILE_ROWS,NUI,WGR,WGC,MTR,MTC)

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
  DATA_TYPE_STR rC[MICRO_TILE_NUM_ROWS][MICRO_TILE_NUM_COLS]  = { {0} };
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
#define globalARow (groupRow*MACRO_TILE_NUM_ROWS + localSerial%MACRO_TILE_NUM_ROWS)
#define globalACol (localSerial/MACRO_TILE_NUM_ROWS)
#define globalAIdx (GET_GLOBAL_INDEX_A( globalARow, globalACol ) )
  A += globalAIdx;
  // which gBij is this thread responsible for loading?
#define globalBRow (localSerial/MACRO_TILE_NUM_COLS)
#define globalBCol (groupCol*MACRO_TILE_NUM_COLS + localSerial%MACRO_TILE_NUM_COLS)
#define globalBIdx (GET_GLOBAL_INDEX_B( globalBRow, globalBCol ) )
  B += globalBIdx;

  uint block_k = K / NUM_UNROLL_ITER;
#pragma nounroll
  do {

    /***************************************************************************
     * local indices being written
     **************************************************************************/
    // which lAij is this thread responsible for writing?
#define localARow (localSerial % MACRO_TILE_NUM_ROWS)
#define localACol (localSerial / MACRO_TILE_NUM_ROWS)
#define localAStride ( (MACRO_TILE_NUM_ROWS+LOCAL_COL_PAD) * (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_ROWS) )
#define globalAStride ( GET_GLOBAL_INDEX_A(0, (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_ROWS) ) )
#define localAIdx ( GET_LOCAL_INDEX_A(localARow, localACol) )
    __local DATA_TYPE_STR *lA = localA + localAIdx;
    // which lBij is this thread responsible for writing?
#define localBRow ( localSerial / MACRO_TILE_NUM_COLS )
#define localBCol ( localSerial % MACRO_TILE_NUM_COLS )
#define localBIdx ( GET_LOCAL_INDEX_B(localBRow, localBCol) )
#define localBStride  ( (MACRO_TILE_NUM_COLS+LOCAL_ROW_PAD) * (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_COLS) )
#define globalBStride ( GET_GLOBAL_INDEX_B( (WG_NUM_ROWS*WG_NUM_COLS/MACRO_TILE_NUM_COLS), 0 ) )
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

";
