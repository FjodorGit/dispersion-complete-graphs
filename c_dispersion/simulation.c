#include "graphs/graphs.h"
#include "pcg/pcg_basic.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

int *simulate(uint num_simulations, Graph graph) {

  int *result = (int *)malloc(num_simulations * sizeof(int));

#pragma omp parallel for num_threads(16)
  for (int i = 0; i < num_simulations; i++) {

    // initialize variables inside for-loop to private them for every thread
    int maximum = graph.particles_count;
    int *graph_representation = (int *)calloc(graph.size, sizeof(int));
    graph_representation[0] = graph.particles_count;

    // array initialized here, to only allocate the memory one time per
    // simulation
    int *destinations = (int *)malloc(graph.particles_count * sizeof(int));

    int num_steps = 0;
    while (maximum > graph.capacity) {
      graph.stepper(&graph_representation, graph.size, graph.capacity, &maximum,
                    destinations);
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
    free(graph_representation);
    free(destinations);
  }

  return result;
}

int *unhappy_process(Graph graph, int *num_steps) {

  int maximum = graph.particles_count;
  (*num_steps) = 0;
  int *graph_representation = (int *)calloc(graph.size, sizeof(int));
  int *destinations = (int *)malloc(graph.size * sizeof(int));

  int capacity = 50000;
  int *result = (int *)calloc(capacity, sizeof(int));

  graph_representation[0] = graph.particles_count;
  while (maximum > graph.capacity) {
    result[*num_steps] = graph.stepper(&graph_representation, graph.size,
                                       graph.capacity, &maximum, destinations);

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

  free(graph_representation); // Free the graph array
  free(destinations);         // Free the destinations array
  return result;
}
