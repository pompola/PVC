#include "omp_common.h"

#include <stdint.h>

const uint16_t getThreadsNum() {
  uint16_t num_threads = 0;
  #pragma omp parallel reduction(+:num_threads)
  ++num_threads;
  return num_threads;
}
