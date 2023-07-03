#include "math.h"
#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>
#include <unistd.h>

void run_experiment(Graph graph, const int number_of_simulations,
                    char *particles_count) {

  float epsilon;
  char *file_name;

  if (strcmp(particles_count, "bigger") == 0) {
    epsilon = 0.01;
    file_name = "results/distribution/data/distribution_bigger.txt";
  }

  if (strcmp(particles_count, "equal") == 0) {
    epsilon = 0;
    file_name = "results/distribution/data/distribution_equal.txt";
  }

  if (strcmp(particles_count, "smaller") == 0) {
    epsilon = -0.02;
    file_name = "results/distribution/data/distribution_smaller.txt";
  }

  pcg32_srandom(time(0), 42);
  const int num_particles = (1 + epsilon) * (graph.size / 2);

  FILE *file = {fopen(file_name, "w")};

  if (file == NULL) {
    printf("Failed to open file");
    return;
  }

  int *result = simulate(number_of_simulations, graph, num_particles);
  for (int i = 0; i < number_of_simulations; i++) {
    fprintf(file, "%f\n", (float)result[i] / sqrt(graph.size));
  }

  fclose(file);
}

int main(int argc, char *argv[]) {
  const int number_of_simulations = 10000;

  stepper stepper = step_fully_connected;
  int capacity = 1;
  int graph_size = 2;
  int opt;

  while ((opt = getopt(argc, argv, "s:t:c:")) != -1) {
    switch (opt) {
    case 's':
      graph_size = atoi(optarg);
      if (graph_size < 2) {
        printf("Graph size has to be at least two\n");
      }
      break;

    case 't':
      if (strcmp(optarg, "fully-connected") != 0 && strcmp(optarg, "circle") &&
          strcmp(optarg, "grid")) {

        printf("Unknown graph %s\n", optarg);
        exit(1);
      }

      stepper = step_fully_connected;

      break;
    case 'c':
      capacity = atoi(optarg);
      if (capacity < 1) {
        printf("Capacity has to be at least 1\n");
        exit(1);
      }
      break;

    case '?':
      printf("Unknown option: %c\n", optopt);
      exit(1);
    }
  }

  Graph graph = {.size = graph_size, .capacity = capacity, .stepper = stepper};

  run_experiment(graph, number_of_simulations, "equal");
}
