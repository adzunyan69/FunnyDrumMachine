#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <memory>
#include <SDL.h>
#include "../Stuff/timer.h"
#include "button.h"
#include "drum.h"

namespace GUI 
{

class MainWindow
{
public:
    MainWindow();
    virtual ~MainWindow();

    bool init();
    bool loop();

private:
    Stuff::FPSTimer fpsTimer;

    SDL_Window *window{nullptr};
    SDL_Surface *surface{nullptr};
    SDL_Renderer *renderer{nullptr};

    const unsigned window_width { 640 };
    const unsigned window_height { 480 };

    float currentTime { 0.0f };

    std::unique_ptr<GUI::Button> startButton{ nullptr };
    std::vector<std::unique_ptr<GUI::Drum>> drums;

    bool initSDL();
    bool initWindow();
    bool initSurface();
    bool initRenderer();
    bool initGame();

    void startDrums();
    bool isShuffling() const;

    void clear();
    void render(float timeStep);

};

} // GUI
#endif
