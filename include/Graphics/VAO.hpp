#ifndef VAO_HPP
#define VAO_HPP

#include <GL/glew.h>
#include <Graphics/VBO.hpp>

class VAO
{
public:
	GLuint ID;
	VAO();

	void LinkVBO(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif //VAO_HPP
