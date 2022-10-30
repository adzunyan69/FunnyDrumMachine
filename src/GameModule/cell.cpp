#include "cell.h"

namespace GUI
{

Cell::Cell(SDL_Renderer *renderer,
           const std::string &file,
           const SDL_Rect &pos,
           const SDL_Rect &borders)
    : cellTexture(std::make_unique<Stuff::Texture>(renderer, file)),
      pos(pos),
      borders(borders),
      currentPositionY(static_cast<float>(pos.y))
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

void Cell::moveY(float step)
{
    if(cellTexture == nullptr)
        return;

    if((currentPositionY + step) >= static_cast<float>(borders.y + borders.h))
    {
        SDL_Log("currY + step vs b.y + b.h (%f vs %f)", (currentPositionY + step), static_cast<float>(borders.y + borders.h));
        SDL_Log("before border{x%d, y%d, w%d, h%d} currY{%f} pos {x%d, y%d, w%d, h%d} step %f",
                borders.x, borders.y, borders.w, borders.h, currentPositionY, pos.x, pos.y, pos.w, pos.h, step);
        currentPositionY = static_cast<float>(borders.y) + ((currentPositionY - borders.y) + step - borders.h);
        pos.y = static_cast<int>(currentPositionY);
        SDL_Log("after border{x%d, y%d, w%d, h%d} currY{%f} pos {x%d, y%d, w%d, h%d} step %f",
                borders.x, borders.y, borders.w, borders.h, currentPositionY, pos.x, pos.y, pos.w, pos.h, step);
    }
    else
    {
        currentPositionY += step;
        SDL_Log("current Position %f step %f", currentPositionY, step);

        pos.y = static_cast<int>(currentPositionY);
    }

}

void Cell::setPosition(int y)
{
    currentPositionY = static_cast<int>(y);
    pos.y = y;
}

} // GUI
