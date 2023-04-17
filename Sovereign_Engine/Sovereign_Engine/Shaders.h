

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void use() const;
	unsigned int getID() const { return ID; }

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
	unsigned int ID;
};


#endif

