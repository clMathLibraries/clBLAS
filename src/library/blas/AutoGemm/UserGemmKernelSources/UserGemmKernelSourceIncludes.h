
#ifndef USER_GEMM_SOURCE_INCLUDES_H
#define USER_GEMM_SOURCE_INCLUDES_H
//**** compiler flags
//**** online compilation flags
const char * const User_srcBuildOptions = "-cl-std=CL2.0";
const char * const User_binBuildOptions = " ";


extern const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_workGroupNumRows;
extern const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_workGroupNumCols;
extern const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_microTileNumRows;
extern const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_microTileNumCols;
extern const unsigned int sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_unroll;
extern const char * const sgemm_Col_NT_B1_MX032_NX064_KX16_ROW_src;

extern const unsigned int sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_workGroupNumRows;
extern const unsigned int sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_workGroupNumCols;
extern const unsigned int sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_microTileNumRows;
extern const unsigned int sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_microTileNumCols;
extern const unsigned int sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_unroll;
extern const char * const sgemm_Col_NT_B1_MX064_NX032_KX16_COLUMN_src;

extern const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_workGroupNumRows;
extern const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_workGroupNumCols;
extern const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_microTileNumRows;
extern const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_microTileNumCols;
extern const unsigned int sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_unroll;
extern const char * const sgemm_Col_NT_B1_MX032_NX032_KX16_SINGLE_src;

extern const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_workGroupNumRows;
extern const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_workGroupNumCols;
extern const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_microTileNumRows;
extern const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_microTileNumCols;
extern const unsigned int sgemm_Col_NT_B1_MX128_NX128_KX16_unroll;
extern const char * const sgemm_Col_NT_B1_MX128_NX128_KX16_src;

#endif