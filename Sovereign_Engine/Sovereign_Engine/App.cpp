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
                    Graphics::camera->camVec += glm::vec3(0.0f, 0.0f, 0.1f);
                }
                else if (event.wheel.y < 0) {
                    std::cout << "wheel backward\n";
                    Graphics::camera->camVec -= glm::vec3(0.0f, 0.0f, 0.1f);
                }
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
    Graphics::RenderFrame();
    Graphics::ClearScreen(0.2, 0.0, 0.6, 1.0);
}

void App::Destroy()
{
    Graphics::CloseWindow();
}
