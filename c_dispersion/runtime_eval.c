#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

void run_experiment() {
  pcg32_srandom(time(0), 42);
  const int number_of_simulations = 200;
  const float epsilon = 0.05;
  int average_num_steps;
  int *result;
  FILE *files[3] = {fopen("./results/data/smaller_half_graph_size.txt", "w"),
                    fopen("./results/data/half_graph_size.txt", "w"),
                    fopen("./results/data/bigger_half_graph_size.txt", "w")};

  for (int file_index = 0; file_index < 3; file_index++) {
    if (files[file_index] == NULL) {
      printf("Failed to open file %d", file_index);
      return;
    }
  }
  for (int graph_size = 100; graph_size <= 1000; graph_size += 50) {
    printf("Graph size: %d \n", graph_size);
    int particles_count[3] = {(int)((1 - epsilon) * (graph_size / 2)),
                              graph_size / 2,
                              (int)((1 + epsilon) * (graph_size / 2))};
    for (int pidx = 0; pidx < 3; pidx++) {
      average_num_steps = 0;
      result =
          simulate(number_of_simulations, graph_size, particles_count[pidx]);
      for (int i = 0; i < number_of_simulations; i++) {
        average_num_steps += result[i];
      }
      average_num_steps = average_num_steps / number_of_simulations;
      printf("Average num steps: %d \n", average_num_steps);
      fprintf(files[pidx], "%d %d\n", graph_size, average_num_steps);
    }
    printf("\n");
  }
  for (int file_index = 0; file_index < 3; file_index++) {
    fclose(files[file_index]);
  }
}

int main() { run_experiment(); }
