#include "../pcg/pcg_basic.h"
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

// Simulate a single step on the line graph.
// Line graph can be thought of as the number line with integer values as node.
// All particles starts out at the origin
// A particle has the options to move to the left, right or stay at its current
// node. Since an infinite grid cannot be represented in memory we start with
// just the origin and increase the size of the graph representation as
// particles move away from the origin
int step_line(int **graph_representation, int *graph_size, const int capacity,
              int *maxp, int *destinations, pcg32_random_t *rngptr,
              bool debug_info) {

  int destinations_count = 0;
  int unhappy_count = 0;
  int left_size_increase = 0;
  int right_size_increase = 0;

  if (debug_info) {
    printf("[ ");
    for (int i = 0; i < *graph_size; i++) {
      printf("%d ", (*graph_representation)[i]);
    }
    printf("]\n");
  }

  for (int i = 0; i < *graph_size; i++) {
    int value = (*graph_representation)[i];
    if (value > capacity) {
      printf("\n");
      unhappy_count += value;
      for (int j = 0; j < value; j++) {
        // generate a new destination for every unhappy particle
        int left_right_stay = pcg32_boundedrand_r(rngptr, 3);
        // sample random number from 0-2
        // 0 means go to the left
        // 1 means go to the right
        // 2 means stay
        if (left_right_stay == 0) {
          if (debug_info) {
            printf("Move to the left\n");
          }
          // particle moves to the left
          if (i == 0) {
            left_size_increase = 1;
            // particle is at the left boarder of the current line. So increase
            // the size of the line by 1
          }
          destinations[destinations_count++] = i - 1; // move left
        } else if (left_right_stay == 1) {
          if (debug_info) {
            printf("Move to the right\n");
          }
          // particle moves to the right
          if (i == *graph_size - 1) {
            right_size_increase = 1;
            // particle is at the right boarder of the current line. So increase
            // the size of the line by 1
          }
          destinations[destinations_count++] = i + 1; // move right
        } else if (left_right_stay == 2) {
          if (debug_info) {
            printf("Stay at your node\n");
          }
          destinations[destinations_count++] = i; // stay
        }
      }
    } else if (value != 0) {
      // all happy particles stay at their node
      for (int j = 0; j < value; j++) {
        destinations[destinations_count++] = i;
      }
    }
  }
  if (debug_info) {
    printf("\n\n\n");
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
