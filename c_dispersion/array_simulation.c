#include "pcg/pcg_basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

void step(int **graph, const uint n, int *maxp) {
  int *destinations = (int *)malloc(sizeof(int) * n);
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

void simulate(uint num_simulations, uint graph_size, uint pariticle_count) {

  int maximum;
  int *graph = (int *)calloc(graph_size, sizeof(int));

  int num_steps;
  for (int i = 0; i < num_simulations; i++) {
    memset(graph, 0, graph_size * sizeof(int));
    graph[0] = pariticle_count;
    maximum = pariticle_count;
    num_steps = 0;
    while (maximum > 1) {
      step(&graph, graph_size, &maximum);
      num_steps++;

      // Print the result
      // printf("[ ");
      // for (int i = 0; i < n; i++) {
      //   printf("%d ", graph[i]);
      // }
      // printf("] \n");
    }
    printf("Num steps: %d \n", num_steps);
  }

  free(graph);
  // return num_steps;
}

int main() {
  pcg32_srandom(time(0), 42);

  int n = 1000000;
  int M = 500000;
  simulate(1, n, M);
  return 0;
}
