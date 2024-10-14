#include <Graphics/EBO.hpp>

#include "Graphics/openGLThings.hpp"

EBO::EBO(GLuint *indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	setData(indices, size);
}

EBO::~EBO()
{
	Delete();
}

void EBO::setData(GLuint *indices, GLsizeiptr size)
{
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}


void EBO::updateData(GLuint *indices, GLsizeiptr size, GLsizeiptr offset)
{
	Bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indices);
	checkOpenGLErrors("EBO::updateData");
}

void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() const
{
	glDeleteBuffers(1, &ID);
}
