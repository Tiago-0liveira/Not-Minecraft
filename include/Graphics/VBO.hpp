#ifndef VBO_HPP
#define VBO_HPP

#include <GL/glew.h>


class VBO {
public:
	GLuint ID;
	VBO(GLfloat *vertices, GLsizeiptr size);
	~VBO();

	void Bind();
	void Unbind();
	void Delete();
};


#endif //VBO_HPP
