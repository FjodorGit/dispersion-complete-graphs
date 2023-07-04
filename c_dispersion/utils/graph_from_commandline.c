#include "../simulation.h"
#include <bits/getopt_core.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph get_graph(int argc, char *argv[]) {
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
      if (strcmp(optarg, "circle")) {
        stepper = step_circle;
      } else if (strcmp(optarg, "grid")) {
        printf("Grid graph not implemented yet\n");
        exit(1);
      }
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
  return graph;
}
