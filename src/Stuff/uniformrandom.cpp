#include "uniformrandom.h"

namespace Stuff
{

int UniformRandom::uniformInt(int min, int max)
{
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    static std::uniform_int_distribution<> distrib(min, max);

    return distrib(gen);
}

} // Stuff
