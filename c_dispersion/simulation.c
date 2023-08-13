#include "pcg/pcg_basic.h"
#include "utils/utils.h"
#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

int *simulate(uint num_simulations, Graph graph) {

  int *result = (int *)malloc(num_simulations * sizeof(int));

#pragma omp parallel num_threads(3)
  {
    // initialize variables inside block to private them for every thread
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, omp_get_thread_num(), time(NULL));
    int maximum, num_steps;
    int *graph_representation = (int *)calloc(graph.size, sizeof(int));

    // array initialized here, to only allocate the memory one time per
    // simulation
    int *destinations = (int *)malloc(graph.particles_count * sizeof(int));
    int graph_size = graph.size;

    printf("Parallization\n");

#pragma omp for
    for (int i = 0; i < num_simulations; i++) {

      memset(graph_representation, 0, graph_size * sizeof(int));
      graph_representation[0] = graph.particles_count;
      maximum = graph.particles_count;
      num_steps = 0;

      while (maximum > graph.capacity) {
        graph.stepper(&graph_representation, &graph_size, graph.capacity,
                      &maximum, destinations, &rng);
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
        printf("Simulation %d/%d with %d\n", i, num_simulations, num_steps);
      }

      result[i] = num_steps;
    }
    free(graph_representation);
    free(destinations);
  }

  return result;
}

int *unhappy_process(Graph graph, int *num_steps, double *variance_evaluation) {

  uint32_t unhappy_count;
  int maximum = graph.particles_count;
  (*num_steps) = 0;
  int *graph_representation = (int *)calloc(graph.size, sizeof(int));
  int *destinations = (int *)malloc(graph.particles_count * sizeof(int));
  pcg32_random_t rng;
  pcg32_srandom_r(&rng, omp_get_thread_num(), time(NULL));
  int array_capacity = 200000;
  int *result = (int *)calloc(array_capacity, sizeof(int));

  graph_representation[0] = graph.particles_count;
  while (maximum > graph.capacity) {

    // expanding result size
    // printf("Step started: %d with maximum: %d\n", *num_steps, maximum);
    if (*num_steps >= array_capacity) {
      // Double the capacity
      printf("Expanding result size\n");
      array_capacity *= 2;
      int *expanded_result = realloc(result, array_capacity * sizeof(int));
      if (expanded_result == NULL) {
        // Handle reallocation failure
        printf("Memory allocation failed. Exiting...\n");
        free(result); // Free the previously allocated memory
        exit(1);
      }
      result = expanded_result;
    }

    unhappy_count = graph.stepper(&graph_representation, &graph.size,
                                  graph.capacity, &maximum, destinations, &rng);
    result[*num_steps] = unhappy_count;
    // if (*num_steps > 0) {
    //   double var = variance(graph, unhappy_count);
    //   variance_evaluation[*num_steps] = var;
    // }

    (*num_steps)++;
    if (*num_steps % 1000 == 0) {
      printf("Step %d\n", *num_steps);
    }
  }

  free(graph_representation); // Free the graph array
  free(destinations);         // Free the destinations array
  return result;
}
