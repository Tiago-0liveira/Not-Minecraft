#ifndef VAO_HPP
#define VAO_HPP

#include <GL/glew.h>
#include <Graphics/VBO.hpp>
#include <Graphics/EBO.hpp>
#include <vector>
#include <Graphics/openGLThings.hpp>
#include <mutex>

class VAO
{
public:
	VAO(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const std::vector<GLfloat> &components);

	void UpdateBuffers(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices);

	void LinkVBO(GLint numComponents, GLenum type);
	static void UnbindEBO();
	void Bind() const;

	static void Unbind();
	void Delete() const;

public:
	GLsizei verticesNum;
	std::mutex vaoMutex;
private:
	GLuint ID;
	GLsizei stride;
	void *offset;
	GLint layout;
	VBO *vbo;
	EBO *ebo;
	std::vector<GLfloat> components;
};

#endif //VAO_HPP
