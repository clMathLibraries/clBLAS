/*******************************************************************************
 * Hand-tuned kernel
 ******************************************************************************/

#ifndef KERNEL_DGEMM_TT_GFX906_TENSILE_SRC_H
#define KERNEL_DGEMM_TT_GFX906_TENSILE_SRC_H
// #pragma message("AutoGemm's dgemm_TT_gfx906_tensile_src overriden by user.")

const unsigned int dgemm_TT_gfx906_tensile_workGroupNumRows = 16;
const unsigned int dgemm_TT_gfx906_tensile_workGroupNumCols = 16;
const unsigned int dgemm_TT_gfx906_tensile_microTileNumRows = 4;
const unsigned int dgemm_TT_gfx906_tensile_microTileNumCols = 8;

#ifndef STRINGIFY
#define STRINGIFY(S) STRINGIFY2(S)
#define STRINGIFY2(S) #S
#endif

//if precompiled is enabled. All hand tuned kerenls should be precompiled.
#ifndef AUTOGEMM_USE_PRE_COMPILED_KERNELS
unsigned char *dgemm_TT_gfx906_tensile_bin = 0;
size_t dgemm_TT_gfx906_tensile_binSize = 0;
#endif

const char * const dgemm_TT_gfx906_tensile_src = STRINGIFY(
/******************************************/
/* Function Prefix                        */
/******************************************/

/* tile parameters */
#define NUM_THREADS 256
#define SG0I 16
#define SG1J 16
#define TT0I 4
#define TT1J 8
#define MT0I (SG0I*TT0I)
#define MT1J (SG1J*TT1J)
#define VECTOR_WIDTH 2
#define GLOBAL_LOAD_VECTOR_WIDTH_A 2
#define GLOBAL_LOAD_VECTOR_WIDTH_B 2
#define GLOBAL_WRITE_VECTOR_WIDTH 2

/* DepthU parameters*/
#define CPSV (NUM_THREADS / MT0I * VECTOR_WIDTH)
#define LOCAL_SPLITU 1
#define UNROLL 8
#define LOCAL_DEPTHU (LOCAL_SPLITU*UNROLL)

/* other */
#define PAD 0
#define WORK_GROUP_MAPPING 64

/* num loads parallel and perpendicular to coalesced */
#define NLCA 1
#define NLCB 1
#define NLPA 1
#define NLPB 2

/* load sizes parallel and perpendicular to coalesced */
#define LSCA (LOCAL_DEPTHU/NLCA)
#define LSPA (MT0I/NLPA)
#define LSCB (MT1J/NLCB)
#define LSPB (LOCAL_DEPTHU/NLPB)
#define LVCA (LSCA/GLOBAL_LOAD_VECTOR_WIDTH_A)
#define LVCB (LSCB/GLOBAL_LOAD_VECTOR_WIDTH_B)
#define LVPA (LSPA/GLOBAL_LOAD_VECTOR_WIDTH_A)
#define LVPB (LSPB/GLOBAL_LOAD_VECTOR_WIDTH_B)
#define LDS_OFFSET_B 512
#define LDS_NUM_ELEMENTS 1536

/* global memory indices */
#define GLOBAL_C(IDX0I, IDX1J, IDXK) (( (IDX0I)*strideC0I + (IDX1J)*strideC1J + (IDXK)*strideCK ))
#define GLOBAL_OFFSET_A(IDXL, IDX0I, IDXK) (( (IDXL)*strideAL + (IDX0I)*strideA0I + (IDXK)*strideAK ))
#define GLOBAL_OFFSET_B(IDX1J, IDXL, IDXK) (( (IDX1J)*strideB1J + (IDXL)*strideBL + (IDXK)*strideBK ))

/* data types */
#define DATA_TYPE double
#define MAC(A,B,DST) mad(A,B,DST)

/* MAC's */
#define TYPE_MAC(MULA,MULB,DST) DST = MAC(MULA,MULB,DST);
#define TYPE_MAC_WRITE(DST,ALPHA,REG,BETA) DST = 0 != (BETA) ? (ALPHA)*(REG) + (BETA)*(DST) : (ALPHA)*(REG);

/* 4x8 micro-tile */
#define MAC_4x8 \
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
  TYPE_MAC(rA[0],rB[4],rC[0+4*TT0I]); \
  TYPE_MAC(rA[1],rB[4],rC[1+4*TT0I]); \
  TYPE_MAC(rA[2],rB[4],rC[2+4*TT0I]); \
  TYPE_MAC(rA[3],rB[4],rC[3+4*TT0I]); \
  TYPE_MAC(rA[0],rB[5],rC[0+5*TT0I]); \
  TYPE_MAC(rA[1],rB[5],rC[1+5*TT0I]); \
  TYPE_MAC(rA[2],rB[5],rC[2+5*TT0I]); \
  TYPE_MAC(rA[3],rB[5],rC[3+5*TT0I]); \
  TYPE_MAC(rA[0],rB[6],rC[0+6*TT0I]); \
  TYPE_MAC(rA[1],rB[6],rC[1+6*TT0I]); \
  TYPE_MAC(rA[2],rB[6],rC[2+6*TT0I]); \
  TYPE_MAC(rA[3],rB[6],rC[3+6*TT0I]); \
  TYPE_MAC(rA[0],rB[7],rC[0+7*TT0I]); \
  TYPE_MAC(rA[1],rB[7],rC[1+7*TT0I]); \
  TYPE_MAC(rA[2],rB[7],rC[2+7*TT0I]); \
  TYPE_MAC(rA[3],rB[7],rC[3+7*TT0I]); \

/* hard-coded initial strides */
__constant unsigned int strideC0I = 1;
__constant unsigned int strideAL = 1;
__constant unsigned int strideB1J = 1;

  /******************************************/
  /* Begin Kernel                           */
  /******************************************/
__attribute__((reqd_work_group_size(NUM_THREADS,1,1)))
__kernel void Cijk_Alik_Bjlk_DB_MT064x128x08_K1_PGR0_PLR0_TT04_08_WG16_16_01_WGM64(
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
  unsigned int const strideA0I,
  unsigned int const strideAK,
  unsigned int const strideBL,
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
  DATA_TYPE a_0_1_0_0;
  DATA_TYPE b_0_0_0_0;
  DATA_TYPE b_0_1_0_0;
  DATA_TYPE b_0_0_1_0;
  DATA_TYPE b_0_1_1_0;

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
    wg0I = wgSerial / 64;
    wg1J = wgSerial % 64 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 1) {
    wg0I = wgSerial / 1;
    wg1J = wgSerial % 1 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 2) {
    wg0I = wgSerial / 2;
    wg1J = wgSerial % 2 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 3) {
    wg0I = wgSerial / 3;
    wg1J = wgSerial % 3 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 4) {
    wg0I = wgSerial / 4;
    wg1J = wgSerial % 4 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 5) {
    wg0I = wgSerial / 5;
    wg1J = wgSerial % 5 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 6) {
    wg0I = wgSerial / 6;
    wg1J = wgSerial % 6 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 7) {
    wg0I = wgSerial / 7;
    wg1J = wgSerial % 7 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 8) {
    wg0I = wgSerial / 8;
    wg1J = wgSerial % 8 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 9) {
    wg0I = wgSerial / 9;
    wg1J = wgSerial % 9 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 10) {
    wg0I = wgSerial / 10;
    wg1J = wgSerial % 10 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 11) {
    wg0I = wgSerial / 11;
    wg1J = wgSerial % 11 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 12) {
    wg0I = wgSerial / 12;
    wg1J = wgSerial % 12 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 13) {
    wg0I = wgSerial / 13;
    wg1J = wgSerial % 13 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 14) {
    wg0I = wgSerial / 14;
    wg1J = wgSerial % 14 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 15) {
    wg0I = wgSerial / 15;
    wg1J = wgSerial % 15 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 16) {
    wg0I = wgSerial / 16;
    wg1J = wgSerial % 16 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 17) {
    wg0I = wgSerial / 17;
    wg1J = wgSerial % 17 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 18) {
    wg0I = wgSerial / 18;
    wg1J = wgSerial % 18 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 19) {
    wg0I = wgSerial / 19;
    wg1J = wgSerial % 19 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 20) {
    wg0I = wgSerial / 20;
    wg1J = wgSerial % 20 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 21) {
    wg0I = wgSerial / 21;
    wg1J = wgSerial % 21 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 22) {
    wg0I = wgSerial / 22;
    wg1J = wgSerial % 22 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 23) {
    wg0I = wgSerial / 23;
    wg1J = wgSerial % 23 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 24) {
    wg0I = wgSerial / 24;
    wg1J = wgSerial % 24 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 25) {
    wg0I = wgSerial / 25;
    wg1J = wgSerial % 25 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 26) {
    wg0I = wgSerial / 26;
    wg1J = wgSerial % 26 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 27) {
    wg0I = wgSerial / 27;
    wg1J = wgSerial % 27 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 28) {
    wg0I = wgSerial / 28;
    wg1J = wgSerial % 28 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 29) {
    wg0I = wgSerial / 29;
    wg1J = wgSerial % 29 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 30) {
    wg0I = wgSerial / 30;
    wg1J = wgSerial % 30 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 31) {
    wg0I = wgSerial / 31;
    wg1J = wgSerial % 31 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 32) {
    wg0I = wgSerial / 32;
    wg1J = wgSerial % 32 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 33) {
    wg0I = wgSerial / 33;
    wg1J = wgSerial % 33 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 34) {
    wg0I = wgSerial / 34;
    wg1J = wgSerial % 34 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 35) {
    wg0I = wgSerial / 35;
    wg1J = wgSerial % 35 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 36) {
    wg0I = wgSerial / 36;
    wg1J = wgSerial % 36 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 37) {
    wg0I = wgSerial / 37;
    wg1J = wgSerial % 37 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 38) {
    wg0I = wgSerial / 38;
    wg1J = wgSerial % 38 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 39) {
    wg0I = wgSerial / 39;
    wg1J = wgSerial % 39 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 40) {
    wg0I = wgSerial / 40;
    wg1J = wgSerial % 40 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 41) {
    wg0I = wgSerial / 41;
    wg1J = wgSerial % 41 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 42) {
    wg0I = wgSerial / 42;
    wg1J = wgSerial % 42 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 43) {
    wg0I = wgSerial / 43;
    wg1J = wgSerial % 43 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 44) {
    wg0I = wgSerial / 44;
    wg1J = wgSerial % 44 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 45) {
    wg0I = wgSerial / 45;
    wg1J = wgSerial % 45 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 46) {
    wg0I = wgSerial / 46;
    wg1J = wgSerial % 46 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 47) {
    wg0I = wgSerial / 47;
    wg1J = wgSerial % 47 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 48) {
    wg0I = wgSerial / 48;
    wg1J = wgSerial % 48 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 49) {
    wg0I = wgSerial / 49;
    wg1J = wgSerial % 49 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 50) {
    wg0I = wgSerial / 50;
    wg1J = wgSerial % 50 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 51) {
    wg0I = wgSerial / 51;
    wg1J = wgSerial % 51 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 52) {
    wg0I = wgSerial / 52;
    wg1J = wgSerial % 52 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 53) {
    wg0I = wgSerial / 53;
    wg1J = wgSerial % 53 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 54) {
    wg0I = wgSerial / 54;
    wg1J = wgSerial % 54 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 55) {
    wg0I = wgSerial / 55;
    wg1J = wgSerial % 55 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 56) {
    wg0I = wgSerial / 56;
    wg1J = wgSerial % 56 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 57) {
    wg0I = wgSerial / 57;
    wg1J = wgSerial % 57 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 58) {
    wg0I = wgSerial / 58;
    wg1J = wgSerial % 58 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 59) {
    wg0I = wgSerial / 59;
    wg1J = wgSerial % 59 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 60) {
    wg0I = wgSerial / 60;
    wg1J = wgSerial % 60 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 61) {
    wg0I = wgSerial / 61;
    wg1J = wgSerial % 61 + block*WORK_GROUP_MAPPING;
  } else if ( blockRemainder == 62) {
    wg0I = wgSerial / 62;
    wg1J = wgSerial % 62 + block*WORK_GROUP_MAPPING;
  } else {
    wg0I = wgSerial / 63;
    wg1J = wgSerial % 63 + block*WORK_GROUP_MAPPING;
  }

  /* global read addresses: tile offset assignment a */
  unsigned int globalReadOffsetA0I = (serial/LVCA) + (wg0I)*MT0I;

  /* global read addresses: tile offset assignment b */
  unsigned int globalReadOffsetB1J = (serial%LVCB)*GLOBAL_LOAD_VECTOR_WIDTH_B + (wg1J)*MT1J;

  /* global read addresses: unroll assignment a */
  unsigned int globalReadOffsetAL = (serial%LVCA)*GLOBAL_LOAD_VECTOR_WIDTH_A;

  /* global read addresses: unroll assignment b */
  unsigned int globalReadOffsetBL = (serial/LVCB);

  /* global read addresses: other free assignments */
  unsigned int wgK = ( get_group_id(2) ) % sizeK;

  /* global read addresses: tile offsets a */
  unsigned int globalReadOffsetA0I_0_0 = globalReadOffsetA0I + 0 + 0*LSPA;

  /* global read addresses: tile offsets b */
  unsigned int globalReadOffsetB1J_0_0 = globalReadOffsetB1J + 0 + 0*LSCB;

  /* global read addresses: unroll offsets a */
  unsigned int globalReadOffsetAL_0_0 = globalReadOffsetAL + 0 + 0*LSCA;

  /* global read addresses: unroll offsets b */
  unsigned int globalReadOffsetBL_0_0 = globalReadOffsetBL + 0 + 0*LSPB;
  unsigned int globalReadOffsetBL_1_0 = globalReadOffsetBL + 0 + 1*LSPB;

  /* global read addresses: shift a */
  globalReadOffsetA0I_0_0 = (  globalReadOffsetA0I_0_0 > size0I-1) ? size0I-1 : globalReadOffsetA0I_0_0;

  /* global read addresses: shift b */
  globalReadOffsetB1J_0_0 = (  globalReadOffsetB1J_0_0 > size1J-GLOBAL_LOAD_VECTOR_WIDTH_B+0) ? size1J-GLOBAL_LOAD_VECTOR_WIDTH_B+0 : globalReadOffsetB1J_0_0;

  /* global read addresses: final offsets a */
  unsigned long globalReadOffsetA_0_0_0_0 = GLOBAL_OFFSET_A( globalReadOffsetAL_0_0, globalReadOffsetA0I_0_0, wgK );

  /* global read addresses: final offsets b */
  unsigned long globalReadOffsetB_0_0_0_0 = GLOBAL_OFFSET_B( globalReadOffsetB1J_0_0, globalReadOffsetBL_0_0, wgK );
  unsigned long globalReadOffsetB_0_0_1_0 = GLOBAL_OFFSET_B( globalReadOffsetB1J_0_0, globalReadOffsetBL_1_0, wgK );

  /* global read addresses: apply user offsets */
  C += offsetC;
  A += offsetA;
  B += offsetB;

  /* global read addresses: addresses a */
  __global DATA_TYPE const *globalReadA_0_0_0_0 = A + globalReadOffsetA_0_0_0_0;

  /* global read addresses: addresses b */
  __global DATA_TYPE const *globalReadB_0_0_0_0 = B + globalReadOffsetB_0_0_0_0;
  __global DATA_TYPE const *globalReadB_0_0_1_0 = B + globalReadOffsetB_0_0_1_0;

  /* global read addresses: increments a */
  long globalReadIncAL = (long)strideAL*LOCAL_DEPTHU;

  /* global read addresses: increments b */
  long globalReadIncBL = (long)strideBL*LOCAL_DEPTHU;

  /******************************************/
  /* Local Write Addresses                  */
  /******************************************/

  /* local write addresses: tile assignment a */
  unsigned int lwA0I = (serial/LVCA);

  /* local write addresses: tile assignment b */
  unsigned int lwB1J = (serial%LVCB)*GLOBAL_LOAD_VECTOR_WIDTH_B;

  /* local write addresses: unroll assignment a */
  unsigned int lwAL = (serial%LVCA)*GLOBAL_LOAD_VECTOR_WIDTH_A;

  /* local write addresses: unroll assignment b */
  unsigned int lwBL = (serial/LVCB);

  /* local write addresses: first offset a */
  unsigned int localWriteFirstOffsetA = lwA0I + lwAL*(MT0I+PAD);

  /* local write addresses: first offset b */
  unsigned int localWriteFirstOffsetB = lwB1J + lwBL*(MT1J+PAD) + LDS_OFFSET_B;

  /* local write addresses: final offsets a */
  unsigned int localWriteOffsetA_0_0_0_0 = localWriteFirstOffsetA + (0 + 0*LSCA)*(MT0I+PAD) + (0 + 0*LSPA);
  unsigned int localWriteOffsetA_0_0_0_1 = localWriteFirstOffsetA + (1 + 0*LSCA)*(MT0I+PAD) + (0 + 0*LSPA);

  /* local write addresses: final offsets b */
  unsigned int localWriteOffsetB_0_0_0_0 = localWriteFirstOffsetB + (0 + 0*LSCB) + (0 + 0*LSPB)*(MT1J+PAD);
  unsigned int localWriteOffsetB_0_0_1_0 = localWriteFirstOffsetB + (0 + 0*LSCB) + (0 + 1*LSPB)*(MT1J+PAD);

  /* local write addresses: declare addresses a */
  __local DATA_TYPE *localWriteA_0_0_0_0;
  __local DATA_TYPE *localWriteA_0_0_0_1;

  /* local write addresses: declare addresses b */
  __local DATA_TYPE *localWriteB_0_0_0_0;
  __local DATA_TYPE *localWriteB_0_0_1_0;

  /* local write addresses: init pointers a */
  localWriteA_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetA_0_0_0_0);
  localWriteA_0_0_0_1 = (__local DATA_TYPE *)(localMemory + localWriteOffsetA_0_0_0_1);

  /* local write addresses: init pointers b */
  localWriteB_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetB_0_0_0_0);
  localWriteB_0_0_1_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetB_0_0_1_0);

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
  rC[16] = SCALAR_ZERO;
  rC[17] = SCALAR_ZERO;
  rC[18] = SCALAR_ZERO;
  rC[19] = SCALAR_ZERO;
  rC[20] = SCALAR_ZERO;
  rC[21] = SCALAR_ZERO;
  rC[22] = SCALAR_ZERO;
  rC[23] = SCALAR_ZERO;
  rC[24] = SCALAR_ZERO;
  rC[25] = SCALAR_ZERO;
  rC[26] = SCALAR_ZERO;
  rC[27] = SCALAR_ZERO;
  rC[28] = SCALAR_ZERO;
  rC[29] = SCALAR_ZERO;
  rC[30] = SCALAR_ZERO;
  rC[31] = SCALAR_ZERO;
  numIterL = sizeL / LOCAL_DEPTHU;

  /* local read addresses: init pointers a */
  localReadA = (__local DATA_TYPE *)(localMemory + localReadOffsetA);

  /* local read addresses: init pointers b */
  localReadB = (__local DATA_TYPE *)(localMemory + localReadOffsetB);

  /******************************************/
  /* Unrolled Loop - Begin                  */
  /******************************************/
  while (numIterL-- > 0) {

    /* global read a */
    a_0_0_0_0 = *(globalReadA_0_0_0_0 + 0);
    a_0_1_0_0 = *(globalReadA_0_0_0_0 + 1);

    /* global read b */
    b_0_0_0_0 = *(globalReadB_0_0_0_0 + 0);
    b_0_1_0_0 = *(globalReadB_0_0_0_0 + 1);
    b_0_0_1_0 = *(globalReadB_0_0_1_0 + 0);
    b_0_1_1_0 = *(globalReadB_0_0_1_0 + 1);

    /* global read inc a */
    globalReadA_0_0_0_0 = (__global DATA_TYPE const *)( ((__global DATA_TYPE const *)globalReadA_0_0_0_0) + globalReadIncAL);

    /* global read inc b */
    globalReadB_0_0_0_0 = (__global DATA_TYPE const *)( ((__global DATA_TYPE const *)globalReadB_0_0_0_0) + globalReadIncBL);
    globalReadB_0_0_1_0 = (__global DATA_TYPE const *)( ((__global DATA_TYPE const *)globalReadB_0_0_1_0) + globalReadIncBL);
    barrier(CLK_LOCAL_MEM_FENCE);

    /* local write a */
    *(localWriteA_0_0_0_0 + 0) = a_0_0_0_0;
    *(localWriteA_0_0_0_1 + 0) = a_0_1_0_0;

    /* local write b */
    *(localWriteB_0_0_0_0 + 0) = b_0_0_0_0;
    *(localWriteB_0_0_0_0 + 1) = b_0_1_0_0;
    *(localWriteB_0_0_1_0 + 0) = b_0_0_1_0;
    *(localWriteB_0_0_1_0 + 1) = b_0_1_1_0;
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
    rB[2*VECTOR_WIDTH+0] = localReadB[2*SG1J*VECTOR_WIDTH + 0];
    rB[2*VECTOR_WIDTH+1] = localReadB[2*SG1J*VECTOR_WIDTH + 1];
    rB[3*VECTOR_WIDTH+0] = localReadB[3*SG1J*VECTOR_WIDTH + 0];
    rB[3*VECTOR_WIDTH+1] = localReadB[3*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x8

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
    rB[2*VECTOR_WIDTH+0] = localReadB[2*SG1J*VECTOR_WIDTH + 0];
    rB[2*VECTOR_WIDTH+1] = localReadB[2*SG1J*VECTOR_WIDTH + 1];
    rB[3*VECTOR_WIDTH+0] = localReadB[3*SG1J*VECTOR_WIDTH + 0];
    rB[3*VECTOR_WIDTH+1] = localReadB[3*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x8

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
    rB[2*VECTOR_WIDTH+0] = localReadB[2*SG1J*VECTOR_WIDTH + 0];
    rB[2*VECTOR_WIDTH+1] = localReadB[2*SG1J*VECTOR_WIDTH + 1];
    rB[3*VECTOR_WIDTH+0] = localReadB[3*SG1J*VECTOR_WIDTH + 0];
    rB[3*VECTOR_WIDTH+1] = localReadB[3*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x8

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
    rB[2*VECTOR_WIDTH+0] = localReadB[2*SG1J*VECTOR_WIDTH + 0];
    rB[2*VECTOR_WIDTH+1] = localReadB[2*SG1J*VECTOR_WIDTH + 1];
    rB[3*VECTOR_WIDTH+0] = localReadB[3*SG1J*VECTOR_WIDTH + 0];
    rB[3*VECTOR_WIDTH+1] = localReadB[3*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x8

    /* iter 4 */

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
    rB[2*VECTOR_WIDTH+0] = localReadB[2*SG1J*VECTOR_WIDTH + 0];
    rB[2*VECTOR_WIDTH+1] = localReadB[2*SG1J*VECTOR_WIDTH + 1];
    rB[3*VECTOR_WIDTH+0] = localReadB[3*SG1J*VECTOR_WIDTH + 0];
    rB[3*VECTOR_WIDTH+1] = localReadB[3*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x8

    /* iter 5 */

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
    rB[2*VECTOR_WIDTH+0] = localReadB[2*SG1J*VECTOR_WIDTH + 0];
    rB[2*VECTOR_WIDTH+1] = localReadB[2*SG1J*VECTOR_WIDTH + 1];
    rB[3*VECTOR_WIDTH+0] = localReadB[3*SG1J*VECTOR_WIDTH + 0];
    rB[3*VECTOR_WIDTH+1] = localReadB[3*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x8

    /* iter 6 */

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
    rB[2*VECTOR_WIDTH+0] = localReadB[2*SG1J*VECTOR_WIDTH + 0];
    rB[2*VECTOR_WIDTH+1] = localReadB[2*SG1J*VECTOR_WIDTH + 1];
    rB[3*VECTOR_WIDTH+0] = localReadB[3*SG1J*VECTOR_WIDTH + 0];
    rB[3*VECTOR_WIDTH+1] = localReadB[3*SG1J*VECTOR_WIDTH + 1];

    /* local read increment a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read increment b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x8

    /* iter 7 (last) */

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
    rB[2*VECTOR_WIDTH+0] = localReadB[2*SG1J*VECTOR_WIDTH + 0];
    rB[2*VECTOR_WIDTH+1] = localReadB[2*SG1J*VECTOR_WIDTH + 1];
    rB[3*VECTOR_WIDTH+0] = localReadB[3*SG1J*VECTOR_WIDTH + 0];
    rB[3*VECTOR_WIDTH+1] = localReadB[3*SG1J*VECTOR_WIDTH + 1];

    /* local read init pointers a */
    localReadA = (__local DATA_TYPE *)(localMemory + localReadOffsetA);

    /* local read init pointers b */
    localReadB = (__local DATA_TYPE *)(localMemory + localReadOffsetB);
    MAC_4x8

    /******************************************/
    /* Unrolled Loop - End                    */
    /******************************************/
  }

  /******************************************/
  /* Tail Loop                              */
  /******************************************/
  numIterL = (((sizeL % LOCAL_DEPTHU) + LOCAL_SPLITU - 1) / LOCAL_SPLITU);

  /* global read a */
  a_0_0_0_0 = ( globalReadOffsetAL_0_0 + 0 >= (sizeL % LOCAL_DEPTHU) ) ? SCALAR_ZERO : *(globalReadA_0_0_0_0 + 0);
  a_0_1_0_0 = ( globalReadOffsetAL_0_0 + 1 >= (sizeL % LOCAL_DEPTHU) ) ? SCALAR_ZERO : *(globalReadA_0_0_0_0 + 1);

  /* global read b */
  b_0_0_0_0 = ( globalReadOffsetBL_0_0 + 0 >= (sizeL % LOCAL_DEPTHU) ) ? SCALAR_ZERO : *(globalReadB_0_0_0_0 + 0);
  b_0_1_0_0 = ( globalReadOffsetBL_0_0 + 0 >= (sizeL % LOCAL_DEPTHU) ) ? SCALAR_ZERO : *(globalReadB_0_0_0_0 + 1);
  b_0_0_1_0 = ( globalReadOffsetBL_1_0 + 0 >= (sizeL % LOCAL_DEPTHU) ) ? SCALAR_ZERO : *(globalReadB_0_0_1_0 + 0);
  b_0_1_1_0 = ( globalReadOffsetBL_1_0 + 0 >= (sizeL % LOCAL_DEPTHU) ) ? SCALAR_ZERO : *(globalReadB_0_0_1_0 + 1);
  barrier(CLK_LOCAL_MEM_FENCE);

  /* local write init pointers a */
  localWriteA_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetA_0_0_0_0);
  localWriteA_0_0_0_1 = (__local DATA_TYPE *)(localMemory + localWriteOffsetA_0_0_0_1);

  /* local write init pointers b */
  localWriteB_0_0_0_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetB_0_0_0_0);
  localWriteB_0_0_1_0 = (__local DATA_TYPE *)(localMemory + localWriteOffsetB_0_0_1_0);

  /* local write a */
  *(localWriteA_0_0_0_0 + 0) = a_0_0_0_0;
  *(localWriteA_0_0_0_1 + 0) = a_0_1_0_0;

  /* local write b */
  *(localWriteB_0_0_0_0 + 0) = b_0_0_0_0;
  *(localWriteB_0_0_0_0 + 1) = b_0_1_0_0;
  *(localWriteB_0_0_1_0 + 0) = b_0_0_1_0;
  *(localWriteB_0_0_1_0 + 1) = b_0_1_1_0;
  barrier(CLK_LOCAL_MEM_FENCE);

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
    rB[2*VECTOR_WIDTH+0] = localReadB[2*SG1J*VECTOR_WIDTH + 0];
    rB[2*VECTOR_WIDTH+1] = localReadB[2*SG1J*VECTOR_WIDTH + 1];
    rB[3*VECTOR_WIDTH+0] = localReadB[3*SG1J*VECTOR_WIDTH + 0];
    rB[3*VECTOR_WIDTH+1] = localReadB[3*SG1J*VECTOR_WIDTH + 1];

    /* local read inc a */
    localReadA += LOCAL_SPLITU*(MT0I+PAD);

    /* local read inc b */
    localReadB += LOCAL_SPLITU*(MT1J+PAD);
    MAC_4x8
  }

  /* shift vector components d1 */
  unsigned int wgMT1J = size1J - wg1J*MT1J;
  if (wgMT1J > MT1J) wgMT1J = MT1J;
  unsigned int r1J = wgMT1J % GLOBAL_LOAD_VECTOR_WIDTH_B;
  if (r1J > 0 && ((wgMT1J/VECTOR_WIDTH) % SG1J) == (serial / SG0I) % SG1J ) {
    unsigned int s1J = (wgMT1J%VECTOR_WIDTH)/GLOBAL_LOAD_VECTOR_WIDTH_B + (wgMT1J/(SG1J*VECTOR_WIDTH))*(VECTOR_WIDTH/GLOBAL_LOAD_VECTOR_WIDTH_B);
    if (r1J == 1) {
      if (s1J == 0) {
        rC[0 + 0*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[0 + 0*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[1 + 0*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[1 + 0*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[2 + 0*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[2 + 0*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[3 + 0*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[3 + 0*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
      } else if (s1J == 1) {
        rC[0 + 1*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[0 + 1*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[1 + 1*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[1 + 1*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[2 + 1*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[2 + 1*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[3 + 1*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[3 + 1*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
      } else if (s1J == 2) {
        rC[0 + 2*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[0 + 2*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[1 + 2*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[1 + 2*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[2 + 2*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[2 + 2*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[3 + 2*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[3 + 2*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
      } else {
        rC[0 + 3*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[0 + 3*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[1 + 3*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[1 + 3*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[2 + 3*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[2 + 3*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
        rC[3 + 3*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 0*TT0I] = rC[3 + 3*TT0I*GLOBAL_LOAD_VECTOR_WIDTH_B + 1*TT0I];
      }
    }
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
  if (globalC0I + 0 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 2*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 2*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+0 + (2*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 1 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 2*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 2*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+1 + (2*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 0 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 2*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 2*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+0 + (2*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 1 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 2*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 2*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+1 + (2*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 0 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 2*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 2*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+0 + (2*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 1 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 2*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 2*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+1 + (2*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 0 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 2*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 2*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+0 + (2*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 1 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 2*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 2*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+1 + (2*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 0 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 3*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 3*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+0 + (3*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 1 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 3*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 3*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+1 + (3*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 0 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 3*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 3*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+0 + (3*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 1 + 0*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 3*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 0*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 3*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[0*VECTOR_WIDTH+1 + (3*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 0 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 3*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 3*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+0 + (3*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 1 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 0 + 3*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 0 + 3*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+1 + (3*VECTOR_WIDTH+0)*TT0I], beta) } }
  if (globalC0I + 0 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 3*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 0 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 3*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+0 + (3*VECTOR_WIDTH+1)*TT0I], beta) } }
  if (globalC0I + 1 + 1*SG0I*VECTOR_WIDTH < size0I) {  if (globalC1J + 1 + 3*SG1J*VECTOR_WIDTH < size1J) {  TYPE_MAC_WRITE( C[ GLOBAL_C( (unsigned long) globalC0I + 1 + 1*SG0I*VECTOR_WIDTH, (unsigned long) globalC1J + 1 + 3*SG1J*VECTOR_WIDTH, (unsigned long) globalCK) ], alpha, rC[1*VECTOR_WIDTH+1 + (3*VECTOR_WIDTH+1)*TT0I], beta) } }
}
);
#endif
