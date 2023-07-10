#include "../pcg/pcg_basic.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

int step_circle(int **graph_representation, const int graph_size,
                const int capacity, int *maxp, int *destinations,
                pcg32_random_t *rngptr) {

  int destinations_count = 0;
  int unhappy_count = 0;

  for (int i = 0; i < graph_size; i++) {
    int value = (*graph_representation)[i];
    if (value > capacity) {

      unhappy_count += value;
      // To reduce the amount of random numbers needed look at the single bits
      // of a random number:
      // For example 26 = 0b11010
      // A zero means go to the left and a one means go to the right in the
      // circle. So here two particles would go to the left and three would go
      // to the right
      int particle_counter = 0;
      while (particle_counter < value) {
        int random = rand();
        int check_bits = 0x1;
        // printf("Value: %d | random: %d | sizeof(random) * 8: %lu\n", value,
        // random, sizeof(random) * 8);
        for (long unsigned int j = 0;
             j < sizeof(random) * 8 && particle_counter < value;
             j++, particle_counter++) {
          int left_or_right = random & check_bits;
          printf("Left or right: %s\n", left_or_right == 0 ? "left" : "right");
          if (left_or_right == 0 && i > 0) {
            destinations[destinations_count++] = i - 1;
          } else if (left_or_right == 0 && i == 0) {
            destinations[destinations_count++] = graph_size - 1;
          } else if (left_or_right != 0 && i < graph_size - 1) {
            destinations[destinations_count++] = i + 1;
          } else if (left_or_right != 0 && i == graph_size - 1) {
            destinations[destinations_count++] = 0;
          }
          check_bits = check_bits << 1;
        }
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
  printf("unhappy paritcles: %d \n", unhappy_count);

  return unhappy_count;
}
