#include "RendererAPI.h"

// =================================== RENDERER_OPEN_GL ===================================
Renderer_GL::Renderer_GL() :
	window(nullptr),
	renderer(nullptr),
	context(NULL)
{

}

Renderer_GL::~Renderer_GL()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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



	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	SetupShaders();
}

void Renderer_GL::Render() const {

	ClearScreen();

	glUseProgram(shaders[0]->getID());
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(window);
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
	window = SDL_CreateWindow(WINDOW_TITLE, 
							  SDL_WINDOWPOS_UNDEFINED, 
							  SDL_WINDOWPOS_UNDEFINED, 
							  (int)WindowWidth,
							  (int)WindowHeight, 
							  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!window) {
		std::cerr << "Error creating SDL window\n";
		return;
	}

	// OpenGL context
	context = SDL_GL_CreateContext(window);
	if (!context)
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

	glViewport(0, 0, (GLsizei)WindowWidth, (GLsizei)WindowHeight);
	
}

void Renderer_GL::ClearScreen() const 
{
	glClearColor(0.5, 0.3, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_GL::SetupShaders() const 
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(VERTEX_PATH, FRAGMENT_PATH);
	shaders.push_back(shader);
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


