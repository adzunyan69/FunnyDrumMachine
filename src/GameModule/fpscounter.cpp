#include "fpscounter.h"


namespace GUI
{

FPSCounter::FPSCounter(SDL_Renderer *renderer,
                       const std::string &fontFile,
                       const SDL_Rect pos,
                       const SDL_Color color)
    : renderer(renderer),
      font(TTF_OpenFont(fontFile.c_str(), 14)),
      texture(Stuff::Texture::loadTextTexture(renderer, std::to_string(0.0f), font, color)),
      pos(pos),
      color(color)
{
    SDL_Log("Creating FPSCounter");
    if(font == nullptr)
    {
        SDL_Log("Unable to load font %s", fontFile.c_str());
    }
}

FPSCounter::~FPSCounter()
{
    TTF_CloseFont(font);
}

void FPSCounter::render(float fps)
{
    if(texture == nullptr)
        return;

    if(fps != currentFPS)
    {
        currentFPS = fps;

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << currentFPS;
        texture = Stuff::Texture::loadTextTexture(renderer, stream.str(), font, color);
    }

    texture->renderTexture(pos);
}

} // GUI
