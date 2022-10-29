#ifndef BUTTON_H
#define BUTTON_H

#include <memory>
#include "../Stuff/texture.h"

namespace GUI
{

class Button
{
public:
    explicit Button(SDL_Renderer *renderer,
                    const std::string &file,
                    const SDL_Rect &pos);
    virtual ~Button();

    void animate(float timeStep);

private:
    std::unique_ptr<Stuff::Texture> buttonTexture{ nullptr };
    const SDL_Rect pos;

    const Uint8 minTransparency{ 64 };
    const Uint8 maxTransparency{ 255 };
    const Uint8 transparencyChangePerSecond{ 125 };
    float currentTransparency{ static_cast<float>(maxTransparency) };
    bool increaseTransparency{ false };
};

} // GUI

#endif // BUTTON_H
