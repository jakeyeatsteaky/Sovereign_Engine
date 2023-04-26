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
#include "VertexArray.h"
#include "VertexBuffer.h"

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
	static std::vector<std::shared_ptr<VertexArray>> vertexArrayObjects;
	static std::vector<std::shared_ptr<VertexBuffer>> vertexBufferObjects;

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

	static void DrawTriangle();
	static void DrawTriangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3, uint32_t color);
	static void DrawRectangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3, const Vec3& vertex4);
	static void DrawCube_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos);
	static void DrawPyramid_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos);

};





#endif