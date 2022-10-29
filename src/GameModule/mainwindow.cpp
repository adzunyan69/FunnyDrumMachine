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
    stepTimer.start();
    auto init = (initSDL() &&
                 initWindow() &&
                 initSurface() &&
                 initRenderer() &&
                 initGame());
    return init;
}

bool MainWindow::loop()
{
    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

        }

        clear();

        float timeStep = stepTimer.getTicks() / 1000.f - currentTime;

        render(timeStep);

        currentTime += timeStep;

    }
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        SDL_Log("Unable to window SDL: %s", SDL_GetError());
        return false;
    }

    return true;
}

bool MainWindow::initGame()
{
    SDL_Log("Init Game's stuff");

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    auto buttonPos = SDL_Rect {
            .x = static_cast<int>(window_width)/2 - 50,
            .y = static_cast<int>(window_height) - 100,
            .w = 100,
            .h = 25
    };

    startButton = std::make_unique<GUI::Button>(renderer,
                                                "images/button.bmp",
                                                buttonPos);

    drum = std::make_unique<GUI::Drum>(renderer,
                                       std::vector<std::string>
                                       {
                                           "images/button.bmp",
                                           "images/button.bmp",
                                           "images/button.bmp"
                                        },
                                       SDL_Point{.x = 50, .y = 50},
                                       SDL_Point{.x = 100, .y = 100});

    return true;
}

void MainWindow::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
}

void MainWindow::render(float timeStep)
{
    startButton->render(timeStep);
    drum->render();

    SDL_RenderPresent(renderer);
}

} // GUI
