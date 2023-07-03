#include <sys/types.h>

typedef int (*stepper)(int **graph_representation, int graph_size, int capacity,
                       int *maxp, int *destinations);

typedef struct {
  const int size;
  const int capacity;
  stepper stepper;
} Graph;

int step_fully_connected(int **graph_representation, int graph_size,
                         int capacity, int *maxp, int *destinations);
