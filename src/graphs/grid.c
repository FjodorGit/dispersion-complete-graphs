#include "../pcg/pcg_basic.h"
#include <math.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

// increasing the grid size to the left and to the right
// changes the index of the previouly established destinations
void adjust_previous_destinations(int **destinations, int destinations_count,
                                  int adjustment, int *grid_width) {
  if (adjustment == 0) {
    // adjustment because of left size increase.
    // Have to add the node height + 1
    for (int d = destinations_count - 1; d >= 0; d--) {
      int destination_height =
          ((*destinations)[d] < 0) ? -1 : (*destinations)[d] / (*grid_width);
      (*destinations)[d] += destination_height + 1;
    }
    *grid_width += 1;
  } else if (adjustment == 1) {
    // adjustment because of right size increase.
    // Have to add the node height
    for (int d = destinations_count - 1; d >= 0; d--) {
      int destination_height =
          ((*destinations)[d] < 0) ? -1 : (*destinations)[d] / (*grid_width);
      (*destinations)[d] += destination_height;
    }
    *grid_width += 1;
  }
}

// Simulate a single step on the grid graph
// Grid graph is an infinite grid ZxZ
// All particles starts out at the origin
// Every particle has the option to move to a neighbour on the left, right, top
// and bottom or stay at its current node.
// The first two numbers of graph_representation are height and width of the
// grid
// Since an infinite grid cannot be represented in memory we start with just the
// origin and increase the size of the graph representation as particles move
// away from the origin
int step_grid(int **graph_representation, int *graph_size, const int capacity,
              int *maxp, int *destinations, pcg32_random_t *rngptr,
              bool debug_info) {

  int destinations_count = 0;
  int unhappy_count = 0;
  bool left_size_increase = false;
  bool right_size_increase = false;
  int top_size_increase = 0;
  int buttom_size_increase = 0;

  int grid_height = (*graph_representation)[0];
  int grid_width = (*graph_representation)[1];

  const int current_height = grid_height;
  const int current_width = grid_width;

  // printing the graph representation
  if (debug_info) {
    for (int h = 0; h < *graph_size - 2;
         h +=
         grid_width) { // -2 because first two numbers are the width and height
      printf("[");
      for (int w = 0; w < grid_width; w++) {
        printf("%d ", (*graph_representation)[2 + h + w]);
      }
      printf("\b]\n");
    }
  }

  for (int h = 0; h < *graph_size - 2; h += current_width) {
    for (int w = 0; w < current_width; w++) {
      // iterate through grid like a matrix
      int value = (*graph_representation)[2 + h + w];
      if (value > capacity) {
        printf("\n");
        unhappy_count += value;
        for (int j = 0; j < value; j++) {
          int height = h / current_width;
          int current_position = h + w;
          if (left_size_increase) {
            current_position += height + 1;
          }
          if (right_size_increase) {
            current_position += height;
          }
          int left_right_top_buttom_stay = pcg32_boundedrand_r(rngptr, 5);
          // sample random number from 0-4
          //  0 means go left
          //  1 means go right
          //  2 means go up
          //  3 means go down
          //  4 means stay
          //

          if (left_right_top_buttom_stay == 0) { // particle move to the left
            if (debug_info) {
              printf("Move to the left\n");
            }

            if (w == 0 && !left_size_increase) {
              // particles is at the left boarder of the current grid. Have to
              // increase the size of the grid and shift previouly allocated
              // indeces

              adjust_previous_destinations(&destinations, destinations_count,
                                           left_right_top_buttom_stay,
                                           &grid_width);

              left_size_increase = true;
              // won't have to increase the size of the grid to the left during
              // this step again

              destinations[destinations_count++] = current_position + height;
              continue;
            }
            destinations[destinations_count++] = current_position - 1;
            // particle just moves a position to the left in the standard case

          } else if (left_right_top_buttom_stay == 1) { // particle move right
            if (debug_info) {
              printf("Move to the right\n");
            }
            if (w == current_width - 1 && !right_size_increase) {
              // particles is at the right boarder of the current grid. Have to
              // increase the size of the grid and shift previouly allocated
              // indeces

              adjust_previous_destinations(&destinations, destinations_count,
                                           left_right_top_buttom_stay,
                                           &grid_width);
              right_size_increase = true;
              // won't have to increase the size of the grid to the right during
              // this step again
              destinations[destinations_count++] =
                  current_position + height + 1;
              continue;
            }
            destinations[destinations_count++] = current_position + 1;
            // particle just moves a position to the right in the standard case

          } else if (left_right_top_buttom_stay == 2) { // particle move up
            if (debug_info) {
              printf("Move up\n");
            }
            if (h == 0 && top_size_increase == 0) {
              top_size_increase = 1;
              grid_height += 1;
            }
            destinations[destinations_count++] = current_position - grid_width;
            // just move the particle up. So one full grid_width back.
          } else if (left_right_top_buttom_stay == 3) {
            if (debug_info) {
              printf("Move down\n");
            }
            if (height == current_height - 1 && buttom_size_increase == 0) {
              buttom_size_increase = 1;
              grid_height += 1;
            }
            destinations[destinations_count++] = current_position + grid_width;
            // just move the particle up. So one full grid_width further.
          } else if (left_right_top_buttom_stay == 4) {
            if (debug_info) {
              printf("Stay at your node\n");
            }
            // particle stays at its current node
            destinations[destinations_count++] = current_position;
          }
        }
      } else if (value != 0) {
        int height = h / current_width;
        int current_position = h + w;
        if (left_size_increase) {
          current_position += height + 1;
        }
        if (right_size_increase) {
          current_position += height;
        }
        for (int j = 0; j < value; j++) {
          destinations[destinations_count++] = current_position;
        }
      }
    }
  }
  if (debug_info) {
    printf("\n\n\n");
  }
  *graph_size = 2 + (grid_width * grid_height);
  // 2 is because first two elements of the array are reserved to save
  // the grid_width and grid_height in the representation

  // Zero-initialize the existing memory block pointed to by
  int *new_graph_representation = calloc(*graph_size, sizeof(int));
  (new_graph_representation)[0] = grid_height;
  (new_graph_representation)[1] = grid_width;
  *maxp = 0;

  // build graph_representation from destinations array
  for (int i = 0; i < destinations_count; i++) {
    int destination = destinations[i] + 2 + grid_width * top_size_increase;
    (new_graph_representation)[destination]++;
    if ((new_graph_representation)[destination] > *maxp) {
      *maxp = (new_graph_representation)[destination];
    }
  }

  free(*graph_representation);
  *graph_representation = new_graph_representation;
  return unhappy_count;
}
