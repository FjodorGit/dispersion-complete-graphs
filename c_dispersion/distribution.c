#include "math.h"
#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void run_experiment(Graph graph, const int number_of_simulations) {

  char file_name[200] = "../results/distribution";
  sprintf(file_name, "%s/%s/capacity_%d/data", file_name, graph.graph_type,
          graph.capacity);
  struct stat st = {0};
  if (stat(file_name, &st) == -1) {
    if (mkdir(file_name, 0700) == -1) {
      perror("Error creating directory");
      exit(1);
    }
  }

  printf("file_name: %s\n", file_name);
  sprintf(file_name, "%s/distribution_for_n=%d_M=%d.dat", file_name, graph.size,
          graph.particles_count);

  pcg32_srandom(time(0), 42);

  FILE *file = {fopen(file_name, "w")};

  if (file == NULL) {
    printf("Failed to open file %s\n", file_name);
    return;
  }

  int *result = simulate(number_of_simulations, graph);
  for (int i = 0; i < number_of_simulations; i++) {
    fprintf(file, "%f\n", (float)result[i] / sqrt(graph.size));
  }

  fclose(file);
}

int main(int argc, char *argv[]) {
  const int number_of_simulations = 1;

  Graph graph = get_graph_from_commandline(argc, argv);

  run_experiment(graph, number_of_simulations);
}
