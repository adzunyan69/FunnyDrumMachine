#include "timer.h"

namespace Stuff
{

FrameInfo FPSTimer::getFrameInfo()
{
  float ticks = SDL_GetTicks();

  float frameTime = (ticks - currentTicks) / 1000.0f;
  currentTicks = ticks;
  timeElapsed += frameTime;

  if( timeElapsed >= 0.5f )
  {
    fps = frames / timeElapsed;
    frames = 0;
    timeElapsed = 0.0f;
  }
  else
  {
    ++frames;
  }

  return FrameInfo
  {
    .frameTime = frameTime,
        .fps = fps
  };
}

} // Stuff
