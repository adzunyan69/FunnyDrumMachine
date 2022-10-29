#include "button.h"

namespace GUI
{

Button::Button(SDL_Renderer *renderer,
               const std::string &file,
               const SDL_Rect &pos)
    : buttonTexture(std::make_unique<Stuff::Texture>(renderer, file)),
      pos(pos)
{
    SDL_Log("Creating button with texture %s", file.c_str());
    if(buttonTexture == nullptr)
    {
        SDL_Log("Unable to load texture for the button %s", file.c_str());
        return;
    }

    buttonTexture->updateTransparency(currentTransparency);
    buttonTexture->renderTexture(pos);
}

Button::~Button()
{

}

void Button::render(float timeStep)
{
    float transparencyStep = static_cast<float>(transparencyChangePerSecond) * timeStep;
    if(increaseTransparency)
    {
        if(currentTransparency + transparencyStep >= static_cast<float>(maxTransparency))
        {
            currentTransparency = static_cast<float>(maxTransparency) - (transparencyStep - (static_cast<float>(maxTransparency) - currentTransparency));
            increaseTransparency = false;
        }
        else
        {
            currentTransparency += transparencyStep;
        }
    }
    else
    {
        if(currentTransparency - transparencyStep <= static_cast<float>(minTransparency))
        {
            currentTransparency = static_cast<float>(minTransparency) + (transparencyStep - (currentTransparency - static_cast<float>(minTransparency)));
            increaseTransparency = true;
        }
        else
        {
            currentTransparency -= transparencyStep;
        }
    }

    buttonTexture->updateTransparency(static_cast<Uint8>(currentTransparency));
    buttonTexture->renderTexture(pos);
}

} // GUI
