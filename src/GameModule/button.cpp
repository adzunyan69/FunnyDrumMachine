#include "button.h"

namespace GUI
{

Button::Button(SDL_Renderer *renderer,
               const std::string &file,
               const SDL_Rect &pos,
               std::function< void(void) > &callback)
  : buttonTexture(Stuff::Texture::loadTexture(renderer, file)),
    pos(pos),
    callback(callback)
{
  if( buttonTexture == nullptr )
  {
    SDL_Log("Unable to load texture for the button %s", file.c_str());
    return;
  }

  buttonTexture->updateTransparency(currentTransparency);
}

Button::~Button()
{

}

void Button::setEnabled(bool enable)
{
  if( enable == false )
    currentTransparency = minTransparency;
  else
    currentTransparency = maxTransparency;

  enabled = enable;
}

bool Button::isEnabled() const
{
  return enabled;
}

void Button::render(float timeStep)
{
  if( buttonTexture == nullptr )
    return;

  if( enabled == true )
  {
    float transparencyStep = static_cast<float>(transparencyChangePerSecond) * timeStep;

    if( isIncreasingTransparency )
      increaseTransparency(transparencyStep);
    else
      decreaseTransparency(transparencyStep);
  }

  buttonTexture->updateTransparency(static_cast<Uint8>(currentTransparency));
  buttonTexture->renderTexture(pos);
}

void Button::increaseTransparency(float transparencyStep)
{
  if( (currentTransparency + transparencyStep) >= static_cast<float>(maxTransparency) )
  {
    currentTransparency = static_cast<float>(maxTransparency) - (transparencyStep - (static_cast<float>(maxTransparency) - currentTransparency));
    isIncreasingTransparency = false;
  }
  else
  {
    currentTransparency += transparencyStep;
  }
}

void Button::decreaseTransparency(float transparencyStep)
{
  if( currentTransparency - transparencyStep <= static_cast<float>(minTransparency) )
  {
    currentTransparency = static_cast<float>(minTransparency) + (transparencyStep - (currentTransparency - static_cast<float>(minTransparency)));
    isIncreasingTransparency = true;
  }
  else
  {
    currentTransparency -= transparencyStep;
  }
}

void Button::handleEvent(const SDL_Event &event)
{
  if(event.type == SDL_MOUSEBUTTONDOWN)
  {
    int x, y;
    SDL_GetMouseState( &x, &y );

    if(
       x >= pos.x && x <= (pos.x + pos.w) &&
       y >= pos.y && y <= (pos.y + pos.h))
    {
      callback();
    }
  }
}

} // GUI
