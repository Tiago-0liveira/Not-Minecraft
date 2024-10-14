#ifndef EBO_HPP
#define EBO_HPP

#include <GL/glew.h>


class EBO {
public:
	GLuint ID;
	EBO(GLuint *indices, GLsizeiptr size);
	~EBO();

	void updateData(GLuint *indices, GLsizeiptr size, GLsizeiptr offset = 0);
	void setData(GLuint *indices, GLsizeiptr size);

	void Bind() const;
	static void Unbind();
	void Delete() const;
};

#endif //EBO_HPP
