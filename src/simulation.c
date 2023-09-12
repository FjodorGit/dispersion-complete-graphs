#include "pcg/pcg_basic.h"
#include "utils/utils.h"
#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

// Computes the dispersion times for 'num_simulation' processes.
// Returns an array containing these
int *simulate(uint num_simulations, Graph graph) {

  int *result = (int *)malloc(num_simulations * sizeof(int));

#pragma omp parallel
  {
    // initialize variables inside block to private them for every thread
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, omp_get_thread_num(), time(NULL));
    int maximum, num_steps;
    int *graph_representation;

    // array initialized here, to only allocate the memory one time per
    // simulation
    int *destinations = (int *)malloc(graph.particles_count * sizeof(int));
    int graph_size = graph.size;

    printf("Paralellization\n");

#pragma omp for
    for (int i = 0; i < num_simulations; i++) {

      if (strcmp(graph.graph_type, "grid") == 0) {
        graph_size = 3;
        graph_representation = (int *)calloc(2 + graph_size, sizeof(int));
        graph_representation[0] = 1;
        graph_representation[1] = 1;
        graph_representation[2] = graph.particles_count;
      } else {
        graph_representation = (int *)calloc(graph_size, sizeof(int));
        graph_representation[0] = graph.particles_count;
      }
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
        printf("Simulation %d/%d ended with %d steps\n", i, num_simulations,
               num_steps);
      }

      result[i] = num_steps;
    }
    free(graph_representation);
    free(destinations);
  }

  return result;
}
// Simulates one dispersion process and tracks the amount of unhappy particles
// at every step. Produces an array containing these.
int *unhappy_process(Graph graph, int *num_steps, double *variance_evaluation) {

  uint32_t unhappy_count;
  int maximum = graph.particles_count;
  (*num_steps) = 0;
  int *destinations = (int *)malloc(graph.particles_count * sizeof(int));
  pcg32_random_t rng;
  pcg32_srandom_r(&rng, omp_get_thread_num(), time(NULL));
  int array_capacity = 200000;
  int *result = (int *)calloc(array_capacity, sizeof(int));

  int *graph_representation;
  if (strcmp(graph.graph_type, "grid") == 0) {
    graph.size = 3;
    graph_representation = (int *)calloc(2 + graph.size, sizeof(int));
    graph_representation[0] = 1;
    graph_representation[1] = 1;
    graph_representation[2] = graph.particles_count;
  } else {
    graph_representation = (int *)calloc(graph.size, sizeof(int));
    graph_representation[0] = graph.particles_count;
  }

  while (maximum > graph.capacity && *num_steps <= 200000) {

    // expanding result size
    if (*num_steps >= array_capacity) {
      // Just in the case where the process takes a long time to finish and
      // the memory of the preallocated array is not enough to store the amount
      // of unhappy particles at the coming steps. Double the result capacity
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

// Same as above, only here we can specify a maximum amount of steps the process
// is allowed to take before terminating
int *unhappy_process_stopped_early(Graph graph, int *num_steps,
                                   uint step_limit) {

  uint32_t unhappy_count;
  int maximum = graph.particles_count;
  (*num_steps) = 0;
  int *destinations = (int *)malloc(graph.particles_count * sizeof(int));
  pcg32_random_t rng;
  int array_capacity = 21000;
  int *result = (int *)calloc(array_capacity, sizeof(int));

  int *graph_representation;
  if (strcmp(graph.graph_type, "grid") == 0) {
    graph.size = 3;
    graph_representation = (int *)calloc(2 + graph.size, sizeof(int));
    graph_representation[0] = 1;
    graph_representation[1] = 1;
    graph_representation[2] = graph.particles_count;
  } else {
    graph_representation = (int *)calloc(graph.size, sizeof(int));
    graph_representation[0] = graph.particles_count;
  }

  while (maximum > graph.capacity && *num_steps <= step_limit) {

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
