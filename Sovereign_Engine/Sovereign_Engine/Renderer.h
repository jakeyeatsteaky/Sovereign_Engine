#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <vector>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "DataStructures.h"
#include "VertexArray.h"
#include "Shaders.h"
#include "VertexBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera;

class Renderer
{
private:
	static const size_t WINDOW_WIDTH = 800;
	static const size_t WINDOW_HEIGHT = 600;

	static size_t windowWidth;
	static size_t windowHeight;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_GLContext context;
	static GLfloat aspect;
	static Camera* camera;
	static std::vector<std::shared_ptr<VertexArray>> vertexArrayObjects;
	static std::vector<std::shared_ptr<VertexBuffer>> vertexBufferObjects;
	static std::vector<Shader*> shaders;
	static glm::mat4 model;
	//static glm::mat4 view;
	static glm::mat4 projection;

public:
	static size_t Width() { return windowWidth; }
	static size_t Height() { return windowHeight; }
	static Camera* GetCamera() { return camera; }
	static bool OpenWindow();
	static void GLSetup();
	static void Init();
	static void SetupShaders(std::string vertexPath, std::string fragmentPath);
	static void CloseWindow();
	static void Update();
	static void SpecifyShader(int shaderIdx);
	static void ClearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	static void RenderFrame();
	static void SetActiveVAO(int vaoIdx);

	static void BeginScene();
	static void SubmitGeometry();
	static void EndScene();

	static unsigned int CreateVertexShader(const char* vertexShaderSource);
	static unsigned int CreateFragmentShader(const char* fragmentShaderSource);
	static unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	static void Draw();
	static void SwapBuffers();

	static void DrawTriangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3, uint32_t color);
	static void DrawRectangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3, const Vec3& vertex4);
	static void DrawCube_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos);
	static void DrawPyramid_Deprecated(GLfloat xPos, GLfloat yPos, GLfloat zPos);

};

class Camera
{
private:

public:
	Camera() = default;
	~Camera() = default;
	void MoveForward() { camVec -= camFront * cameraSpeed; }
	void MoveBackward() { camVec += camFront * cameraSpeed; }
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 camVec = glm::vec3(0.f, 0.f, 3.f);
	glm::vec3 camFront = glm::vec3(0.f, 0.f, 1.f);
	glm::vec3 camUp = glm::vec3(0.f, 1.f, 0.f);
	float cameraSpeed = 1.5f;
};



#endif