#include <Graphics/VBO.hpp>

#include "Graphics/openGLThings.hpp"

VBO::VBO(GLfloat *vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	setData(vertices, size);
}

VBO::~VBO()
{
	Delete();
}

void VBO::setData(GLfloat *vertices, GLsizeiptr size)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::updateData(GLfloat *vertices, GLsizeiptr size, GLsizeiptr offset)
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	checkOpenGLErrors("VBO::updateData");
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}