#include "math.h"
#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

void run_experiment(const int graph_size, const int number_of_simulations,
                    char *particles_count) {

  float epsilon;
  char *file_name;

  if (strcmp(particles_count, "bigger") == 0) {
    epsilon = 0.02;
    file_name = "results/distribution/data/distribution_bigger.txt";
  }

  if (strcmp(particles_count, "equal") == 0) {
    epsilon = 0;
    file_name = "results/distribution/data/distribution_equal.txt";
  }

  if (strcmp(particles_count, "smaller") == 0) {
    epsilon = -0.04;
    file_name = "results/distribution/data/distribution_smaller_100000.txt";
  }

  pcg32_srandom(time(0), 42);
  const int num_particles = (1 + epsilon) * (graph_size / 2);

  FILE *file = {fopen(file_name, "w")};

  if (file == NULL) {
    printf("Failed to open file");
    return;
  }

  int *result = simulate(number_of_simulations, graph_size, num_particles);
  for (int i = 0; i < number_of_simulations; i++) {
    fprintf(file, "%f\n", (float)result[i] / sqrt(graph_size));
  }

  fclose(file);
}

int main() {
  const int number_of_simulations = 10000;
  const int graph_size = 100000;
  run_experiment(graph_size, number_of_simulations, "equal");
}
