#ifndef DRUM_H
#define DRUM_H

#include <vector>
#include <memory>
#include "cell.h"

namespace GUI
{

class Drum
{
public:
    Drum(SDL_Renderer *renderer,
         const std::vector<std::string> &files,
         const SDL_Point &pos,
         const SDL_Point &cellSize);
    virtual ~Drum();

    void render();
private:
    std::vector<std::unique_ptr<Cell>> cells;
    std::vector<SDL_Rect> cellsStrongPositions;
    const SDL_Point pos;

    const int spacingBetweenCells { 5 };
};

} // GUI

#endif // DRUM_H
