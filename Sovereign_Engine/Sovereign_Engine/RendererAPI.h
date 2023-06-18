#ifndef RENDERER_API_H
#define RENDERER_API_H

#include "RendererInterface.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include <SDL.h>
#include <SDL_opengl.h>

#include "Shaders.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"
#include "Mesh.h"

namespace Renderer
{
	constexpr const char* WINDOW_TITLE = "Sovereign Engine";
	constexpr int WindowWidth = 800;
	constexpr int WindowHeight = 600;
	constexpr uint32_t CLEAR_COLOR = 0xff00ffff;
	constexpr const char* VERTEX_PATH = "../shaders/shader1.vert";
	constexpr const char* FRAGMENT_PATH = "../shaders/shader1.frag";
	constexpr const char* TEXTURE_PATH = "../assets/textures/abc.jpg";
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
	virtual void SetupTextures() const override;

	//mutable unsigned int m_vertexArray;
// 	mutable VertexArray* m_vao;
	// Renderer_GL Specific functions
	mutable Mesh* m_mesh;

private:

	mutable SDL_Window* m_window;
	mutable SDL_Renderer* m_renderer;
	mutable SDL_GLContext m_context;
	mutable std::vector<std::shared_ptr<Shader>>m_shaders;
	mutable std::vector<std::shared_ptr<Texture>> m_textures;

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
	virtual void SetupTextures() const override;
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
	virtual void SetupTextures() const override;
};


#endif