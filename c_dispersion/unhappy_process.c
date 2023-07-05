#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <sys/stat.h>
#include <time.h>

void run_experiment(Graph graph) {
  pcg32_srandom(time(0), 42);
  const int particles_count[3] = {0.99 * graph.particles_count,
                                  graph.particles_count,
                                  graph.particles_count * 1.01};

  char file_name[512] = "../results/unhappy_process";
  sprintf(file_name, "%s/%s/capacity_%d", file_name, graph.graph_type,
          graph.capacity);
  struct stat st = {0};
  if (stat(file_name, &st) == -1) {
    if (mkdir(file_name, 0700) == -1) {
      perror("Error creating directory");
      exit(1);
    }
  }

  sprintf(file_name, "%s/data/unhappy_process_n=%d", file_name, graph.size);
  FILE *file = fopen(file_name, "w");

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

  printf("Running unhappy process for n=%d and M=%d", graph.size,
         graph.particles_count);
  unhappy_evaluation_equal = unhappy_process(graph, num_steps_equal);

  graph.particles_count = particles_count[0];
  printf("Running unhappy process for n=%d and M=%d", graph.size,
         graph.particles_count);
  unhappy_evaluation_smaller = unhappy_process(graph, num_steps_smaller);

  graph.particles_count = particles_count[2];
  printf("Running unhappy process for n=%d and M=%d", graph.size,
         graph.particles_count);
  unhappy_evaluation_bigger = unhappy_process(graph, num_steps_bigger);
  printf("Finished unhappy processes.");

  for (int i = 0; i < *num_steps_bigger; i++) {
    fprintf(file, "%d %d %d %d \n", i, unhappy_evaluation_equal[i],
            unhappy_evaluation_smaller[i], unhappy_evaluation_bigger[i]);
  }
  fclose(file);

  free(unhappy_evaluation_equal);
  free(unhappy_evaluation_bigger);
  free(unhappy_evaluation_smaller);
  free(num_steps_bigger);
  free(num_steps_smaller);
  free(num_steps_equal);
}

int main(int argc, char *argv[]) {

  Graph graph = get_graph(argc, argv);
  run_experiment(graph);
  return 0;
}
