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
         const SDL_Rect &pos);
    virtual ~Cell();

    void render();

private:
    std::unique_ptr<Stuff::Texture> cellTexture{ nullptr };
    const SDL_Rect pos;
};

} // GUI

#endif // CELL_H
