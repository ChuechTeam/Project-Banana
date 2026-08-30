//
// Created by natha on 8/30/2026.
//

#include "GeneticSystem.hpp"
/**
     *
     * @param rng the rng generator
     * @param mutation_range range of mutation, which would be 1 over range chance of mutation for each attribute. For example, if mutation_range is 1000, then each attribute has a 1/1000 chance of mutating.
     */
void GeneticSystem::mutation(std::mt19937& rng, Genome& genome, int mutation_range) {
    std::normal_distribution<float> speed_distribution(0.0f, 0.2f);
    std::normal_distribution<float> energy_distribution(0.0f, 2.0f);

    std::binomial_distribution<int> vision_range_distribution(10, 0.5);
    std::binomial_distribution<int> vision_angle_distribution(20, 0.5);

    float speed_mutation;
    if (rng() % mutation_range == 0) {
        do {
            speed_mutation = speed_distribution(rng);
        } while (speed_mutation < 0.1f && speed_mutation > -0.1f);
    } else {
        speed_mutation = 0.0f;
    }
    genome.speed = std::max(0.0f, genome.speed + speed_mutation);


    float energy_mutation;
    if (rng() % mutation_range == 0) {
        do {
            energy_mutation = energy_distribution(rng);
        } while (energy_mutation < 1.0f && energy_mutation > -1.0f);
    } else {
        energy_mutation = 0.0f;
    }
    genome.base_energy = std::max(0.0f, genome.base_energy + energy_mutation);

    int vision_range_mutation;
    if (rng() % mutation_range == 0) {
        do {
            vision_range_mutation = vision_range_distribution(rng) - 5;
        } while (vision_range_mutation < 1 && vision_range_mutation > -1);
    } else {
        vision_range_mutation = 0;
    }
    genome.vision.range = std::max(0, genome.vision.range + vision_range_mutation);

    int vision_angle_mutation;
    if (rng() % mutation_range == 0) {
        do {
            vision_angle_mutation = vision_angle_distribution(rng) - 10;
        } while (vision_angle_mutation < 1 && vision_angle_mutation > -1);
    } else {
        vision_angle_mutation = 0;
    }
    genome.vision.angle = std::clamp(genome.vision.angle + vision_angle_mutation, 0, 360);
}
