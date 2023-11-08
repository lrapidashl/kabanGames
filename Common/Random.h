#include <random>

class Random
{
private:
    struct PRNG
    {
        std::mt19937 engine;
    };

    static void initGenerator(PRNG& generator);

public:
    static float random(float minValue, float maxValue);
};
