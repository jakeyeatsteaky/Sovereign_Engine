#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Graphics.h"
#include "Shaders.h"


SDL_Window* Graphics::window = NULL;
SDL_Renderer* Graphics::renderer = NULL;
SDL_GLContext Graphics::context = NULL;
size_t Graphics::windowWidth = Graphics::WINDOW_WIDTH;
size_t Graphics::windowHeight = Graphics::WINDOW_HEIGHT;
GLfloat Graphics::aspect = 0.0f;
std::vector<std::shared_ptr<VAO>> Graphics::vertexArrayObjects = {};
std::vector<std::shared_ptr<VBO>> Graphics::vertexBufferObjects = {};


const char* WINDOW_TITLE = "3D SDL App";

namespace GraphicsUtility
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


bool Graphics::OpenWindow()
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

void Graphics::GLSetup()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//
	std::shared_ptr<VAO> vao = std::make_shared<VAO>(1);
	std::shared_ptr<VBO> vbo = std::make_shared<VBO>(1);
	vertexArrayObjects.push_back(vao);
	vertexBufferObjects.push_back(vbo);
}

void Graphics::Update()
{

}

void Graphics::CloseWindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Graphics::ClearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
	glClearDepth(1.0f);

	glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
	GLfloat aspect = (GLfloat)windowWidth / (GLfloat)windowHeight;
	GraphicsUtility::gluPerspective(45.0f, aspect, 0.1f, 100.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	// Reset the current transform
	glLoadIdentity();
}


void Graphics::RenderFrame()
{
	float vertices[] = {
		// positions         // colors
	   -0.5f, -0.2887f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.2887f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.0f, 0.5774f, 0.0f,    0.0f, 0.0f, 1.0f
	};
	size_t verticesSize = sizeof(vertices);

	DrawTriangle(vertices, verticesSize);
	SDL_GL_SwapWindow(window);
}

unsigned int Graphics::CreateVertexShader(const char* vertexShaderSource)
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

unsigned int Graphics::CreateFragmentShader(const char* fragmentShaderSource)
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

unsigned int Graphics::CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
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

void Graphics::DrawTriangle(float vertices[], size_t verticesSize)
{
	std::string vertexPath = "../shaders/shader1.vert";
	std::string fragmentPath = "../shaders/shader1.frag";
	Shader shader = Shader(vertexPath.c_str(), fragmentPath.c_str());

	vertexArrayObjects.at(0)->BindVertexArray();
	vertexBufferObjects.at(0)->Bind(vertices, verticesSize);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// position Attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));	// color Attribute
	glEnableVertexAttribArray(1);

	vertexArrayObjects.at(0)->ClearFromBinding();
	vertexBufferObjects.at(0)->ClearFromBinding();

	shader.use();

	float value = (float)SDL_GetTicks();
	glm::mat4 trans(1.0f);
	trans = glm::rotate(trans, glm::radians(value), glm::vec3(0.0f, 0.0f, 1.0f));
	unsigned int transLoc = glGetUniformLocation(shader.getID(), "transform");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

	vertexArrayObjects.at(0)->BindVertexArray();

	glDrawArrays(GL_TRIANGLES, 0, 3);

	vertexArrayObjects.at(0)->ClearFromBinding();


}

void Graphics::DrawTriangle(const Vec3& vertex1, const Vec3& vertex2, const  Vec3& vertex3, uint32_t color)
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

	std::shared_ptr<VAO> vao = vertexArrayObjects.at(0);
	std::shared_ptr<VBO> vbo = vertexBufferObjects.at(0);

	vao->BindVertexArray();
	vbo->Bind(vertices, sizeof(vertices));

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

void Graphics::DrawRectangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3, const Vec3& vertex4)
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
	vertexBufferObjects.at(0)->Bind(vertices, sizeof(vertices));
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

void Graphics::DrawCube_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos)
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

void Graphics::DrawPyramid_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos)
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


