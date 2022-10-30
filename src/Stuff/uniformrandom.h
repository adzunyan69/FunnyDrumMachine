#ifndef UNIFORMRANDOM_H
#define UNIFORMRANDOM_H

#include <random>

namespace Stuff
{

class UniformRandom
{
public:
  UniformRandom() = delete;

  static int uniformInt(int min, int max);
};

} // Stuff
#endif // UNIFORMRANDOM_H
