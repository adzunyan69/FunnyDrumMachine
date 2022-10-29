#include "cell.h"

namespace GUI
{

Cell::Cell(SDL_Renderer *renderer,
           const std::string &file,
           const SDL_Rect &pos)
    : cellTexture(std::make_unique<Stuff::Texture>(renderer, file)),
      pos(pos)
{
    SDL_Log("Creating cell with texture %s", file.c_str());
    if(cellTexture == nullptr)
    {
        SDL_Log("Unable to load texture for the cell %s", file.c_str());
        return;
    }
}

Cell::~Cell()
{
}

void Cell::render()
{
    if(cellTexture == nullptr)
        return;

    cellTexture->renderTexture(pos);
}

} // GUI
