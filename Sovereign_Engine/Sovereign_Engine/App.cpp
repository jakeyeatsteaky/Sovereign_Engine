#include "App.h"
#include "Graphics.h"

void App::Setup()
{
    m_isRunning = Graphics::OpenWindow();
    Graphics::GLSetup();
}

void App::Input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                m_isRunning = false;
            break;
        }
    }
}

void App::Update()
{
    Graphics::Update();
}

void App::Render()
{
    Graphics::ClearScreen(0.0, 0.0, 0.6, 1.0);
    Graphics::RenderFrame();
}

void App::Destroy()
{
    Graphics::CloseWindow();
}
