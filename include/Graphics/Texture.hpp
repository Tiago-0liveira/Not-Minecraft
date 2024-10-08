#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <stb_image.h>
#include <format>

#include <Graphics/openGLThings.hpp>
#include <Graphics/Shader.hpp>

class Texture
{
public:
	Texture(const char *filename, GLenum texType, GLenum slot, GLenum pixelType);
	~Texture();

	void texUnit(Shader &shader, const char *uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();

	GLuint ID;
	GLenum type;
	int width, height;
	GLenum colorFormat;
};

#endif //TEXTURE_HPP
