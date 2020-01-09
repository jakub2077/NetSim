#include "helpers.hpp"

#include <cstdlib>

double random_prob(){
    return ((double)rand() / (RAND_MAX));
}

double fixed_prob_05(){
    return 0.5;
}

double fixed_prob_06(){
    return 0.6;
}

double fixed_prob_09(){
    return 0.9;
}

// Do generowania wysokiej jakości ciągów liczb pseudolosowych warto użyć
// zaawansowanych generatorów, np. algorytmu Mersenne Twister.
// zob. https://en.cppreference.com/w/cpp/numeric/random
std::random_device rd;
std::mt19937 rng(rd());

double default_probability_generator() {
    // Generuj liczby pseudolosowe z przedziału [0, 1); 10 bitów losowości.
    return std::generate_canonical<double, 10>(rng);
}

std::function<double()> probability_generator = default_probability_generator;