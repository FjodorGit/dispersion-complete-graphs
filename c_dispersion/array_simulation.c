#include "pcg/pcg_basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

void step(int **graph, const uint n, int *maxp, int *destinations) {
  int destinations_count = 0;

  for (int i = 0; i < n; i++) {
    int value = (*graph)[i];
    if (value > 1) {
      for (int j = 0; j < value; j++) {
        int random_index = pcg32_boundedrand(n);
        destinations[destinations_count++] = random_index;
      }
    } else if (value == 1) {
      destinations[destinations_count++] = i;
    }
  }

  memset(*graph, 0, n * sizeof(int));
  *maxp = 0;
  for (int i = 0; i < destinations_count; i++) {
    int destination = destinations[i];
    (*graph)[destination]++;
    if ((*graph)[destination] > *maxp) {
      *maxp = (*graph)[destination];
    }
  }
}

int simulate(uint num_simulations, uint graph_size, uint pariticle_count) {

  int maximum;
  int num_steps;
  int *graph = (int *)calloc(graph_size, sizeof(int));
  int *destinations = (int *)malloc(graph_size * sizeof(int));

  int *result = (int *)malloc(num_simulations * sizeof(int));

  for (int i = 0; i < num_simulations; i++) {
    memset(graph, 0, graph_size * sizeof(int));
    graph[0] = pariticle_count;
    maximum = pariticle_count;
    num_steps = 0;
    while (maximum > 1) {
      step(&graph, graph_size, &maximum, destinations);
      num_steps++;

      // Print the result
      // printf("[ ");
      // for (int i = 0; i < graph_size; i++) {
      //   printf("%d ", graph[i]);
      // }
      // printf("] \n");
    }
    // printf("Num steps: %d \n", num_steps);
    result[i] = num_steps;
  }

  free(graph);
  int average = 0;
  for (int i = 0; i < num_simulations; i++) {
    average += result[i];
  }
  return average / num_simulations;
}

void run_experiment() {
  const int number_of_simulations = 200;
  const float epsilon = 0.05;
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
      int average_num_steps =
          simulate(number_of_simulations, graph_size, particles_count[pidx]);
      printf("Average num steps: %d \n", average_num_steps);
      fprintf(files[pidx], "%d %d\n", graph_size, average_num_steps);
    }
    printf("\n");
  }
}

int main() {
  pcg32_srandom(time(0), 42);

  run_experiment();
  return 0;
}
