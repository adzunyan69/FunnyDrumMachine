#ifndef DRUM_H
#define DRUM_H

#include <vector>
#include <memory>
#include "../Stuff/texture.h"

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
    std::vector<std::pair<std::unique_ptr<Stuff::Texture>, SDL_Rect>> cells;
    std::vector<SDL_Rect> cellsStrongPositions;
    const SDL_Point pos;
    const SDL_Point cellSize;

    const int spacingBetweenCells { 5 };
};

} // GUI

#endif // DRUM_H
