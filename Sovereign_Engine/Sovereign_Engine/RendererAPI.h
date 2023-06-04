#ifndef RENDERER_API_H
#define RENDERER_API_H

#include "RendererInterface.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include <SDL.h>
#include <SDL_opengl.h>

#include "Shaders.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"

namespace Renderer
{
	constexpr const char* WINDOW_TITLE = "Sovereign Engine";
	constexpr int WindowWidth = 800;
	constexpr int WindowHeight = 600;
	constexpr uint32_t CLEAR_COLOR = 0xff00ffff;
	constexpr const char* VERTEX_PATH = "../shaders/shader1.vert";
	constexpr const char* FRAGMENT_PATH = "../shaders/shader1.frag";
}


class Renderer_GL : public RendererInterface {
public:

	Renderer_GL();
	~Renderer_GL();
	
	// RenderInterface virtual functions
	virtual void Init() const override;
	virtual void Render() const override;
	virtual void OpenWindow() const override;
	virtual void ClearScreen() const override;
	virtual void SetupShaders() const override;

	mutable unsigned int m_vertexArray;
	mutable VertexArray* m_vao;
	// Renderer_GL Specific functions

private:

	mutable SDL_Window* window;
	mutable SDL_Renderer* renderer;
	mutable SDL_GLContext context;
	mutable std::vector<std::shared_ptr<Shader>> shaders;

};


class Renderer_Vulk : public RendererInterface {
public:
	Renderer_Vulk();
	~Renderer_Vulk();
	virtual void Init() const override;
	virtual void Render() const override;
	virtual void OpenWindow() const override;
	virtual void ClearScreen() const override;
	virtual void SetupShaders() const override;
};

class Renderer_DX : public RendererInterface {
public:
	Renderer_DX();
	~Renderer_DX();
	virtual void Init() const override;
	virtual void Render() const override;
	virtual void OpenWindow() const override;
	virtual void ClearScreen() const override;
	virtual void SetupShaders() const override;
};


#endif