#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <vector>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>


#include "DataStructures.h"

class VAO;
class VBO;

struct Graphics
{
	static const size_t WINDOW_WIDTH = 800;
	static const size_t WINDOW_HEIGHT = 600;

	static size_t windowWidth;
	static size_t windowHeight;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_GLContext context;
	static GLfloat aspect;
	static std::vector<std::shared_ptr<VAO>> vertexArrayObjects;
	static std::vector<std::shared_ptr<VBO>> vertexBufferObjects;

	static size_t Width() { return windowWidth; }
	static size_t Height() { return windowHeight; }
	static bool OpenWindow();
	static void GLSetup();
	static void CloseWindow();
	static void Update();
	static void ClearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	static void RenderFrame();

	static unsigned int CreateVertexShader(const char* vertexShaderSource);
	static unsigned int CreateFragmentShader(const char* fragmentShaderSource);
	static unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);


	static void DrawTriangle(float vertices[], size_t verticesSize);
	static void DrawTriangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3, uint32_t color);
	static void DrawRectangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3, const Vec3& vertex4);
	static void DrawCube_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos);
	static void DrawPyramid_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos);

};

class VAO
{
public:
	VAO(size_t n) : size(n) {

		glGenVertexArrays(size, &vao_idx);
	}

	VAO() = default;
	VAO(const VAO& other) :size(other.size), vao_idx(other.vao_idx) {}
	~VAO() = default;

	unsigned int GetUniqueId() { return vao_idx; }

	void BindVertexArray() {
		glBindVertexArray(vao_idx);
	}

	void ClearFromBinding() {
		glBindVertexArray(0);
	}

	void Destroy() {
		printf("Deleting VAO object");
		glDeleteVertexArrays((GLsizei)size, &vao_idx);
	}



	//private:
	size_t size;
	unsigned int vao_idx;
};

class VBO
{
public:
	VBO(size_t n) : size(n) {
		glGenBuffers((GLsizei)size, &vbo_idx);
	}
	VBO(const VBO& other) : size(other.size), vbo_idx(other.vbo_idx) {}
	VBO() = default;
	~VBO() = default;

	void Bind(float* vertices, GLsizeiptr sizevert) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_idx);
		glBufferData(GL_ARRAY_BUFFER, sizevert, vertices, GL_STATIC_DRAW);
	}

	void ClearFromBinding() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Destroy() {
		glDeleteBuffers(size, &vbo_idx);
	}

private:
	unsigned int vbo_idx;
	size_t size;
};

#endif