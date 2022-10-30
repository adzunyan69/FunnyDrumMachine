#ifndef DRUM_H
#define DRUM_H

#include <vector>
#include <memory>
#include "cell.h"
#include "../Stuff/uniformrandom.h"

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

    void render(float timeStep);
    void startShuffle(float seconds);
    bool isShuffling() const;
private:
    SDL_Renderer *renderer{ nullptr };

    std::vector<std::pair<std::unique_ptr<Cell>, std::size_t>> cells;
    std::vector<SDL_Rect> cellsStrongPositions;
    SDL_Rect drumRect;
    SDL_Point cellSize;

    const int spacingBetweenCells { 6 };

    bool shuffling { false };
    float shufflingSpeed { 0.0f };
    float targetShufflingDistance { 0.0f };
    float currentShufflingDistance { 0.0f };

    void setNewIndexes(std::size_t step);
};

} // GUI

#endif // DRUM_H
