#ifndef VBO_HPP
#define VBO_HPP

#include <GL/glew.h>


class VBO {
public:
	GLuint ID;
	VBO(GLfloat *vertices, GLsizeiptr size);
	~VBO();

	void setData(GLfloat *vertices, GLsizeiptr size);
	void updateData(GLfloat *vertices, GLsizeiptr size, GLsizeiptr offset = 0);

	void Bind();
	void Unbind();
	void Delete();
};


#endif //VBO_HPP
