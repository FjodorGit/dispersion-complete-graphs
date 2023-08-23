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
  // printf("adjustment\n");
  if (adjustment == 0) {
    for (int d = destinations_count - 1; d >= 0; d--) {
      int destination_height =
          ((*destinations)[d] < 0) ? -1 : (*destinations)[d] / (*grid_width);
      // printf("Destination: %d | Destination height: %d\n",
      // (*destinations)[d],
      //        destination_height);
      (*destinations)[d] += destination_height + 1;
    }
    *grid_width += 1;
  } else if (adjustment == 1) {
    for (int d = destinations_count - 1; d >= 0; d--) {
      int destination_height =
          ((*destinations)[d] < 0) ? -1 : (*destinations)[d] / (*grid_width);
      (*destinations)[d] += destination_height;
    }
    *grid_width += 1;
  }
}

// Grid graph is an infinite grid
// All particles starts out at the origin
// Every particle has to option to move to a neighbour on the left, right, top
// and bottom or stay at its current node.
// The first two numbers of graph_representation are height and width of the
// grid
int step_grid(int **graph_representation, int *graph_size, const int capacity,
              int *maxp, int *destinations, pcg32_random_t *rngptr) {

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

  // for (int h = 0; h < *graph_size - 2;
  //      h +=
  //      grid_width) { // -2 because first two numbers are the width and height
  //   printf("[");
  //   for (int w = 0; w < grid_width; w++) {
  //     printf("%d ", (*graph_representation)[2 + h + w]);
  //   }
  //   printf("\b]\n");
  // }

  for (int h = 0; h < *graph_size - 2; h += current_width) {
    for (int w = 0; w < current_width; w++) {
      int value = (*graph_representation)[2 + h + w];
      if (value > capacity) {
        unhappy_count += value;
        // 0 means go left
        // 1 means go right
        // 2 means go up
        // 3 means go down
        // 4 means stay
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
          // printf("Move %d\n", left_right_top_buttom_stay);
          if (left_right_top_buttom_stay == 0) {
            if (w == 0 && !left_size_increase) {
              adjust_previous_destinations(&destinations, destinations_count,
                                           left_right_top_buttom_stay,
                                           &grid_width);
              left_size_increase = true;
              destinations[destinations_count++] = current_position + height;
              continue;
            }
            destinations[destinations_count++] = current_position - 1;
          } else if (left_right_top_buttom_stay == 1) {
            if (w == current_width - 1 && !right_size_increase) {
              adjust_previous_destinations(&destinations, destinations_count,
                                           left_right_top_buttom_stay,
                                           &grid_width);
              right_size_increase = true;
              destinations[destinations_count++] =
                  current_position + height + 1;
              continue;
            }
            destinations[destinations_count++] = current_position + 1;
          } else if (left_right_top_buttom_stay == 2) {
            if (h == 0 && top_size_increase == 0) {
              top_size_increase = 1;
              grid_height += 1;
            }
            destinations[destinations_count++] = current_position - grid_width;
          } else if (left_right_top_buttom_stay == 3) {
            if (height == current_height - 1 && buttom_size_increase == 0) {
              buttom_size_increase = 1;
              grid_height += 1;
            }
            destinations[destinations_count++] = current_position + grid_width;
          } else if (left_right_top_buttom_stay == 4) {
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
      // printf("Destinations: [");
      // for (int d = 0; d < destinations_count; d++) {
      //   printf(" %d", destinations[d]);
      // }
      // printf(" ]\n");
    }
  }
  *graph_size = 2 + (grid_width * grid_height);

  // Zero-initialize the existing memory block pointed to by
  int *new_graph_representation = calloc(*graph_size, sizeof(int));
  (new_graph_representation)[0] = grid_height;
  (new_graph_representation)[1] = grid_width;
  *maxp = 0;

  for (int i = 0; i < destinations_count; i++) {
    int destination = destinations[i] + 2 + grid_width * top_size_increase;
    (new_graph_representation)[destination]++;
    if ((new_graph_representation)[destination] > *maxp) {
      *maxp = (new_graph_representation)[destination];
    }
  }

  free(*graph_representation);
  *graph_representation = new_graph_representation;
  // printf("\n");
  return unhappy_count;
}
