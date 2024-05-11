#pragma once

namespace Random
{
    int    rand_int(int min, int max);
    float  rand_float(); // returns a value between 0.0f - 1.0f
    double rand_double(); // same as float but higher precision
}