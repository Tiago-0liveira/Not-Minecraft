#include <Graphics/VAO.hpp>

VAO::VAO(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const std::vector<GLfloat> &components)
	: stride(0), offset(nullptr), layout(0), vbo(nullptr), ebo(nullptr), components(components), verticesNum(indices.size())
{
	for (auto &component : components)
		stride += component * sizeof(GLfloat);

	glGenVertexArrays(1, &ID);
	UpdateBuffers(vertices, indices);
}

void VAO::UpdateBuffers(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices) {

	Bind();
	if (ebo == nullptr) {
		ebo = new EBO(indices.data(), indices.size() * sizeof(GLuint));
		if (ebo == nullptr)
			throw std::runtime_error("Failed to create EBO");
	} else
	{
		ebo->updateData(indices.data(), indices.size() * sizeof(GLuint));
	}
	if (vbo == nullptr) {
		vbo = new VBO(vertices.data(), vertices.size() * sizeof(GLfloat));
		if (vbo == nullptr)
			throw std::runtime_error("Failed to create VBO");
	} else
	{
		vbo->updateData(vertices.data(), vertices.size() * sizeof(GLfloat));
	}

	layout = 0;  // Reset the layout index
	offset = nullptr;  // Reset the offset
	verticesNum = indices.size();

	for (auto &size : components)
		LinkVBO(size, GL_FLOAT);

	Unbind();
}

void VAO::LinkVBO(GLint numComponents, GLenum type)
{
	Bind();
	vbo->Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	offset = static_cast<void *>(static_cast<char *>(offset) + numComponents * sizeof(GLfloat));
	layout++;
	vbo->Unbind();
}

void VAO::UnbindEBO()
{
	EBO::Unbind();
}

void VAO::Bind() const
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete() const
{
	glDeleteVertexArrays(1, &ID);
}
