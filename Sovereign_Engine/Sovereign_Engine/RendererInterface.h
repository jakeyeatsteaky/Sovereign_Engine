#ifndef RENDERER_INTERFACE_H
#define RENDERER_INTERFACE_H

#include "enumerations.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

class Mesh;

class RendererInterface {
public:
	RendererInterface() = default;
	~RendererInterface();

	static std::unique_ptr<RendererInterface> MakeRenderer(RENDERER_API api);

	virtual void Init() const = 0;
	virtual void Render() const = 0;
	virtual void OpenWindow() const = 0;
	virtual void ClearScreen() const = 0;
	virtual void SetupShaders() const = 0;


private:
	std::unordered_map<std::string, Mesh*> m_meshMap;
	RENDERER_API m_activeAPI;
	
};



#endif