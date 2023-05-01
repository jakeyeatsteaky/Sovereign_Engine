#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include "Renderer.h"
#include "Shaders.h"


SDL_Window* Renderer::window = nullptr;
SDL_Renderer* Renderer::renderer = nullptr;
SDL_GLContext Renderer::context = NULL;
Camera* Renderer::camera = nullptr;
size_t Renderer::windowWidth = Renderer::WINDOW_WIDTH;
size_t Renderer::windowHeight = Renderer::WINDOW_HEIGHT;
GLfloat Renderer::aspect = 0.0f;
std::vector<std::shared_ptr<VertexArray>> Renderer::vertexArrayObjects = {};
std::vector<std::shared_ptr<VertexBuffer>> Renderer::vertexBufferObjects = {};
std::vector<Shader*> Renderer::shaders = {};
glm::mat4 Renderer::model = glm::mat4(1.0f);
//glm::mat4 Renderer::view = glm::mat4(1.0f);
glm::mat4 Renderer::projection = glm::mat4(1.0f);


const char* WINDOW_TITLE = "3D SDL App";

namespace RendererUtility
{
	void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
	{
		GLdouble xmin, xmax, ymin, ymax;

		ymax = zNear * tan(fovy * M_PI / 360.0);
		ymin = -ymax;
		xmin = ymin * aspect;
		xmax = ymax * aspect;

		glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
	}
}


bool Renderer::OpenWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL\n";
		return false;
	}

	// Set the desired OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Create the window using SDL
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)windowWidth, (int)windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!window) {
		std::cerr << "Error creating SDL window\n";
		return false;
	}

	// OpenGL context
	context = SDL_GL_CreateContext(window);
	if (!context)
	{
		std::cerr << "Error creating OpenGL Context\n";
		return false;
	}

	// Enable glew experimental, this enables some more OpenGL extensions.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error initializing glewExperimental\n";
	}

	return true;
}

void Renderer::GLSetup()
{
	Init();
	SetupShaders("../shaders/shader1.vert", "../shaders/shader1.frag");

	// GLLoadGeometr
	float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
	0, 1, 2, // front face
	2, 3, 0,
	1, 5, 6, // right face
	6, 2, 1,
	7, 6, 5, // back face
	5, 4, 7,
	4, 0, 3, // left face
	3, 7, 4,
	4, 5, 1, // bottom face
	1, 0, 4,
	3, 2, 6, // top face
	6, 7, 3
	};

	size_t verticesSize = sizeof(vertices);
	size_t indicesSize = sizeof(indices);
	//endGLLoadGeometry


	// Create Buffer/Array objects
	for (int i = 0; i < 5; ++i)
	{
		std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();
		std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>();

		vbo->Bind(vertices, indices, verticesSize, indicesSize);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// position Attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));	// position Attribute
		glEnableVertexAttribArray(1);

		vertexArrayObjects.push_back(vao);
		vertexBufferObjects.push_back(vbo);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	// end create BAOs
}

void Renderer::Init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	camera = new Camera();
	
}

void Renderer::SetupShaders(std::string vertexPath, std::string fragmentPath)
{
	Shader* shader = new Shader(vertexPath.c_str(), fragmentPath.c_str());
	shaders.push_back(shader);
}

void Renderer::Update()
{
	model = glm::mat4(1.0f);
	camera->view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);

	
}

void Renderer::CloseWindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::ClearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
	GLfloat aspect = (GLfloat)windowWidth / (GLfloat)windowHeight;
	RendererUtility::gluPerspective(45.0f, aspect, 0.1f, 100.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	// Reset the current transform
	glLoadIdentity();
}

void Renderer::RenderFrame()
{
	// Begin Scene - set state for camera, environment, lighting
	// SubmitGeometry - bind a shader, bind a vertex array, draw
	// End Scene - 

	BeginScene();

	glm::vec3 cubePositions[] = {
		
		glm::vec3(2.4f, -0.4f, -15.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	float tick = SDL_GetTicks() / 1000.f;

	for (size_t i = 0; i <= 4; ++i)
	{
		model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
		model = glm::rotate(model, tick, glm::vec3(0.f, 1.f, 0.5f));
		camera->view = glm::lookAt(camera->camVec, camera->camFront, camera->camUp);
		projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
			
		SpecifyShader(0);
		SetActiveVAO(i);
		Draw();

	}

	SwapBuffers();
}

void Renderer::BeginScene()
{
	
}

void Renderer::SubmitGeometry()
{
	
}

void Renderer::EndScene()
{
	
}




void Renderer::SpecifyShader(int shaderIdx)
{
	Shader* shader = shaders.at(shaderIdx);
	shader->use();
	shader->setMat4Uniform("model", model);
	shader->setMat4Uniform("view", camera->view);
	shader->setMat4Uniform("projection", projection);
}

void Renderer::SetActiveVAO(int vaoIdx)
{
	vertexArrayObjects.at(vaoIdx)->BindVertexArray();
}

void Renderer::Draw()
{
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Renderer::SwapBuffers()
{
	SDL_GL_SwapWindow(window);
}

#ifdef USE_DEPRECATED

void Renderer::DrawTriangle(const Vec3& vertex1, const Vec3& vertex2, const  Vec3& vertex3, uint32_t color)
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.0f,1.0f,0.0f, 1.0f);\n"
		"	if(gl_FragCoord.x > gl_FragCoord.y)\n"
		"		FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);  "
		"}\n\0";

	//----- Vertex Shader -----//
	unsigned int vertexShader = CreateVertexShader(vertexShaderSource);

	//----- Fragment Shader -----//
	unsigned int fragmentShader = CreateFragmentShader(fragmentShaderSource);

	//----- Shader Program -----//
	unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);


	// form array from vertices
	float vertices[] = {
		vertex1.xPos, vertex1.yPos, vertex1.zPos,
		vertex2.xPos, vertex2.yPos, vertex2.zPos,
		vertex3.xPos, vertex3.yPos, vertex3.zPos
	};

	std::shared_ptr<VertexArray> vao = vertexArrayObjects.at(0);
	std::shared_ptr<VertexBuffer> vbo = vertexBufferObjects.at(0);

	vao->BindVertexArray();
	//vbo->Bind(vertices, sizeof(vertices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	vbo->ClearFromBinding();
	vao->ClearFromBinding();

	glUseProgram(shaderProgram);

	vao->BindVertexArray();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDeleteProgram(shaderProgram);
	vao->ClearFromBinding();
}

void Renderer::DrawRectangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3, const Vec3& vertex4)
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"out vec3 pos;\n"
		"void main()\n"
		"{\n"
		"pos = aPos;\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 cpuColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = cpuColor;\n"
		"}\n\0";

	//----- Vertex Shader -----//
	unsigned int vertexShader = CreateVertexShader(vertexShaderSource);

	//----- Fragment Shader -----//
	unsigned int fragmentShader = CreateFragmentShader(fragmentShaderSource);

	//----- Shader Program -----//
	unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);


	// form array from vertices
	float vertices[] = {
		vertex1.xPos, vertex1.yPos, vertex1.zPos,
		vertex2.xPos, vertex2.yPos, vertex2.zPos,
		vertex3.xPos, vertex3.yPos, vertex3.zPos,
		vertex4.xPos, vertex4.yPos, vertex4.zPos
	};

	unsigned int indices[] = { 0,1,3,1,2,3 };

	vertexArrayObjects.at(0)->BindVertexArray();
	//vertexBufferObjects.at(0)->Bind(vertices, sizeof(vertices));
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);

	uint32_t timeValue = static_cast<float>(SDL_GetTicks() / 500);
	float green = sin(timeValue) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "cpuColor");
	glUniform4f(vertexColorLocation, 0.0f, green, 0.0f, 1.0f);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	vertexArrayObjects.at(0)->ClearFromBinding();
}

void Renderer::DrawCube_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos)
{
	// Have to change to version 3.1 or lower to use these
	GLfloat angleCube = 0.5f;
	glTranslatef(xPos, yPos, zPos);
	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);

	// Draw the cube
	glBegin(GL_QUADS);
	{
		// Top face (y = 1.0f)
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// Bottom face (y = -1.0f)
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Back face (z = -1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		// Front face (z = -1.0f)
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		// Left face (x = -1.0f)
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// Right face (x = 1.0f)
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	}
	glEnd();
	glLoadIdentity();

}

void Renderer::DrawPyramid_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos)
{
	// Have to use GL version 3.1 or lower to use
	// 
	// Set the pyramid location
	GLfloat anglePyramid = 0.f;
	glTranslatef(xPos, yPos, zPos);
	glRotatef(anglePyramid, 1.0f, 1.0f, 0.0f);

	// Draw the pyramid
	glBegin(GL_TRIANGLES);
	{
		// Front
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Right
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Back
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// Left
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	}
	glEnd();
	glLoadIdentity();

}

unsigned int Renderer::CreateVertexShader(const char* vertexShaderSource)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return vertexShader;
}

unsigned int Renderer::CreateFragmentShader(const char* fragmentShaderSource)
{
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return fragmentShader;
}

unsigned int Renderer::CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

#endif
