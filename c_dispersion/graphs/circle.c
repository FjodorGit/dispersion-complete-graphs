#include "../pcg/pcg_basic.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

int step_circle_graph(int **graph, const uint n, int *maxp, int *destinations) {

  int destinations_count = 0;
  int unhappy_count = 0;

  for (int i = 0; i < n; i++) {
    int value = (*graph)[i];
    if (value > 1) {
      int particle_counter = 0;
      while (particle_counter < value) {
        int random = rand();
        int check_bits = 0x1;
        for (int j = 0; j < sizeof(random) && particle_counter < value;
             j++, particle_counter++) {
          int left_or_right = random & check_bits;
          if (left_or_right == 0 && i > 0) {
            destinations[destinations_count++] = i - 1;
          } else if (left_or_right == 0 && i == 0) {
            destinations[destinations_count++] = n - 1;
          } else if (left_or_right == 1 && i < n - 1) {
            destinations[destinations_count++] = i + 1;
          } else if (left_or_right == 1 && i == n - 1) {
            destinations[destinations_count++] = 0;
          }
          check_bits = check_bits << 1;
        }
      }
    } else if (value == 1) {
      destinations[destinations_count++] = i;
    }
  }

  memset(*graph, 0, n * sizeof(int));
  *maxp = 0;
  for (int i = 0; i < destinations_count; i++) {
    int destination = destinations[i];
    (*graph)[destination]++;
    if ((*graph)[destination] > *maxp) {
      *maxp = (*graph)[destination];
    }
  }

  return unhappy_count;
}
