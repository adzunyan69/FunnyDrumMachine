#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

namespace Stuff
{

struct FrameInfo
{
  float frameTime { 0.0 };
  float fps { 0.0 };
};

class FPSTimer
{
public:
  FPSTimer() = default;

  FrameInfo getFrameInfo();

private:
  Uint32 currentTicks{ 0 };
  Uint32 frames{ 0 };
  float timeElapsed { 0.0f };
  float fps { 0.0f };
};

} // Stuff
#endif // TIMER_H
