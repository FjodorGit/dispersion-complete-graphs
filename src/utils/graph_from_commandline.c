#include "./utils.h"
#include <bits/getopt_core.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function to process the command line arguments of the programm
// and return the required graph type
Graph get_graph_from_commandline(int argc, char *argv[]) {
  stepper stepper = step_fully_connected;
  int capacity = 1;
  int graph_size = 1;
  int particles_count = 0;
  bool debug_info = false;
  int opt;
  bool user_specified_graph_size = false;
  bool inifinite_graph = false;
  char graph_type[128] = "fully_connected";

  printf("Initializing graph..\n");

  while ((opt = getopt(argc, argv, "s:t:c:p:d")) != -1) {
    switch (opt) {
    case 's':
      graph_size = atoi(optarg);
      user_specified_graph_size = true;
      break;

    case 't':
      if (strcmp(optarg, "line") == 0) {
        stepper = step_line;
        strcpy(graph_type, optarg);
        inifinite_graph = true;
      } else if (strcmp(optarg, "grid") == 0) {
        stepper = step_grid;
        strcpy(graph_type, optarg);
        inifinite_graph = true;
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
      break;

    case 'd':
      debug_info = true;
    }
  }

  if (particles_count < 2) {
    printf("Particles count at least 2\n");
    exit(1);
  }

  if (graph_size < 2 && strcmp(graph_type, "fully_connected") == 0) {
    printf("Graph size has to be at least two on a fully connected graph.\n");
    exit(1);
  }

  if (inifinite_graph && user_specified_graph_size) {
    graph_size = 1;
    printf(
        "Graph of type %s is inifinite. The graph size is irrelevant here.\n",
        graph_type);
  }

  Graph graph = {.size = graph_size,
                 .capacity = capacity,
                 .particles_count = particles_count,
                 .stepper = stepper,
                 .debug_info = debug_info};
  strcpy(graph.graph_type, graph_type);
  return graph;
}
