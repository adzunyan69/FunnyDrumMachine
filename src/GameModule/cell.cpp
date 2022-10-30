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

  if( cellTexture == nullptr )
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
  if( cellTexture == nullptr || fadeTexture == nullptr )
    return;


  if( isSplitted )
    renderFadeTexture();

  renderCellTexture();

}

void Cell::renderFadeTexture()
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

void Cell::renderCellTexture()
{
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
  if( cellTexture == nullptr )
    return;

  if( isCellTextureBelowBorders(step) )
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

    if( isCellNeedToBeCropped() )
    {
      int diff = (borders.y + borders.h) - (currentRect.y);
      currentRect.h = diff;

      isSplitted = true;
    }
  }

}

bool Cell::isCellTextureBelowBorders(float step) const
{
  return ( currentPositionY + step) >= static_cast<float>(borders.y + borders.h );
}

bool Cell::isCellNeedToBeCropped() const
{
  return ( currentRect.y + cellSize.y > borders.y + borders.h );
}

void Cell::reset(int y)
{
  currentPositionY = static_cast<int>(y);
  currentRect.y = y;
  currentRect.h = cellSize.y;
}

} // GUI
