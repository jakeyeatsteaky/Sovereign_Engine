#include "App.h"
#include <iostream>

App::App() :
    m_isRunning(false),
    m_rendererAPI(Renderer_API_Open_GL) 
{
    CreateRenderer();
}

App::~App() {
    
}


void App::Setup()
{
    SetIsRunning(true);

    m_renderer->Init();

    std::cout << "App successfully Set Up\n";
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
                if (event.wheel.y > 0) 
                    std::cout << "wheel forward\n";                                    
                else if (event.wheel.y < 0) 
                    std::cout << "wheel backward\n";                    
                break;
        }

    }
}

void App::Update()
{
    /*
        Update Renderer Subsystem
    */
}

void App::Render()
{
    m_renderer->Render();
}

void App::Destroy()
{
    // Deallocate resources to subsystems 
    std::cout << "App successfully destroyed\n";
}


bool App::IsRunning() {
    return m_isRunning;
}

void App::SetIsRunning(bool isRunning) {
    m_isRunning = isRunning;
}

void App::CreateRenderer() {
    std::string renderer;
    switch (m_rendererAPI)
    {
        case Renderer_API_Open_GL:
		{
            m_renderer = std::make_unique<Renderer_GL>();
            renderer = "Open GL";
			break;
		}
		case Renderer_API_Vulkan:
        {
            m_renderer = std::make_unique<Renderer_Vulk>();
            renderer = "Vulkan";
			break;
        }

		case Renderer_API_DX3D:
        {
            m_renderer = std::make_unique<Renderer_DX>();
            renderer = "Direct X 3D";
            break;
        }

    }

    std::cout << "Created Renderer: " << renderer << std::endl;
}



