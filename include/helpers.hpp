#ifndef NETSIM_HELPERS_HPP
#define NETSIM_HELPERS_HPP

#include "types.hpp"

double random_prob();

double fixed_prob_05();

double fixed_prob_06();

double fixed_prob_09();

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;

#endif //NETSIM_HELPERS_HPP
