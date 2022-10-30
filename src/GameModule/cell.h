#ifndef CELL_H
#define CELL_H

#include <memory>
#include "../Stuff/texture.h"

namespace GUI
{

class Cell
{
public:
  Cell(SDL_Renderer *renderer,
       const std::string &file,
       const SDL_Rect &currentRect,
       const SDL_Rect &borders);
  virtual ~Cell();

  void render();
  void move(float step);
  void reset(int y);

private:
  std::unique_ptr<Stuff::Texture> cellTexture{ nullptr };
  std::unique_ptr<Stuff::Texture> fadeTexture{ nullptr };
  SDL_Point cellSize;
  SDL_Rect currentRect;
  const SDL_Rect borders;
  float currentPositionY { 0 };
  bool isSplitted { false };

  void renderFadeTexture();
  void renderCellTexture();
  bool isCellTextureBelowBorders(float step) const;
  bool isCellNeedToBeCropped() const;
};

} // GUI

#endif // CELL_H
