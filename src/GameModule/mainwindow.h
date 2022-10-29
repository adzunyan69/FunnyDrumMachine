#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <memory>
#include <SDL.h>
#include "../Stuff/timer.h"
#include "button.h"

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
    Stuff::Timer stepTimer;

    SDL_Window *window{nullptr};
    SDL_Surface *surface{nullptr};
    SDL_Renderer *renderer{nullptr};

    const unsigned window_width { 640 };
    const unsigned window_height { 480 };

    float currentTime { 0.0f };

    std::unique_ptr<GUI::Button> startButton{ nullptr };

    bool initSDL();
    bool initWindow();
    bool initSurface();
    bool initRenderer();
    bool initGame();

    void clear();
    void render(float timeStep);

};

} // GUI
#endif
