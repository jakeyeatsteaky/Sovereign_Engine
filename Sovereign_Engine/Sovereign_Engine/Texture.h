#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	Texture() = default;
	Texture(const char* pathToTexture);


private:
	unsigned int m_texIdx;
	int m_width;
	int m_height;
	int m_numChannels;
};



#endif