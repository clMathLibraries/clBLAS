/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DGEMM_NN_GFX906_TENSILE_SRC_H
#define KERNEL_DGEMM_NN_GFX906_TENSILE_SRC_H
// #pragma message("AutoGemm's dgemm_NN_gfx906_tensile_src overriden by user.")

const unsigned int dgemm_NN_gfx906_tensile_workGroupNumRows = 16;
const unsigned int dgemm_NN_gfx906_tensile_workGroupNumCols = 16;
const unsigned int dgemm_NN_gfx906_tensile_microTileNumRows = 4;
const unsigned int dgemm_NN_gfx906_tensile_microTileNumCols = 4;

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

//if precompiled is enabled. All hand tuned kerenls should be precompiled.
#ifndef AUTOGEMM_USE_PRE_COMPILED_KERNELS
unsigned char *dgemm_NN_gfx906_tensile_bin = 0;
size_t dgemm_NN_gfx906_tensile_binSize = 0;
#endif

const char * const dgemm_NN_gfx906_tensile_src = STRINGIFY(
/******************************************/
/* Function Prefix                        */
/******************************************/

/* tile parameters */
#define NUM_THREADS 256
#define SG0I 16
#define SG1J 16
#define TT0I 4
#define TT1J 4
#define MT0I (SG0I*TT0I)
#define MT1J (SG1J*TT1J)
#define VECTOR_WIDTH 2
#define GLOBAL_LOAD_VECTOR_WIDTH_A 1
#define GLOBAL_LOAD_VECTOR_WIDTH_B 1
#define GLOBAL_WRITE_VECTOR_WIDTH 2

/* DepthU parameters*/
#define CPSV (NUM_THREADS / MT0I * VECTOR_WIDTH)
#define LOCAL_SPLITU 1
#define UNROLL 4
#define LOCAL_DEPTHU (LOCAL_SPLITU*UNROLL)

/* other */
#define PAD 0
#define WORK_GROUP_MAPPING 2

/* num loads parallel and perpendicular to coalesced */
#define NLCA 1
#define NLCB 1
#define NLPA 1
#define NLPB 1

/* load sizes parallel and perpendicular to coalesced */
#define LSCA (MT0I/NLCA)
#define LSPA (LOCAL_DEPTHU/NLPA)
#define LSCB (LOCAL_DEPTHU/NLCB)
#define LSPB (MT1J/NLPB)
#define LVCA (LSCA/GLOBAL_LOAD_VECTOR_WIDTH_A)
#define LVCB (LSCB/GLOBAL_LOAD_VECTOR_WIDTH_B)
#define LVPA (LSPA/GLOBAL_LOAD_VECTOR_WIDTH_A)
#define LVPB (LSPB/GLOBAL_LOAD_VECTOR_WIDTH_B)
#define LDS_OFFSET_B 256
#define LDS_NUM_ELEMENTS 1024
#define LDS_OFFSET_BLK 512

/* global memory indices */
#define GLOBAL_C(IDX0I, IDX1J, IDXK) (( (IDX0I)*strideC0I + (IDX1J)*strideC1J + (IDXK)*strideCK ))
#define GLOBAL_OFFSET_A(IDX0I, IDXL, IDXK) (( (IDX0I)*strideA0I + (IDXL)*strideAL + (IDXK)*strideAK ))
#define GLOBAL_OFFSET_B(IDXL, IDX1J, IDXK) (( (IDXL)*strideBL + (IDX1J)*strideB1J + (IDXK)*strideBK ))

/* data types */
#define DATA_TYPE double
#define MAC(A,B,DST) mad(A,B,DST)

/* MAC's */
#define TYPE_MAC(MULA,MULB,DST) DST = MAC(MULA,MULB,DST);
#define TYPE_MAC_WRITE(DST,ALPHA,REG,BETA) DST = 0 != (BETA) ? (ALPHA)*(REG) + (BETA)*(DST) : (ALPHA)*(REG);

/* 4x4 micro-tile */
#define MAC_4x4 \
  TYPE_MAC(rA[0],rB[0],rC[0+0*TT0I]); \
  TYPE_MAC(rA[1],rB[0],rC[1+0*TT0I]); \
  TYPE_MAC(rA[2],rB[0],rC[2+0*TT0I]); \
  TYPE_MAC(rA[3],rB[0],rC[3+0*TT0I]); \
  TYPE_MAC(rA[0],rB[1],rC[0+1*TT0I]); \
  TYPE_MAC(rA[1],rB[1],rC[1+1*TT0I]); \
  TYPE_MAC(rA[2],rB[1],rC[2+1*TT0I]); \
  TYPE_MAC(rA[3],rB[1],rC[3+1*TT0I]); \
  TYPE_MAC(rA[0],rB[2],rC[0+2*TT0I]); \
  TYPE_MAC(rA[1],rB[2],rC[1+2*TT0I]); \
  TYPE_MAC(rA[2],rB[2],rC[2+2*TT0I]); \
  TYPE_MAC(rA[3],rB[2],rC[3+2*TT0I]); \
  TYPE_MAC(rA[0],rB[3],rC[0+3*TT0I]); \
  TYPE_MAC(rA[1],rB[3],rC[1+3*TT0I]); \
  TYPE_MAC(rA[2],rB[3],rC[2+3*TT0I]); \
  TYPE_MAC(rA[3],rB[3],rC[3+3*TT0I]); \

/* hard-coded initial strides */
__constant unsigned int strideC0I = 1;
__constant unsigned int strideA0I = 1;
__constant unsigned int strideBL = 1;

  /******************************************/
  /* Begin Kernel                           */
  /******************************************/
__attribute__((reqd_work_group_size(NUM_THREADS,1,1)))
__kernel void Cijk_Ailk_Bljk_DB_MT064x064x04_K1_PGR1_PLR0_TT04_04_WG16_16_01_WGM02(
  __global double *C,
  __global double const * restrict A,
  __global double const * restrict B,
  double const alpha,
  double const beta,
  unsigned int const offsetC,
  unsigned int const offsetA,
  unsigned int const offsetB,
  unsigned int const strideC1J,
  unsigned int const strideCK,
  unsigned int const strideAL,
  unsigned int const strideAK,
  unsigned int const strideB1J,
  unsigned int const strideBK,
  unsigned int const size0I,
  unsigned int const size1J,
  unsigned int const sizeK,
  unsigned int const sizeL ) {

  /******************************************/
  /* Allocate Resources                     */
  /******************************************/
#define SCALAR_ZERO (double)(0)
  DATA_TYPE rA[TT0I];
  DATA_TYPE rB[TT1J];

  /* registers for global->local */
  DATA_TYPE a_0_0_0_0;
  DATA_TYPE b_0_0_0_0;

  /* allocate local memory */
  __local DATA_TYPE localMemory[LDS_NUM_ELEMENTS];

  /******************************************/
  /* Global Read Addresses                  */
  /******************************************/

  /* global read addresses: subgroup */
  unsigned int serial = get_local_id(0);
  unsigned int sgId = serial / (SG0I*SG1J);

  /* global read addresses: work-group */
  unsigned int wg0I = get_group_id(0);
  unsigned int wg1J = get_group_id(1);
  unsigned int nwg0I = get_num_groups(0);
  unsigned int nwg1J = get_num_groups(1);

  unsigned long wgSerial = wg0I + (wg1J % WORK_GROUP_MAPPING) * nwg0I;
  unsigned int block = wg1J / WORK_GROUP_MAPPING;
  unsigned int blockRemainder = (wg1J < nwg1J-(nwg1J % WORK_GROUP_MAPPING) ) ? 0 : nwg1J % WORK_GROUP_MAPPING;
  if ( blockRemainder == 0) {
    wg0I = wgSerial / 2;
    wg1J = wgSerial % 2 + block*WORK_GROUP_MAPPING;
  } else {
    wg0I = wgSerial / 1;
    wg1J = wgSerial % 1 + block*WORK_GROUP_MAPPING;
  }

  /* global read addresses: tile offset assignment a */
  unsigned int globalReadOffsetA0I = (serial%LVCA)*GLOBAL_LOAD_VECTOR_WIDTH_A + (wg0I)*MT0I;

  /* global read addresses: tile offset assignment b */
  unsigned int globalReadOffsetB1J = (serial/LVCB) + (wg1J)*MT1J;

  /* global read addresses: unroll assignment a */
  unsigned int globalReadOffsetAL = (serial/LVCA);

  /* global read addresses: unroll assignment b */
  unsigned int globalReadOffsetBL = (serial%LVCB)*GLOBAL_LOAD_VECTOR_WIDTH_B;

  /* global read addresses: other free assignments */
  unsigned int wgK = ( get_group_id(2) ) % sizeK;

  /* global read addresses: tile offsets a */
  unsigned int globalReadOffsetA0I_0_0 = globalReadOffsetA0I + 0 + 0*LSCA;

  /* global read addresses: tile offsets b */
  unsigned int globalReadOffsetB1J_0_0 = globalReadOffsetB1J + 0 + 0*LSPB;

  /* global read addresses: unroll offsets a */
  unsigned int globalReadOffsetAL_0_0 = globalReadOffsetAL + 0 + 0*LSPA;

  /* global read addresses: unroll offsets b */
  unsigned int globalReadOffsetBL_0_0 = globalReadOffsetBL + 0 + 0*LSCB;

  /* global read addresses: shift a */
  globalReadOffsetA0I_0_0 = (  globalReadOffsetA0I_0_0 > size0I-GLOBAL_LOAD_VECTOR_WIDTH_A+0) ? size0I-GLOBAL_LOAD_VECTOR_WIDTH_A+0 : globalReadOffsetA0I_0_0;

  /* global read addresses: shift b */
  globalReadOffsetB1J_0_0 = (  globalReadOffsetB1J_0_0 > size1J-1) ? size1J-1 : globalReadOffsetB1J_0_0;

  /* global read addresses: final offsets a */
  unsigned long globalReadOffsetA_0_0_0_0 = GLOBAL_OFFSET_A( globalReadOffsetA0I_0_0, globalReadOffsetAL_0_0, wgK );

  /* global read addresses: final offsets b */
  unsigned long globalReadOffsetB_0_0_0_0 = GLOBAL_OFFSET_B( globalReadOffsetBL_0_0, globalReadOffsetB1J_0_0, wgK );

  /* global read addresses: apply user offsets */
  C += offsetC;
  A += offsetA;
  B += offsetB;

  /* global read addresses: addresses a */
  __global DATA_TYPE const *globalReadA_0_0_0_0 = A + globalReadOffsetA_0_0_0_0;

  /* global read addresses: addresses b */
  __global DATA_TYPE const *globalReadB_0_0_0_0 = B + globalReadOffsetB_0_0_0_0;

  /* global read addresses: increments a */
  long globalReadIncAL = (long)strideAL*LOCAL_DEPTHU;

  /* global read addresses: increments b */
  long globalReadIncBL = (long)strideBL*LOCAL_DEPTHU;

  /******************************************/
  /* Local Write Addresses                  */
  /******************************************/

  /* local write addresses: tile assignment a */
  unsigned int lwA0I = (serial%LVCA)*GLOBAL_LOAD_VECTOR_WIDTH_A;

  /* local write addresses: tile assignment b */
  unsigned int lwB1J = (serial/LVCB);

  /* local write addresses: unroll assignment a */
  unsigned int lwAL = (serial/LVCA);

  /* local write addresses: unroll assignment b */
  unsigned int lwBL = (serial%LVCB)*GLOBAL_LOAD_VECTOR_WIDTH_B;

  /* local write addresses: first offset a */
  unsigned int localWriteFirstOffsetA = lwA0I + lwAL*(MT0I+PAD);

  /* local write addresses: first offset b */
  unsigned int localWriteFirstOffsetB = lwB1J + lwBL*(MT1J+PAD) + LDS_OFFSET_B;

  /* local write addresses: final offsets a */
  unsigned int localWriteOffsetA_0_0_0_0 = localWriteFirstOffsetA + (0 + 0*LSCA) + (0 + 0*LSPA)*(MT0I+PAD);

  /* local write addresses: final offsets b */
  unsigned int localWriteOffsetB_0_0_0_0 = localWriteFirstOffsetB + (0 + 0*LSCB)*(MT1J+PAD) + (0 + 0*LSPB);

  /* local write addresses: declare addresses a */
  __local DATA_TYPE *localWriteA_0_0_0_0;

  /* local write addresses: declare addresses b */
  __local DATA_TYPE *localWriteB_0_0_0_0;

  /* local write addresses: init pointers a */
  localWriteA_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetA_0_0_0_0);

  /* local write addresses: init pointers b */
  localWriteB_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetB_0_0_0_0);

  /******************************************/
  /* Local Read Addresses                   */
  /******************************************/

  /* local read addresses: tile assignments a */
  unsigned int lr0I = (serial % SG0I);

  /* local read addresses: tile assignments b */
  unsigned int lr1J = (serial / SG0I) % SG1J;

  /* local read addresses: final offsets a */
  unsigned int localReadOffsetA = lr0I*VECTOR_WIDTH + sgId*(MT0I+PAD);

  /* local read addresses: final offsets b */
  unsigned int localReadOffsetB = lr1J*VECTOR_WIDTH + sgId*(MT1J+PAD) + LDS_OFFSET_B;

  /* local read addresses: declare addresses a */
  __local DATA_TYPE *localReadA;

  /* local read addresses: declare addresses b */
  __local DATA_TYPE *localReadB;

  /* declare loop num iterations */
  unsigned int numIterL;

  /* registers for MAC's */
  DATA_TYPE rC[TT0I*TT1J];
  rC[0] = SCALAR_ZERO;
  rC[1] = SCALAR_ZERO;
  rC[2] = SCALAR_ZERO;
  rC[3] = SCALAR_ZERO;
  rC[4] = SCALAR_ZERO;
  rC[5] = SCALAR_ZERO;
  rC[6] = SCALAR_ZERO;
  rC[7] = SCALAR_ZERO;
  rC[8] = SCALAR_ZERO;
  rC[9] = SCALAR_ZERO;
  rC[10] = SCALAR_ZERO;
  rC[11] = SCALAR_ZERO;
  rC[12] = SCALAR_ZERO;
  rC[13] = SCALAR_ZERO;
  rC[14] = SCALAR_ZERO;
  rC[15] = SCALAR_ZERO;
  numIterL = sizeL / LOCAL_DEPTHU;

  /* local read addresses: init pointers a */
  localReadA = (__local DATA_TYPE *)(localMemory + localReadOffsetA);

  /* local read addresses: init pointers b */
  localReadB = (__local DATA_TYPE *)(localMemory + localReadOffsetB);

  /* prefetch: global -> local */
  if (sizeL >= LOCAL_DEPTHU) {

    /* global read a */
    a_0_0_0_0 = *(globalReadA_0_0_0_0 + 0);

    /* global read b */
    b_0_0_0_0 = *(globalReadB_0_0_0_0 + 0);

    /* global read inc a */
    globalReadA_0_0_0_0 = (__global DATA_TYPE const *)( ((__global DATA_TYPE const *)globalReadA_0_0_0_0) + globalReadIncAL);

    /* global read inc b */
    globalReadB_0_0_0_0 = (__global DATA_TYPE const *)( ((__global DATA_TYPE const *)globalReadB_0_0_0_0) + globalReadIncBL);

    /* local write a */
    *(localWriteA_0_0_0_0 + 0) = a_0_0_0_0;

    /* local write b */
    *(localWriteB_0_0_0_0 + 0) = b_0_0_0_0;

    /* local write swap a */
    localWriteOffsetA_0_0_0_0 = (localWriteOffsetA_0_0_0_0 + LDS_OFFSET_BLK)%(LDS_OFFSET_BLK*2);

    /* local write swap b */
    localWriteOffsetB_0_0_0_0 = (localWriteOffsetB_0_0_0_0 + LDS_OFFSET_BLK)%(LDS_OFFSET_BLK*2);

    /* local write init pointers a */
    localWriteA_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetA_0_0_0_0);

    /* local write init pointers b */
    localWriteB_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetB_0_0_0_0);
  }

  /******************************************/
  /* Unrolled Loop - Begin                  */
  /******************************************/
  while (numIterL-- > 1) {

    /* global read a */
    a_0_0_0_0 = *(globalReadA_0_0_0_0 + 0);

    /* global read b */
    b_0_0_0_0 = *(globalReadB_0_0_0_0 + 0);

    /* global read inc a */
    globalReadA_0_0_0_0 = (__global DATA_TYPE const *)( ((__global DATA_TYPE const *)globalReadA_0_0_0_0) + globalReadIncAL);

    /* global read inc b */
    globalReadB_0_0_0_0 = (__global DATA_TYPE const *)( ((__global DATA_TYPE const *)globalReadB_0_0_0_0) + globalReadIncBL);
    barrier(CLK_LOCAL_MEM_FENCE);

    /* iter 0 */

    /* local read a */
    rA[0*VECTOR_WIDTH+0] = localReadA[0*SG0I*VECTOR_WIDTH + 0];
    rA[0*VECTOR_WIDTH+1] = localReadA[0*SG0I*VECTOR_WIDTH + 1];
    rA[1*VECTOR_WIDTH+0] = localReadA[1*SG0I*VECTOR_WIDTH + 0];
    rA[1*VECTOR_WIDTH+1] = localReadA[1*SG0I*VECTOR_WIDTH + 1];

    /* local read b */
    rB[0*VECTOR_WIDTH+0] = localReadB[0*SG1J*VECTOR_WIDTH + 0];
    rB[0*VECTOR_WIDTH+1] = localReadB[0*SG1J*VECTOR_WIDTH + 1];
    rB[1*VECTOR_WIDTH+0] = localReadB[1*SG1J*VECTOR_WIDTH + 0];
    rB[1*VECTOR_WIDTH+1] = localReadB[1*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x4

    /* iter 1 */

    /* local read a */
    rA[0*VECTOR_WIDTH+0] = localReadA[0*SG0I*VECTOR_WIDTH + 0];
    rA[0*VECTOR_WIDTH+1] = localReadA[0*SG0I*VECTOR_WIDTH + 1];
    rA[1*VECTOR_WIDTH+0] = localReadA[1*SG0I*VECTOR_WIDTH + 0];
    rA[1*VECTOR_WIDTH+1] = localReadA[1*SG0I*VECTOR_WIDTH + 1];

    /* local read b */
    rB[0*VECTOR_WIDTH+0] = localReadB[0*SG1J*VECTOR_WIDTH + 0];
    rB[0*VECTOR_WIDTH+1] = localReadB[0*SG1J*VECTOR_WIDTH + 1];
    rB[1*VECTOR_WIDTH+0] = localReadB[1*SG1J*VECTOR_WIDTH + 0];
    rB[1*VECTOR_WIDTH+1] = localReadB[1*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x4

    /* iter 2 */

    /* local read a */
    rA[0*VECTOR_WIDTH+0] = localReadA[0*SG0I*VECTOR_WIDTH + 0];
    rA[0*VECTOR_WIDTH+1] = localReadA[0*SG0I*VECTOR_WIDTH + 1];
    rA[1*VECTOR_WIDTH+0] = localReadA[1*SG0I*VECTOR_WIDTH + 0];
    rA[1*VECTOR_WIDTH+1] = localReadA[1*SG0I*VECTOR_WIDTH + 1];

    /* local read b */
    rB[0*VECTOR_WIDTH+0] = localReadB[0*SG1J*VECTOR_WIDTH + 0];
    rB[0*VECTOR_WIDTH+1] = localReadB[0*SG1J*VECTOR_WIDTH + 1];
    rB[1*VECTOR_WIDTH+0] = localReadB[1*SG1J*VECTOR_WIDTH + 0];
    rB[1*VECTOR_WIDTH+1] = localReadB[1*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x4

    /* iter 3 (last) */

    /* local read a */
    rA[0*VECTOR_WIDTH+0] = localReadA[0*SG0I*VECTOR_WIDTH + 0];
    rA[0*VECTOR_WIDTH+1] = localReadA[0*SG0I*VECTOR_WIDTH + 1];
    rA[1*VECTOR_WIDTH+0] = localReadA[1*SG0I*VECTOR_WIDTH + 0];
    rA[1*VECTOR_WIDTH+1] = localReadA[1*SG0I*VECTOR_WIDTH + 1];

    /* local read b */
    rB[0*VECTOR_WIDTH+0] = localReadB[0*SG1J*VECTOR_WIDTH + 0];
    rB[0*VECTOR_WIDTH+1] = localReadB[0*SG1J*VECTOR_WIDTH + 1];
    rB[1*VECTOR_WIDTH+0] = localReadB[1*SG1J*VECTOR_WIDTH + 0];
    rB[1*VECTOR_WIDTH+1] = localReadB[1*SG1J*VECTOR_WIDTH + 1];

    /* local write a */
    *(localWriteA_0_0_0_0 + 0) = a_0_0_0_0;

    /* local write b */
    *(localWriteB_0_0_0_0 + 0) = b_0_0_0_0;

    /* local write swap offsets a */
    localWriteOffsetA_0_0_0_0 = (localWriteOffsetA_0_0_0_0 + LDS_OFFSET_BLK)%(LDS_OFFSET_BLK*2);

    /* local write swap offsets b */
    localWriteOffsetB_0_0_0_0 = (localWriteOffsetB_0_0_0_0 + LDS_OFFSET_BLK)%(LDS_OFFSET_BLK*2);

    /* local write init pointers a */
    localWriteA_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetA_0_0_0_0);

    /* local write init pointers b */
    localWriteB_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetB_0_0_0_0);

    /* local read swap offsets a */
    localReadOffsetA = (localReadOffsetA + LDS_OFFSET_BLK)%(LDS_OFFSET_BLK*2);

    /* local read swap offsets b */
    localReadOffsetB = (localReadOffsetB + LDS_OFFSET_BLK)%(LDS_OFFSET_BLK*2);

    /* local read init pointers a */
    localReadA = (__local DATA_TYPE *)(localMemory + localReadOffsetA);

    /* local read init pointers b */
    localReadB = (__local DATA_TYPE *)(localMemory + localReadOffsetB);
    MAC_4x4

    /******************************************/
    /* Unrolled Loop - End                    */
    /******************************************/
  }

  /* prefetch: last unrolled iteration */
  if (sizeL >= LOCAL_DEPTHU) {
    barrier(CLK_LOCAL_MEM_FENCE);

    /* iter 0 */

    /* local read a */
    rA[0*VECTOR_WIDTH+0] = localReadA[0*SG0I*VECTOR_WIDTH + 0];
    rA[0*VECTOR_WIDTH+1] = localReadA[0*SG0I*VECTOR_WIDTH + 1];
    rA[1*VECTOR_WIDTH+0] = localReadA[1*SG0I*VECTOR_WIDTH + 0];
    rA[1*VECTOR_WIDTH+1] = localReadA[1*SG0I*VECTOR_WIDTH + 1];

    /* local read b */
    rB[0*VECTOR_WIDTH+0] = localReadB[0*SG1J*VECTOR_WIDTH + 0];
    rB[0*VECTOR_WIDTH+1] = localReadB[0*SG1J*VECTOR_WIDTH + 1];
    rB[1*VECTOR_WIDTH+0] = localReadB[1*SG1J*VECTOR_WIDTH + 0];
    rB[1*VECTOR_WIDTH+1] = localReadB[1*SG1J*VECTOR_WIDTH + 1];

    /* local read inc a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read inc b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x4

    /* iter 1 */

    /* local read a */
    rA[0*VECTOR_WIDTH+0] = localReadA[0*SG0I*VECTOR_WIDTH + 0];
    rA[0*VECTOR_WIDTH+1] = localReadA[0*SG0I*VECTOR_WIDTH + 1];
    rA[1*VECTOR_WIDTH+0] = localReadA[1*SG0I*VECTOR_WIDTH + 0];
    rA[1*VECTOR_WIDTH+1] = localReadA[1*SG0I*VECTOR_WIDTH + 1];

    /* local read b */
    rB[0*VECTOR_WIDTH+0] = localReadB[0*SG1J*VECTOR_WIDTH + 0];
    rB[0*VECTOR_WIDTH+1] = localReadB[0*SG1J*VECTOR_WIDTH + 1];
    rB[1*VECTOR_WIDTH+0] = localReadB[1*SG1J*VECTOR_WIDTH + 0];
    rB[1*VECTOR_WIDTH+1] = localReadB[1*SG1J*VECTOR_WIDTH + 1];

    /* local read inc a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read inc b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x4

    /* iter 2 */

    /* local read a */
    rA[0*VECTOR_WIDTH+0] = localReadA[0*SG0I*VECTOR_WIDTH + 0];
    rA[0*VECTOR_WIDTH+1] = localReadA[0*SG0I*VECTOR_WIDTH + 1];
    rA[1*VECTOR_WIDTH+0] = localReadA[1*SG0I*VECTOR_WIDTH + 0];
    rA[1*VECTOR_WIDTH+1] = localReadA[1*SG0I*VECTOR_WIDTH + 1];

    /* local read b */
    rB[0*VECTOR_WIDTH+0] = localReadB[0*SG1J*VECTOR_WIDTH + 0];
    rB[0*VECTOR_WIDTH+1] = localReadB[0*SG1J*VECTOR_WIDTH + 1];
    rB[1*VECTOR_WIDTH+0] = localReadB[1*SG1J*VECTOR_WIDTH + 0];
    rB[1*VECTOR_WIDTH+1] = localReadB[1*SG1J*VECTOR_WIDTH + 1];

    /* local read inc a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read inc b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x4

    /* iter 3 */

    /* local read a */
    rA[0*VECTOR_WIDTH+0] = localReadA[0*SG0I*VECTOR_WIDTH + 0];
    rA[0*VECTOR_WIDTH+1] = localReadA[0*SG0I*VECTOR_WIDTH + 1];
    rA[1*VECTOR_WIDTH+0] = localReadA[1*SG0I*VECTOR_WIDTH + 0];
    rA[1*VECTOR_WIDTH+1] = localReadA[1*SG0I*VECTOR_WIDTH + 1];

    /* local read b */
    rB[0*VECTOR_WIDTH+0] = localReadB[0*SG1J*VECTOR_WIDTH + 0];
    rB[0*VECTOR_WIDTH+1] = localReadB[0*SG1J*VECTOR_WIDTH + 1];
    rB[1*VECTOR_WIDTH+0] = localReadB[1*SG1J*VECTOR_WIDTH + 0];
    rB[1*VECTOR_WIDTH+1] = localReadB[1*SG1J*VECTOR_WIDTH + 1];

    /* local read inc a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read inc b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x4
  }

  /******************************************/
  /* Tail Loop                              */
  /******************************************/

  /* local write reset offsets a */
  localWriteOffsetA_0_0_0_0 %= LDS_OFFSET_BLK;

  /* local write reset offsets b */
  localWriteOffsetB_0_0_0_0 %= LDS_OFFSET_BLK;
  numIterL = (((sizeL % LOCAL_DEPTHU) + LOCAL_SPLITU - 1) / LOCAL_SPLITU);

  /* global read a */
  a_0_0_0_0 = ( globalReadOffsetAL_0_0 + 0 >= (sizeL % LOCAL_DEPTHU) ) ? SCALAR_ZERO : *(globalReadA_0_0_0_0 + 0);

  /* global read b */
  b_0_0_0_0 = ( globalReadOffsetBL_0_0 + 0 >= (sizeL % LOCAL_DEPTHU) ) ? SCALAR_ZERO : *(globalReadB_0_0_0_0 + 0);
  barrier(CLK_LOCAL_MEM_FENCE);

  /* local write init pointers a */
  localWriteA_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetA_0_0_0_0);

  /* local write init pointers b */
  localWriteB_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetB_0_0_0_0);

  /* local write a */
  *(localWriteA_0_0_0_0 + 0) = a_0_0_0_0;

  /* local write b */
  *(localWriteB_0_0_0_0 + 0) = b_0_0_0_0;
  barrier(CLK_LOCAL_MEM_FENCE);

  /* local read reset offsets a */
  localReadOffsetA %= LDS_OFFSET_BLK;

  /* local read reset offsets b */
  localReadOffsetB %= LDS_OFFSET_BLK;

  /* local read init pointers a */
  localReadA = (__local DATA_TYPE *)(localMemory + localReadOffsetA);

  /* local read init pointers b */
  localReadB = (__local DATA_TYPE *)(localMemory + localReadOffsetB);

  /* tail loop: macs */
  while (numIterL-- > 0) {

    /* local read a */
    rA[0*VECTOR_WIDTH+0] = localReadA[0*SG0I*VECTOR_WIDTH + 0];
    rA[0*VECTOR_WIDTH+1] = localReadA[0*SG0I*VECTOR_WIDTH + 1];
    rA[1*VECTOR_WIDTH+0] = localReadA[1*SG0I*VECTOR_WIDTH + 0];
    rA[1*VECTOR_WIDTH+1] = localReadA[1*SG0I*VECTOR_WIDTH + 1];

    /* local read b */
    rB[0*VECTOR_WIDTH+0] = localReadB[0*SG1J*VECTOR_WIDTH + 0];
    rB[0*VECTOR_WIDTH+1] = localReadB[0*SG1J*VECTOR_WIDTH + 1];
    rB[1*VECTOR_WIDTH+0] = localReadB[1*SG1J*VECTOR_WIDTH + 0];
    rB[1*VECTOR_WIDTH+1] = localReadB[1*SG1J*VECTOR_WIDTH + 1];

    /* local read inc a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read inc b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x4
  }

  /* not-LocalSplitU: global write indices */
  unsigned int globalC0I = (wg0I)*MT0I + (serial % SG0I)*VECTOR_WIDTH;
  unsigned int globalC1J = (wg1J)*MT1J + (serial / SG0I)*VECTOR_WIDTH;
  unsigned int globalCK = (wgK);

  /* not-LocalSplitU: global write */
  if (globalC0I + 0 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 0*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 0*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+0 + (0*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 1 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 0*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 0*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+1 + (0*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 0 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 0*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 0*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+0 + (0*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 1 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 0*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 0*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+1 + (0*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 0 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 0*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 0*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+0 + (0*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 1 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 0*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 0*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+1 + (0*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 0 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 0*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 0*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+0 + (0*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 1 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 0*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 0*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+1 + (0*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 0 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 1*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 1*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+0 + (1*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 1 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 1*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 1*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+1 + (1*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 0 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 1*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 1*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+0 + (1*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 1 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 1*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 1*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+1 + (1*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 0 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 1*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 1*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+0 + (1*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 1 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 1*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 1*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+1 + (1*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 0 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 1*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 1*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+0 + (1*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 1 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 1*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 1*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+1 + (1*VECTOR_WIDTH+1)*TT0I], beta) } }
}
);
#endif
