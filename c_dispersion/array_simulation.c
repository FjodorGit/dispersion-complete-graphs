#include "pcg/pcg_basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

int step(int **graph, const uint n, int *maxp, int *destinations) {

  int destinations_count = 0;
  int unhappy_count = 0;

  for (int i = 0; i < n; i++) {
    int value = (*graph)[i];
    if (value > 1) {
      for (int j = 0; j < value; j++) {
        unhappy_count++;
        int random_index = pcg32_boundedrand(n);
        destinations[destinations_count++] = random_index;
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

int *simulate(uint num_simulations, uint graph_size, uint pariticle_count) {

  int maximum;
  int num_steps;
  int *graph = (int *)calloc(graph_size, sizeof(int));
  int *destinations = (int *)malloc(graph_size * sizeof(int));

  int *result = (int *)malloc(num_simulations * sizeof(int));

  for (int i = 0; i < num_simulations; i++) {
    memset(graph, 0, graph_size * sizeof(int));
    graph[0] = pariticle_count;
    maximum = pariticle_count;
    num_steps = 0;
    while (maximum > 1) {
      step(&graph, graph_size, &maximum, destinations);
      num_steps++;

      // Print the result
      // printf("[ ");
      // for (int i = 0; i < graph_size; i++) {
      //   printf("%d ", graph[i]);
      // }
      // printf("] \n");
    }
    // printf("Num steps: %d \n", num_steps);

    if (i % 100 == 0) {
      printf("Simulation %d/%d \n", i, num_simulations);
    }

    result[i] = num_steps;
  }

  free(graph);
  return result;
}

int *unhappy_process(uint graph_size, uint pariticle_count, int *num_steps) {

  int maximum;
  (*num_steps) = 0;
  int *graph = (int *)calloc(graph_size, sizeof(int));
  int *destinations = (int *)malloc(graph_size * sizeof(int));

  int capacity = 50000;
  int *result = (int *)calloc(capacity, sizeof(int));

  graph[0] = pariticle_count;
  maximum = pariticle_count;
  while (maximum > 1) {
    result[*num_steps] = step(&graph, graph_size, &maximum, destinations);

    if (*num_steps + 1 >= capacity) {
      capacity *= 2;
      int *should_not_be_null = realloc(result, capacity * sizeof(int));
      if (should_not_be_null == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        free(result); // Free the previously allocated memory
        exit(1);
      }
      result = should_not_be_null;
    }

    (*num_steps)++;
  }

  free(graph);        // Free the graph array
  free(destinations); // Free the destinations array
  return result;
}
