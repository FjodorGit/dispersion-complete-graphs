#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

void run_experiment() {
  pcg32_srandom(time(0), 42);
  const int graph_size = 1000000;
  const int particles_count[3] = {495000, 500000, 505000};

  FILE *file = fopen("results/process/data/unhappy_particles_process.txt", "w");

  if (file == NULL) {
    printf("Failed to open file");
    return;
  }

  int *num_steps_equal = malloc(sizeof(int));
  int *num_steps_smaller = malloc(sizeof(int));
  int *num_steps_bigger = malloc(sizeof(int));
  int *unhappy_evaluation_equal = calloc(50000, sizeof(int));
  int *unhappy_evaluation_smaller = calloc(50000, sizeof(int));
  int *unhappy_evaluation_bigger = calloc(50000, sizeof(int));

  unhappy_evaluation_equal =
      unhappy_process(graph_size, particles_count[1], num_steps_equal);
  unhappy_evaluation_smaller =
      unhappy_process(graph_size, particles_count[0], num_steps_smaller);
  unhappy_evaluation_bigger =
      unhappy_process(graph_size, particles_count[2], num_steps_bigger);

  for (int i = 0; i < *num_steps_bigger; i++) {
    fprintf(file, "%d %d %d %d \n", i, unhappy_evaluation_equal[i],
            unhappy_evaluation_smaller[i], unhappy_evaluation_bigger[i]);
  }
  fclose(file);

  free(unhappy_evaluation_equal);   // Free memory allocated in unhappy_process
  free(unhappy_evaluation_bigger);  // Free memory allocated in unhappy_process
  free(unhappy_evaluation_smaller); // Free memory allocated in unhappy_process
  free(num_steps_bigger);
  free(num_steps_smaller);
  free(num_steps_equal);
}

int main() {
  run_experiment();
  return 0;
}
