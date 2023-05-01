#include "App.h"
#include "Renderer.h"

void App::Setup()
{
    m_isRunning = Renderer::OpenWindow();
    Renderer::GLSetup();
}

void App::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) 
        {
            case SDL_QUIT:
                m_isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    m_isRunning = false;
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0) {
                    std::cout << "wheel forward\n";
                    Renderer::GetCamera()->MoveForward();
                }
                else if (event.wheel.y < 0) {
                    std::cout << "wheel backward\n";
                    Renderer::GetCamera()->MoveBackward();
                }
                break;
        }

    }
}

void App::Update()
{
    Renderer::Update();
}

void App::Render()
{
    Renderer::ClearScreen(0.2, 0.0, 0.6, 1.0);
    Renderer::RenderFrame();
}

void App::Destroy()
{
    Renderer::CloseWindow();
}
