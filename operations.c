#include "operations.h"

#include <omp.h>
#include <stdint.h>

void pAddArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  #pragma omp parallel for
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] + arr2[i];
}

void pSubArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  #pragma omp parallel for
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] - arr2[i];
}

void pMulArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  #pragma omp parallel for
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] * arr2[i];
}

void pDivArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  #pragma omp parallel for
  for(uint32_t i=0; i<size; ++i)
    if(arr2[i])
      out[i] = arr1[i] / arr2[i];
    else out[i] = arr1[i]; // i dont give a f
}



void sAddArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] + arr2[i];
}

void sSubArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] - arr2[i];
}

void sMulArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) {
  for(uint32_t i=0; i<size; ++i)
    out[i] = arr1[i] * arr2[i];
}

void sDivArray(const arr_t* arr1, const arr_t* arr2, arr_t* out, const uint32_t size) { 
  for(uint32_t i=0; i<size; ++i)
    if(arr2[i])
      out[i] = arr1[i] / arr2[i];
    else out[i] = arr1[i]; // do i need to repeat myself?
}
