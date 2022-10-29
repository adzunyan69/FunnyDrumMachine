#include "drum.h"

namespace GUI
{

Drum::Drum(SDL_Renderer *renderer,
           const std::vector<std::string> &files,
           const SDL_Point &pos,
           const SDL_Point &cellSize)
    : pos(pos),
      cellSize(cellSize)
{
    if(files.empty() == true)
    {
        SDL_Log("List of the textures is empty");
        return;
    }

    for(int i = 0; i < files.size(); ++i)
    {
        SDL_Rect textureRect {
            .x = pos.x,
            .y = pos.y + spacingBetweenCells * (i + 1) + cellSize.y * i,
            .w = cellSize.x,
            .h = cellSize.y
        };

        cellsStrongPositions.push_back(textureRect);
        cells.push_back(
                    {
                        std::make_unique<Stuff::Texture>(renderer, files.at(i)),
                        textureRect
                    }
        );

    }
}

Drum::~Drum()
{

}

void Drum::render()
{
    for(auto &[texture, rect] : cells)
    {
        texture->renderTexture(rect);
    }
}

} // GUI
