#include "mainwindow.h"

namespace GUI
{

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

}

bool MainWindow::init()
{
    auto init = (initSDL() &&
                 initWindow() &&
                 initSurface() &&
                 initRenderer());
    texture = std::make_unique<Stuff::Texture>(renderer, "images/test");

    return init;
}

bool MainWindow::loop()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    Stuff::Texture texture{ renderer, "images/test.bmp" };
    //Render texture to screen
    SDL_Rect DestR
    {
        .x = 200,
            .y = 150,
                .w = 50,
                .h = 75
    };
    texture.renderTexture(DestR);

    //Update screen
    SDL_RenderPresent( renderer );

    SDL_Delay(3000);
    return true;
}

bool MainWindow::initSDL()
{
    SDL_Log("Init SDL");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    return true;
}

bool MainWindow::initWindow()
{
    SDL_Log("Init SDL Window");
    window = SDL_CreateWindow(
        "SDL2_Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_width,
        window_height,
        0);

    if (window == nullptr)
    {
        SDL_Log("Unable to window SDL: %s", SDL_GetError());
        return false;
    }
    return true;
}

bool MainWindow::initSurface()
{
    SDL_Log("Init Window Surface");
    surface = SDL_GetWindowSurface(window);

    if(surface == nullptr)
    {
        SDL_Log("Unable to get window surface: %s", SDL_GetError());
        return false;
    }

    return true;
}

bool MainWindow::initRenderer()
{
    SDL_Log("Init SDL Renderer");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (renderer == nullptr)
    {
        SDL_Log("Unable to window SDL: %s", SDL_GetError());
        return false;
    }

    return true;
}

} // GUI
