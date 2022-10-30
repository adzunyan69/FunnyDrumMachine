#include "drum.h"

namespace GUI
{

Drum::Drum(SDL_Renderer *renderer,
           const std::vector<std::string> &files,
           const SDL_Point &pos,
           const SDL_Point &cellSize)
  : renderer(renderer),
    cellSize(cellSize)
{
  if( files.empty() == true )
  {
    SDL_Log("List of the textures is empty");
    return;
  }

  drumRect = SDL_Rect {
             .x = pos.x,
             .y = pos.y,
             .w = cellSize.x,
             .h = static_cast<int>(cellSize.y * files.size() + spacingBetweenCells * (files.size()))
  };

  for( int i = 0; i < files.size(); ++i )
  {
    SDL_Rect textureRect {
      .x = pos.x,
          .y = pos.y + spacingBetweenCells * (i + 1) + cellSize.y * i - spacingBetweenCells/2,
          .w = cellSize.x,
          .h = cellSize.y
    };



    cellsStrongPositions.push_back(textureRect);
    cells.push_back(
          {
            std::make_unique<Cell>(
            renderer,
            files.at(i),
            textureRect,
            drumRect
            ),
            i
          });
  }
}

Drum::~Drum()
{

}

void Drum::render(float timeStep)
{
  SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
  SDL_RenderFillRect(renderer, &drumRect);

  if( shuffling )
  {

    float moveStep = shufflingSpeed * timeStep;

    if( (targetShufflingDistance - moveStep) <= 0 )
    {
      for( auto &[cell, index] : cells )
        cell->reset(cellsStrongPositions.at(index).y);

      targetShufflingDistance = 0.0f;
      shuffling = false;
    }
    else
    {
      for( auto &[cell, _] : cells )
        cell->move(moveStep);

      targetShufflingDistance -= moveStep;
    }
  }

  for( auto &[cell, _] : cells )
    cell->render();
}

void Drum::startShuffle(float seconds)
{
  if( isShuffling() == true )
    return;

  int steps = static_cast<std::size_t>(Stuff::UniformRandom::uniformInt(5, 10));
  SDL_Log("Steps for the drum: %d", steps);

  setNewIndexes(steps);
  targetShufflingDistance = static_cast<float>(steps) * (cellSize.y + spacingBetweenCells);
  shufflingSpeed = targetShufflingDistance / seconds;

  shuffling = true;
}

bool Drum::isShuffling() const
{
  return shuffling;
}

void Drum::setNewIndexes(std::size_t step)
{
  for( auto &[cell, index] : cells )
    index = (index + step) % cells.size();
}

} // GUI
