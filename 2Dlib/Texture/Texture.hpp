#include <string>
#include "../../OpenGLWrappers/TextureObj.hpp"


class Texture
{
private:
	TextureObj<GL_TEXTURE_2D> m_textureObj;
	int m_width;
	int m_height;
public:
	void loadFromFile(const std::string &path);
	virtual ~Texture();
};