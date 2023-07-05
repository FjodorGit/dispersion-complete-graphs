#include <sys/types.h>

typedef int (*stepper)(int **graph_representation, const int graph_size,
                       const int capacity, int *maxp, int *destinations);

typedef struct {
  const int size;
  const int capacity;
  const stepper stepper;
  char graph_type[128];
  int particles_count;
} Graph;

int step_fully_connected(int **graph_representation, const int graph_size,
                         const int capacity, int *maxp, int *destinations);

int step_circle(int **graph_representation, const int graph_size,
                const int capacity, int *maxp, int *destinations);
