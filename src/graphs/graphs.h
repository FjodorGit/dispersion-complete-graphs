#include "../pcg/pcg_basic.h"
#include <stdbool.h>
#include <sys/types.h>

typedef int (*stepper)(int **graph_representation, int *graph_size,
                       const int capacity, int *maxp, int *destinations,
                       pcg32_random_t *rngptr, bool debug_info);

typedef struct {
  int size;
  const int capacity;
  const stepper stepper;
  char graph_type[128];
  int particles_count;
  bool debug_info;
} Graph;

int step_fully_connected(int **graph_representation, int *graph_size,
                         const int capacity, int *maxp, int *destinations,
                         pcg32_random_t *rngptr, bool debug_info);

int step_line(int **graph_representation, int *graph_size, const int capacity,
              int *maxp, int *destinations, pcg32_random_t *rngptr,
              bool debug_info);

int step_grid(int **graph_representation, int *graph_size, const int capacity,
              int *maxp, int *destinations, pcg32_random_t *rngptr,
              bool debug_info);
