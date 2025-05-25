#include "operations.h"
#include "random.h"
#include "timer.h"
#include "omp_common.h"

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
  srand(time(NULL));

  arr_t array1[ARRAY_SIZE],
        array2[ARRAY_SIZE],
        out_array[ARRAY_SIZE];
  double trand1=0, trand2=0,
         ptadd=0, ptsub=0, ptmul=0, ptdiv=0,
         stadd=0, stsub=0, stmul=0, stdiv=0;

  printf("Settings:\n\tOMP Threads: %d\n\tArray sizes: %d\n\tCycles: %d\n\n",
         getThreadsNum(), ARRAY_SIZE, CYCLES);


  for(uint32_t i=0; i<CYCLES; ++i) {
    randomFill(array1, ARRAY_SIZE);
    randomFill(array2, ARRAY_SIZE);

    ADDTIME_COR(pAddArray, ptadd, CYCLES, array1, array2, out_array, ARRAY_SIZE);
    ADDTIME_COR(sAddArray, stadd, CYCLES, array1, array2, out_array, ARRAY_SIZE);

    ADDTIME_COR(pSubArray, ptsub, CYCLES, array1, array2, out_array, ARRAY_SIZE);
    ADDTIME_COR(sSubArray, stsub, CYCLES, array1, array2, out_array, ARRAY_SIZE);

    ADDTIME_COR(pMulArray, ptmul, CYCLES, array1, array2, out_array, ARRAY_SIZE);
    ADDTIME_COR(sMulArray, stmul, CYCLES, array1, array2, out_array, ARRAY_SIZE);

    ADDTIME_COR(pDivArray, ptdiv, CYCLES, array1, array2, out_array, ARRAY_SIZE);
    ADDTIME_COR(sDivArray, stdiv, CYCLES, array1, array2, out_array, ARRAY_SIZE);
  }

  printf("Calculations done.\np - parallel, s - serial\nTime for:\n\tpAdd: %f\t\tsAdd: %f\n\
\tpSub: %f\t\tsSub: %f\n\tpMul: %f\t\tsMul: %f\n\tpDiv: %f\t\tsDiv: %f\n\tRand arr1: %f\t\tRand arr2: %f",
         ptadd, stadd, ptsub, stsub, ptmul, stmul, ptdiv, stdiv, trand1, trand2);

  return 0;
}
