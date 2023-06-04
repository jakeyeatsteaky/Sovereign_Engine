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
	 0.25f,  0.35f, 0.0f,	1.0f, 0.0f, 0.0f, 
	 0.25f, -0.25f, 0.0f,	0.0f, 1.0f, 0.0f, 
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 
	-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

#if 0
	HERES WHAT I AM THINKING
		--> Since all the mesh needs is a vertexArray, then I want to be able to separate vertexarray creation
		from the creation of vertex bufferes and index buffers

		I think vertex buffers should be imported upon setup of the app

		from there, they can be stored in a data structure which holds vertex buffers and index buffers

		when a vertex array is created, it accesses an index in that data structure.

		Create Vertex array -> DataStructure.bind()->VBO --> DataStrct7ure.bindf()->IBO

		Then the vertex attribute layout can be set and the vertex array can be moved to the specific mesh
#endif
	
	m_vao = new VertexArray();						// Create Vertex Array Object, and Bind
	VertexBuffer vbo(vertices, sizeof(vertices));	// Bind Vertex Buffer to this VAO
	IndexBuffer ibo(indices, sizeof(indices));		// Bind IBO to this VAO

	VertexLayout vlo(2);							// Create Vertex Layout shell for 2 attributes
	vlo.SetLayout(0, 3, 6, 0);
	vlo.SetLayout(1, 3, 6, 3);
	std::cout << std::boolalpha << vlo.ReadyForUse() << std::endl;

	vbo.ClearFromBinding();

	glBindVertexArray(0);
	ibo.ClearFromBinding();

	SetupShaders();
}

void Renderer_GL::Render() const {

	ClearScreen();



	//TODO #5 ===============================
	
	//	mesh1->Bind() --> specify shader program, then bind the vao

	glUseProgram(shaders[0]->getID());
	m_vao->Bind(); 

	//ENDTODO #5 =============================



	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	window = SDL_CreateWindow(Renderer::WINDOW_TITLE, 
							  SDL_WINDOWPOS_UNDEFINED, 
							  SDL_WINDOWPOS_UNDEFINED, 
							  (int)Renderer::WindowWidth,
							  (int)Renderer::WindowHeight, 
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

	glViewport(0, 0, (GLsizei)Renderer::WindowWidth, (GLsizei)Renderer::WindowHeight);
	
}

void Renderer_GL::ClearScreen() const 
{
	glClearColor(0.5, 0.3, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_GL::SetupShaders() const 
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(Renderer::VERTEX_PATH, Renderer::FRAGMENT_PATH);
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


