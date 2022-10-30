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
    TTF_Quit();
    SDL_Quit();

}

bool MainWindow::init()
{
    auto init = (initSDL() &&
                 initTTF() &&
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

        auto frameInfo = fpsTimer.getFrameInfo();

        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            if(isShuffling() == false && startButton->isEnabled() == false)
                startButton->setEnabled(true);

            if(startButton->isEnabled())
                startButton->handleEvent(e);

        }

        clear();

        render(frameInfo);
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

bool MainWindow::initTTF()
{
    SDL_Log("Init SDL_TTF");
    if(TTF_Init() != 0)
    {
        SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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

    auto buttonPos = SDL_Rect {
            .x = static_cast<int>(window_width)/2 - 50,
            .y = static_cast<int>(window_height) - 100,
            .w = 100,
            .h = 25
    };

    std::function<void(void)> f = [this] ()
    {
        this->startDrums();
        this->startButton->setEnabled(false);
    };

    startButton = std::make_unique<GUI::Button>(renderer,
                                                "images/button.bmp",
                                                buttonPos,
                                                f);


    const std::vector<std::string> drumImages =
    {
        "images/test.bmp",
        "images/test.bmp",
        "images/test.bmp"
    };

    for(std::size_t i = 0; i < 5; ++i)
    {
        drums.push_back(
                    std::make_unique<GUI::Drum>(renderer,
                                                drumImages,
                                                SDL_Point{.x = static_cast<int>(50 + 100 * i), .y = 50},
                                                SDL_Point{.x = 75, .y = 75}
                                                )
                    );
    }

    fpsCounter = std::make_unique<GUI::FPSCounter>(renderer, "JetBrainsMono-Regular.ttf");

    return true;
}

void MainWindow::startDrums()
{
    for(std::size_t i = 0; i < drums.size(); ++i)
    {
        if(drums.at(i) == nullptr)
            continue;

        drums.at(i)->startShuffle(4.0f + 0.25f * i);
    }
}

bool MainWindow::isShuffling() const
{
    for(auto &drum : drums)
        if(drum->isShuffling())
            return true;

    return false;
}

void MainWindow::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
}

void MainWindow::render(Stuff::FrameInfo frameInfo)
{
    if(startButton != nullptr)
        startButton->render(frameInfo.frameTime);
    for(auto &drum : drums)
    {
        if(drum == nullptr)
            continue;

        drum->render(frameInfo.frameTime);
    }

    if(fpsCounter != nullptr)
        fpsCounter->render(frameInfo.fps);

    SDL_RenderPresent(renderer);
}

} // GUI
