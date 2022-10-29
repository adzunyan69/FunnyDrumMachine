#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <memory>
#include <SDL.h>
#include "../Stuff/texture.h"

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

    std::unique_ptr<Stuff::Texture> texture{ nullptr };

    bool initSDL();
    bool initWindow();
    bool initSurface();
    bool initRenderer();

};

} // GUI
#endif
