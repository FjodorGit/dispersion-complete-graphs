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
  const int number_of_processes = 1000;

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
          unhappy_process_stopped_early(graph, num_steps, 5000);

      printf("Finished unhappy processes %d.\n", pr_nr);

      char directory[512] = "../results/average_process";
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

      sprintf(unhappy_process_filename,
              "%s/unhappy_process_n=%d_M=%d_PrNr=%d.dat", directory, graph.size,
              graph.particles_count, pr_nr);

      FILE *unhappy_process_file = fopen(unhappy_process_filename, "w");
      // FILE *variance_file = fopen(variance_filename, "w");

      if (unhappy_process_file == NULL) {
        printf("Failed to open file %s\n", unhappy_process_filename);
        exit(1);
      }
      // if (variance_file == NULL) {
      //   printf("Failed to open file %s\n", variance_filename);
      //   return;
      // }

      for (int i = 0; i < *num_steps; i++) {
        fprintf(unhappy_process_file, "%d\n", unhappy_evaluation[i]);
      }

      // double minus_one_std_diviation;
      // double plus_one_std_diviation;
      // for (int i = 1; i < *num_steps; i++) {
      //   fprintf(variance_file, "%d %f\n", i, variance_evaluation[i]);
      // }

      // fclose(variance_file);
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
