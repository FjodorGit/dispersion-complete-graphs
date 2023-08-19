#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <sys/stat.h>
#include <time.h>

void run_experiment(Graph graph) {
  pcg32_srandom(time(0), 42);

  int *num_steps = malloc(sizeof(int));
  int *unhappy_evaluation = calloc(200000, sizeof(int));
  double *variance_evaluation = calloc(200000, sizeof(int));
  variance_evaluation[0] = 0;

  printf("Running unhappy process for n=%d and M=%d\n", graph.size,
         graph.particles_count);
  unhappy_evaluation = unhappy_process(graph, num_steps, variance_evaluation);

  printf("Finished unhappy processes.");

  char directory[512] = "../results/unhappy_process";
  sprintf(directory, "%s/%s/capacity_%d/data", directory, graph.graph_type,
          graph.capacity);
  struct stat st = {0};
  if (stat(directory, &st) == -1) {
    if (mkdir(directory, 0700) == -1) {
      printf("Error creating directory: %s\n", directory);
      exit(1);
    }
  }

  char unhappy_process_filename[512];
  char variance_filename[512];

  sprintf(unhappy_process_filename, "%s/unhappy_process_n=%d_M=%d.dat",
          directory, graph.size, graph.particles_count);
  sprintf(variance_filename, "%s/variance_process_n=%d_M=%d.dat", directory,
          graph.size, graph.particles_count);

  FILE *unhappy_process_file = fopen(unhappy_process_filename, "w");
  FILE *variance_file = fopen(variance_filename, "w");

  if (unhappy_process_file == NULL) {
    printf("Failed to open file %s\n", unhappy_process_filename);
    return;
  }
  if (variance_file == NULL) {
    printf("Failed to open file %s\n", variance_filename);
    return;
  }

  for (int i = 0; i < *num_steps; i++) {
    fprintf(unhappy_process_file, "%d\n", unhappy_evaluation[i]);
  }

  // double minus_one_std_diviation;
  // double plus_one_std_diviation;
  // for (int i = 1; i < *num_steps; i++) {
  //   fprintf(variance_file, "%d %f\n", i, variance_evaluation[i]);
  // }

  fclose(variance_file);
  fclose(unhappy_process_file);

  free(unhappy_evaluation);
  free(num_steps);
}

int main(int argc, char *argv[]) {

  Graph graph = get_graph_from_commandline(argc, argv);
  run_experiment(graph);
  return 0;
}
