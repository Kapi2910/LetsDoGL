#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <gl/glew.h>
#include <SOIL2/SOIL2.h>
class Texture
{
public:
	Texture(const std::string& textureFile);
	virtual ~Texture();

	void Bind(unsigned int unit);

private:
	GLuint texture;
};
#endif // !TEXTURE_H
