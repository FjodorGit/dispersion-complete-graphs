#include "../pcg/pcg_basic.h"
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

int step_line(int **graph_representation, int *graph_size, const int capacity,
              int *maxp, int *destinations, pcg32_random_t *rngptr) {

  int destinations_count = 0;
  int unhappy_count = 0;
  int left_size_increase = 0;
  int right_size_increase = 0;

  // printf("[ ");
  // for (int i = 0; i < *graph_size; i++) {
  //   printf("%d ", (*graph_representation)[i]);
  // }
  // printf("]\n");

  for (int i = 0; i < *graph_size; i++) {
    int value = (*graph_representation)[i];
    if (value > capacity) {
      unhappy_count += value;
      // 0 means go to the left
      // 1 means go to the right
      // 2 means stay
      for (int j = 0; j < value; j++) {
        int left_right_stay = pcg32_boundedrand_r(rngptr, 3);
        // printf("Move %d\n", left_right_stay);
        if (left_right_stay == 0) {
          if (i == 0) {
            left_size_increase = 1;
          }
          destinations[destinations_count++] = i - 1;
        } else if (left_right_stay == 1) {
          if (i == *graph_size - 1) {
            right_size_increase = 1;
          }
          destinations[destinations_count++] = i + 1;
        } else if (left_right_stay == 2) {
          destinations[destinations_count++] = i;
        }
      }
    } else if (value != 0) {
      for (int j = 0; j < value; j++) {
        destinations[destinations_count++] = i;
      }
    }
  }

  *graph_size = *graph_size + left_size_increase + right_size_increase;

  int *new_graph_representation = calloc(*graph_size, sizeof(int));
  free(*graph_representation);
  *graph_representation = new_graph_representation;
  // Zero-initialize the existing memory block pointed to by

  *maxp = 0;
  for (int i = 0; i < destinations_count; i++) {
    int destination = destinations[i] + left_size_increase;
    (*graph_representation)[destination]++;
    if ((*graph_representation)[destination] > *maxp) {
      *maxp = (*graph_representation)[destination];
    }
  }
  return unhappy_count;
}
