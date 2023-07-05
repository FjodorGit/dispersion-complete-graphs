#include "../pcg/pcg_basic.h"
#include "graphs.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

int step_fully_connected(int **graph_representation, int graph_size,
                         int capacity, int *maxp, int *destinations,
                         pcg32_random_t *rngptr) {

  int destinations_count = 0;
  int unhappy_count = 0;

  for (int i = 0; i < graph_size; i++) {
    int value = (*graph_representation)[i];
    if (value > capacity) {
      for (int j = 0; j < value; j++) {
        unhappy_count++;
        int random_index = pcg32_boundedrand_r(rngptr, graph_size);
        destinations[destinations_count++] = random_index;
      }
    } else if (value != 0) {
      for (int j = 0; j < value; j++) {
        destinations[destinations_count++] = i;
      }
    }
  }

  memset(*graph_representation, 0, graph_size * sizeof(int));
  *maxp = 0;
  for (int i = 0; i < destinations_count; i++) {
    int destination = destinations[i];
    (*graph_representation)[destination]++;
    if ((*graph_representation)[destination] > *maxp) {
      *maxp = (*graph_representation)[destination];
    }
  }

  return unhappy_count;
}
