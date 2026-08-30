//
// Created by natha on 8/30/2026.
//

#ifndef PROJECT_BANANA_GENOME_HPP
#define PROJECT_BANANA_GENOME_HPP
#include <random>

#include "Vision.hpp"

struct Genome;

class GeneticSystem {
private:
    inline static std::normal_distribution<float> speed_distribution{0.0f, 0.2f};
    inline static std::normal_distribution<float> energy_distribution{0.0f, 2.0f};

    inline static std::binomial_distribution<int> vision_range_distribution{10, 0.5};
    inline static std::binomial_distribution<int> vision_angle_distribution{20, 0.5};

public:
    static void mutation(std::mt19937& rng, Genome& genome, int mutation_range = 1000);
};


struct Genome {
    float speed = 1.0f;
    float base_energy = 5.0f;
    Vision vision = {2, 360};
    float metabolism = 1.0f;

};


#endif //PROJECT_BANANA_GENOME_HPP
