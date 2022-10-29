#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <SDL.h>

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
    SDL_Window *window{nullptr};
    SDL_Surface *surface{nullptr};
    SDL_Renderer *renderer{nullptr};

    const unsigned window_width { 640 };
    const unsigned window_height { 480 };

    bool initSDL();
    bool initWindow();
    bool initSurface();
    bool initRenderer();

};

} // GUI
#endif
