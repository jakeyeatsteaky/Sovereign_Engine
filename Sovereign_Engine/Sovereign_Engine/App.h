#ifndef APP_H
#define APP_H
#include <memory>

#include "enumerations.h"
#include "RendererInterface.h"
#include "RendererAPI.h"

class App
{
public:
	App();
	~App();
	void Setup();
	void Input();
	void Update();
	void Render();
	void Destroy();


	void SetIsRunning(bool isRunning);
	bool IsRunning();
	void CreateRenderer();

private:
	bool m_isRunning = false;
	std::unique_ptr<RendererInterface> m_renderer;
	RENDERER_API m_rendererAPI;
};


#endif
