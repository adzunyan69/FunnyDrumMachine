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
         const SDL_Rect &pos,
         const SDL_Rect &borders);
    virtual ~Cell();

    void render();
    void moveY(float step);
    void setPosition(int y);

private:
    std::unique_ptr<Stuff::Texture> cellTexture{ nullptr };
    SDL_Rect pos;
    const SDL_Rect borders;
    float currentPositionY { 0 };
};

} // GUI

#endif // CELL_H
