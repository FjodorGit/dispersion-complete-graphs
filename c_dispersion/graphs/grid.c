#include "../pcg/pcg_basic.h"
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

// Grid graph starts out with all particles on the left top node
// and indexes first from left to right like reading a book.
// Every particle has to option to move to a neighbour on the left, right, top
// and bottom. If the paritcle decides to move to place where there is no
// neighbour (for example because its on an edge), then the particle just stays
// at its current position
int step_grid(int **graph_representation, const int graph_size,
              const int capacity, int *maxp, int *destinations,
              pcg32_random_t *rngptr) {

  int destinations_count = 0;
  int unhappy_count = 0;

  int graph_root = sqrt(graph_size);
  for (int i = 0; i < graph_size; i++) {
    int value = (*graph_representation)[i];
    if (value > capacity) {

      unhappy_count += value;
      // To reduce the amount of random numbers needed look at two bits of a
      // of a random number at a time:
      // The mappings are as follows:
      // - 0 -> left
      // - 1 -> right
      // - 2 -> top
      // - 3 -> bottom
      //
      // For example 26 = 0b011110 reading to bits at a time:
      // - 10 = 2 -> top
      // - 11 = 3 -> botttom
      // - 01 = 1 -> right
      //
      int particle_to_moved = 0;
      while (particle_to_moved < value) {

        int random = rand();
        int check_bits = 0b11;

        for (long unsigned int j = 0;
             j < sizeof(random) * 4 && particle_to_moved < value;
             j++, particle_to_moved++) {
          int left_right_top_bottom = (random & check_bits) >> (2 * j);

          // switch (left_right_top_bottom) {
          // case 0:
          //   printf("left\n");
          //   break;
          // case 1:
          //   printf("right\n");
          //   break;
          // case 2:
          //   printf("top\n");
          //   break;
          // case 3:
          //   printf("bottom\n");
          //   break;
          // }

          if (left_right_top_bottom == 0 && i % graph_root > 0) {
            destinations[destinations_count++] = i - 1;
          } else if (left_right_top_bottom == 1 &&
                     (i % graph_root) != graph_root - 1) {
            destinations[destinations_count++] = i + 1;
          } else if (left_right_top_bottom == 2 && i > graph_root - 1) {
            destinations[destinations_count++] = i - graph_root;
          } else if (left_right_top_bottom == 3 &&
                     i < graph_root * (graph_root - 1)) {
            destinations[destinations_count++] = i + graph_root;
          } else {
            destinations[destinations_count++] = i;
          }

          check_bits <<= 2;
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
  // printf("unhappy paritcles: %d \n", unhappy_count);

  // for (int i = 0; i < graph_root * graph_root; i++) {
  //   if (i % graph_root == 0) {
  //     printf("[ ");
  //   }
  //   printf("%d ", (*graph_representation)[i]);
  //   if (i % graph_root == graph_root - 1) {
  //     printf("]\n");
  //   }
  // }
  // printf("\n\n");

  return unhappy_count;
}
