#include "../graphs/graphs.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

double expected_value(Graph graph, uint32_t unhappy_count) {
  double first_summand = (graph.particles_count - unhappy_count) *
                         (1 - pow(1 - 1.0 / graph.size, unhappy_count));
  double second_summand =
      unhappy_count *
      ((double)(graph.size - graph.particles_count + unhappy_count) /
       graph.size) *
      pow(1 - 1.0 / graph.size, unhappy_count - 1);
  return first_summand - second_summand;
}

// Implementation of the variance from the formula of the thesis
double variance(Graph graph, uint32_t unhappy_count) {
  uint32_t H_t = (graph.particles_count - unhappy_count);
  double hit_free = 1 - ((double)H_t / graph.size);
  double one_minus_one_over_n = 1 - (1.0 / graph.size);
  double one_minus_two_over_n = 1 - (2.0 / graph.size);
  double mult1 = pow(one_minus_one_over_n, unhappy_count - 2);
  double mult2 = one_minus_one_over_n * mult1;
  double mult3 = one_minus_one_over_n * mult2;
  double mult4 = pow(one_minus_two_over_n, unhappy_count - 2);
  double mult5 = one_minus_two_over_n * one_minus_two_over_n * mult4;
  double expected_value_of_square =
      H_t * (1 - mult3) + H_t * (H_t - 1) * (1 - 2 * mult3 + mult5) -
      2 * H_t * unhappy_count * (1 - mult2) * hit_free * mult2 +
      unhappy_count * hit_free * mult2 +
      unhappy_count * (unhappy_count - 1) * hit_free *
          (1 - (double)(H_t - 1) / graph.size) * mult4;
  double expected_value_normal = expected_value(graph, unhappy_count);
  return expected_value_of_square -
         expected_value_normal * expected_value_normal;
}
