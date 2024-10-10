#pragma once
#include <random>

static int randrange(int start, int end) {
    // Ensure the end is exclusive, so we need to use (end - start)
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 engine(rd()); // Seed the generator
    std::uniform_int_distribution<int> dist(start, end - 1); // Define the range [start, end)

    return dist(engine); // Generate and return the random number
}

//static float randrange_float(float start, float end) {
//    std::random_device rd; // Obtain a random number from hardware
//    std::mt19937 engine(rd()); // Seed the generator
//    std::uniform_real_distribution<float> dist(start, end); // Define the range [start, end)
//
//    return dist(engine); // Generate and return the random float
//}

static float randrange_float(float start, float end) {
    // Scale the random integer to the desired range
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // Generate a float between 0 and 1
    return start + random * (end - start); // Scale to the desired range [start, end)
}