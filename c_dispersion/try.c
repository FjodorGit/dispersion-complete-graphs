#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

void append_result_column(char col_name[], char filename[], float *results,
                          int result_len) {

  const char *newFileName = "resulting_file.txt";

  FILE *originalFile = fopen(filename, "r");
  if (originalFile == NULL) {
    printf("Failed to open the file '%s'.\n", filename);
    exit(1);
  }

  FILE *newFile = fopen(newFileName, "w");
  if (newFile == NULL) {
    printf("Failed to create the new result file.\n");
    fclose(originalFile);
    exit(1);
  }

  char line[100];
  int result_index = 0;
  for (; fgets(line, sizeof(line), originalFile) != NULL &&
         result_index < result_len;
       result_index++) {
    // Remove the newline character at the end of the line
    line[strcspn(line, "\n")] = 0;

    fprintf(newFile, "%s %f\n", line, results[result_index]);
  }

  for (; result_index < result_len; result_index++) {
    fprintf(newFile, "%f\n", results[result_index]);
  }

  fclose(originalFile);
  fclose(newFile);

  if (remove(filename) != 0) {
    printf("Failed to remove the old file.\n");
    exit(1);
  }

  if (rename(newFileName, filename) != 0) {
    printf("Failed to rename the new file.\n");
    exit(1);
  }
}

int *simulate(uint num_simulations, Graph graph, uint pariticle_count) {

  int *result = (int *)malloc(num_simulations * sizeof(int));

  for (int i = 0; i < num_simulations; i++) {

    // initialize variables inside for-loop to private them for every thread
    int maximum = pariticle_count;
    int *graph_representation = (int *)calloc(graph.size, sizeof(int));
    graph_representation[0] = pariticle_count;

    // array initialized here, to only allocate the memory one time per
    // simulation
    int *destinations = (int *)malloc(pariticle_count * sizeof(int));

    int num_steps = 0;
    while (maximum > graph.capacity) {
      graph.stepper(&graph_representation, graph.size, graph.capacity, &maximum,
                    destinations);
      num_steps++;

      printf("[ ");
      for (int i = 0; i < graph.size; i++) {
        printf("%d ", graph_representation[i]);
      }
      printf("] \n");
    }
    // printf("Num steps: %d \n", num_steps);

    if (i % 100 == 0) {
      printf("Simulation %d/%d \n", i, num_simulations);
    }

    result[i] = num_steps;
    free(graph_representation);
    free(destinations);
  }

  return result;
}

int main() {
  // float results[5] = {1, 2, 3, 4, 5};
  // append_result_column("name", "test_file.txt", results, 5);
  stepper stepper = step_circle;

  Graph graph = {.size = 10, .capacity = 1, .stepper = stepper};

  simulate(1, graph, 5);
}
