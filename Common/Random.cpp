#include "Random.h"
#include <cassert>

void Random::initGenerator(Random::PRNG &generator) {
    std::random_device device;
    generator.engine.seed(device());
}

float Random::random(float minValue, float maxValue) {
    PRNG generator;
    initGenerator(generator);
    assert(minValue <= maxValue);

    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    return (float)distribution(generator.engine);
}
