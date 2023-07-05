#include "../simulation.h"
#include <bits/getopt_core.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph get_graph_from_commandline(int argc, char *argv[]) {
  stepper stepper = step_fully_connected;
  int capacity = 1;
  int graph_size = 2;
  int particles_count = 0;
  int opt;
  char *graph_type = "fully_connected";

  printf("Initializing graph..\n");

  while ((opt = getopt(argc, argv, "s:t:c:p:")) != -1) {
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
        strcpy(graph_type, optarg);
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

    case 'p':
      particles_count = atoi(optarg);
      if (particles_count < 1) {
        printf("Capacity has to be at least 1\n");
        exit(1);
      }
      break;

    case '?':
      printf("Unknown option: %c\n", optopt);
      exit(1);
    }
  }

  Graph graph = {.size = graph_size,
                 .capacity = capacity,
                 .particles_count = particles_count,
                 .stepper = stepper};
  strcpy(graph.graph_type, graph_type);
  return graph;
}
