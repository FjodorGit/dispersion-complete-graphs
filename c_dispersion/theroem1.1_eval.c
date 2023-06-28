#include "pcg/pcg_basic.h"
#include "simulation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

void run_experiment() {
  pcg32_srandom(time(0), 42);
  const int number_of_simulations = 10;
  int A = 1;
  const int graph_size = 10000;

  const float epsilon[3] = {-exp(1) * 1 / sqrt(graph_size) * (1.2),
                            exp(1) * 1 / sqrt(graph_size),
                            exp(1) * 1 / sqrt(graph_size) * (1.2)};
  const int bound[3] = {
      A * 1 / -epsilon[0] * log(epsilon[0] * epsilon[0] * graph_size),
      A * sqrt(graph_size),
      A * (1 / epsilon[2]) * exp(epsilon[2] * epsilon[2] * graph_size)};

  int particles_count[3];
  for (int i = 0; i < 3; i++) {
    particles_count[i] = (1 + epsilon[i]) * (graph_size / 2);
  }
  const float percent_bound = exp(-A);
  int *result;
  int bigger_than_bound;

  for (int i = 0; i < 3; i++) {
    bigger_than_bound = 0;

    printf("bound: %d \n", bound[i]);
    result = simulate(number_of_simulations, graph_size, particles_count[i]);
    for (int j = 0; j < number_of_simulations; j++) {
      if (result[j] > bound[i]) {
        bigger_than_bound++;
      }
    }
    printf("Bigger than bound(%d): %d/%d = %f%% vs Theorecial: %f%%\n",
           bound[i], bigger_than_bound, number_of_simulations,
           (float)bigger_than_bound / number_of_simulations, percent_bound);
    printf("\n");
  }
}
int main() { run_experiment(); }
