#include "random.h"

#include <stdlib.h>

void randomFill(arr_t array[], const uint32_t size) {
  #pragma omp parallel for
  for(uint32_t i=0; i<size; ++i)
    array[i] = rand()%MAX_RAND;
}
