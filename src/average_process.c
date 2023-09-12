#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <sys/stat.h>
#include <time.h>

// Runs the process 1000 times for 5000 steps. Produces 1000 seperate files.
// Later the average over these 1000 process is taken with a python script, to
// produce the average process
void run_experiment(Graph graph) {
  pcg32_srandom(time(0), 42);
  const int number_of_processes = 1000;
  const int stop_early_after = 5000;

  char directory[512] = "../results/average_process";

  // create result directory if missing
  sprintf(directory, "%s/%s/capacity_%d", directory, graph.graph_type,
          graph.capacity);
  struct stat st1 = {0};
  if (stat(directory, &st1) == -1) {
    if (mkdir(directory, 0700) == -1) {
      printf("Error creating directory: %s\n", directory);
      exit(1);
    }
  }

  // create data directory if missing
  sprintf(directory, "%s/data", directory);
  struct stat st2 = {0};
  if (stat(directory, &st2) == -1) {
    if (mkdir(directory, 0700) == -1) {
      printf("Error creating directory: %s\n", directory);
      exit(1);
    }
  }

#pragma omp parallel
  {
    printf("Paralellization\n");
#pragma omp for
    for (int pr_nr = 0; pr_nr < number_of_processes; pr_nr++) {

      int *num_steps = malloc(sizeof(int));
      int *unhappy_evaluation = calloc(21000, sizeof(int));

      printf("Running average unhappy process %d for n=%d and M=%d\n", pr_nr,
             graph.size, graph.particles_count);
      unhappy_evaluation =
          unhappy_process_stopped_early(graph, num_steps, stop_early_after);

      printf("Finished unhappy processes %d.\n", pr_nr);

      char unhappy_process_filename[512];
      char variance_filename[512];

      sprintf(unhappy_process_filename,
              "%s/unhappy_process_n=%d_M=%d_PrNr=%d.dat", directory, graph.size,
              graph.particles_count, pr_nr);

      FILE *unhappy_process_file = fopen(unhappy_process_filename, "w");
      // FILE *variance_file = fopen(variance_filename, "w");

      if (unhappy_process_file == NULL) {
        printf("Failed to open file %s\n", unhappy_process_filename);
        exit(1);
      }

      for (int i = 0; i < *num_steps; i++) {
        fprintf(unhappy_process_file, "%d\n", unhappy_evaluation[i]);
      }

      fclose(unhappy_process_file);

      free(unhappy_evaluation);
      free(num_steps);
    }
  }
}

int main(int argc, char *argv[]) {

  Graph graph = get_graph_from_commandline(argc, argv);
  run_experiment(graph);
  return 0;
}
