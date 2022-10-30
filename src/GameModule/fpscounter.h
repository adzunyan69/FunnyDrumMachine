#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <SDL_ttf.h>
#include "../Stuff/texture.h"

namespace GUI
{

class FPSCounter
{
public:
    FPSCounter(SDL_Renderer *renderer,
               const std::string &fontFile,
               SDL_Rect pos = SDL_Rect{.x = 15, .y = 450, .w = 45, .h = 15},
               SDL_Color color = SDL_Color{255, 255, 255, 255} );
    virtual ~FPSCounter();

    void render(float fps);
private:
    float currentFPS{ 0.0f };

    SDL_Renderer *renderer{ nullptr };
    const SDL_Rect pos;
    const SDL_Color color;
    const std::size_t fontSize{ 14 };
    TTF_Font* font{ nullptr };
    std::unique_ptr<Stuff::Texture> texture{ nullptr };


};

} // GUI
#endif // FPSCOUNTER_H
