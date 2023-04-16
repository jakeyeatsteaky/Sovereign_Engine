#ifndef APP_H
#define APP_H

class App
{
public:
	App() = default;
	~App() = default;
	void Setup();
	void Input();
	void Update();
	void Render();
	void Destroy();

	bool IsRunning() { return m_isRunning; }

private:
	bool m_isRunning = false;
};


#endif#pragma once
