#include "cell.h"

namespace GUI
{

Cell::Cell(SDL_Renderer *renderer,
           const std::string &file,
           const SDL_Rect &currentRect,
           const SDL_Rect &borders)
    : cellTexture(Stuff::Texture::loadTexture(renderer, file)),
      fadeTexture(Stuff::Texture::loadTexture(renderer, "images/test1.bmp")),
      currentRect(currentRect),
      borders(borders),
      currentPositionY(static_cast<float>(currentRect.y))
{
    cellSize = SDL_Point
    {
            .x = currentRect.w,
            .y = currentRect.h
    };
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
    if(cellTexture == nullptr || fadeTexture == nullptr)
        return;


    if(isSplitted)
    {
        fadeTexture->renderTexture(
                    SDL_Rect
                    {
                        .x = 0,
                        .y = currentRect.h,
                        .w = currentRect.w,
                        .h = cellSize.y - currentRect.h
                    },
                    SDL_Rect
                    {
                        .x = currentRect.x,
                        .y = borders.y,
                        .w = currentRect.w,
                        .h = cellSize.y - currentRect.h
                    } );
    }

    cellTexture->renderTexture(
                SDL_Rect
                {
                    .x = 0,
                    .y = 0,
                    .w = currentRect.w,
                    .h = currentRect.h
                },
                currentRect);

}

void Cell::move(float step)
{
    if(cellTexture == nullptr)
        return;

    if((currentPositionY + step) >= static_cast<float>(borders.y + borders.h))
    {
        currentRect.h = cellSize.y;
        isSplitted = false;

        currentPositionY = static_cast<float>(borders.y) + ((currentPositionY - borders.y) + step - borders.h);
        currentRect.y = static_cast<int>(currentPositionY);
    }
    else
    {
        currentPositionY += step;

        currentRect.y = static_cast<int>(currentPositionY);

        if(currentRect.y + cellSize.y > borders.y + borders.h)
        {
            auto diff = (currentRect.y + cellSize.y) - (borders.y + borders.h);
            currentRect.h = cellSize.y - diff;

            isSplitted = true;
        }
    }

}

void Cell::reset(int y)
{
    currentPositionY = static_cast<int>(y);
    currentRect.y = y;
    currentRect.h = cellSize.y;
}

} // GUI
