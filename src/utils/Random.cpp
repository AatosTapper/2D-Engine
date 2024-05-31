#include "Random.h"

#include <random>
#include <ctime>
#include <limits>

typedef std::mt19937 rng_type;
rng_type rng;

static uint64_t get_seed()
{
    static uint64_t offset = static_cast<uint64_t>(std::time(nullptr));
    return ++offset;
}

namespace Random
{
    int rand_int(int min, int max)
    {
        rng_type::result_type const seedval = static_cast<uint32_t>(get_seed());
        rng.seed(seedval);

        std::uniform_int_distribution<int> udist(min, max);
        const int random_number = udist(rng);

        return random_number;
    }

    float rand_float()
    {
        return static_cast<float>(rand_double());
    }

    double rand_double()
    {
        constexpr int int_min = std::numeric_limits<int>::min();
        constexpr int int_max = std::numeric_limits<int>::max();
        constexpr uint64_t divider = static_cast<uint64_t>((int64_t)int_max - (int64_t)int_min);

        int num = rand_int(int_min, int_max);

        return static_cast<double>(num - int_min) / divider;
    }
}
