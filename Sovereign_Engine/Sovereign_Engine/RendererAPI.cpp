#include "RendererAPI.h"
#include "Texture.h"

// =================================== RENDERER_OPEN_GL ===================================
Renderer_GL::Renderer_GL() :
	m_window(nullptr),
	m_renderer(nullptr),
	m_context(NULL)
{

}

Renderer_GL::~Renderer_GL()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Renderer_GL::Init() const 
{
	OpenWindow();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	SetupShaders();
	SetupTextures();

	m_mesh = new Mesh(m_shaders[0], m_textures[0]);
}

void Renderer_GL::Render() const {

	ClearScreen();
	
	m_mesh->Render();
	
	SDL_GL_SwapWindow(m_window);
}

void Renderer_GL::OpenWindow() const {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL\n";
		return;
	}

	// Set the desired OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Create the window using SDL
	m_window = SDL_CreateWindow(Renderer::WINDOW_TITLE, 
							  SDL_WINDOWPOS_UNDEFINED, 
							  SDL_WINDOWPOS_UNDEFINED, 
							  (int)Renderer::WindowWidth,
							  (int)Renderer::WindowHeight, 
							  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!m_window) {
		std::cerr << "Error creating SDL window\n";
		return;
	}

	// OpenGL context
	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context)
	{
		std::cerr << "Error creating OpenGL Context\n";
		return;
	}

	// Enable glew experimental, this enables some more OpenGL extensions.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error initializing glewExperimental\n";
	}

	glViewport(0, 0, (GLsizei)Renderer::WindowWidth, (GLsizei)Renderer::WindowHeight);
	
}

void Renderer_GL::ClearScreen() const 
{
	glClearColor((GLclampf)0.5,(GLclampf) 0.3, (GLclampf)1.0,(GLclampf) 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_GL::SetupShaders() const 
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(Renderer::VERTEX_PATH, Renderer::FRAGMENT_PATH);
	m_shaders.push_back(shader);
}

void Renderer_GL::SetupTextures() const
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(Renderer::TEXTURE_PATH, Extension_Type_JPG);
	m_textures.push_back(texture);
}
















// =================================== RENDERER_VULKAN ===================================

Renderer_Vulk::Renderer_Vulk()
{

}

Renderer_Vulk::~Renderer_Vulk()
{

}

void Renderer_Vulk::Init() const {

}

void Renderer_Vulk::Render() const {

}

void Renderer_Vulk::OpenWindow() const {

}

void Renderer_Vulk::ClearScreen() const {

}

void Renderer_Vulk::SetupShaders() const
{
	
}

void Renderer_Vulk::SetupTextures() const
{

}


// =================================== RENDERER_DX3D ===================================

Renderer_DX::Renderer_DX()
{

}

Renderer_DX::~Renderer_DX()
{

}

void Renderer_DX::Init() const {

}

void Renderer_DX::Render() const {

}

void Renderer_DX::OpenWindow() const {

}

void Renderer_DX::ClearScreen() const {

}

void Renderer_DX::SetupShaders() const
{
	
}

void Renderer_DX::SetupTextures() const
{

}


