
#pragma once


#include <string>

class Texture
{
private:
	unsigned int m_RendererID; //Object ID
	std::string m_FilePath; //File path for texture
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP; // Width, Height, BitsPerPixel
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0)const;
	void Unbind() const;

	inline int GetWidth()const { return m_Width; }
	inline int GetHeight()const { return m_Height; }
};