#include <Graphics/Texture.hpp>

Texture::Texture(const char *filename, GLenum texType, GLenum slot, GLenum pixelType)
{
	type = texType;
	int numColCh;
	width = height = 0;
	unsigned char *bytes = stbi_load(filename, &width, &height, &numColCh, 0);
	if (!bytes) {
		std::cerr << "Failed to load texture: " << filename << "\nReason: " << stbi_failure_reason() << std::endl;
		return;
	}
	switch (numColCh)
	{
		case 1: colorFormat = GL_RED; break;/* Grayscale */
		case 3: colorFormat = GL_RGB; break;/* RGB */
		case 4: colorFormat = GL_RGBA; break;/* RGBA */
		default:/* Unknown */ {
			throw std::runtime_error(std::format("Unsupported number for color channels: %d\n", numColCh));
			break;
		}
	}

	glGenTextures(1, &ID);
	checkOpenGLErrors("Texture::Texture glGenTextures");

	glActiveTexture(slot);
	checkOpenGLErrors("Texture::Texture glActiveTexture");
	glBindTexture(texType, ID);
	checkOpenGLErrors("Texture::Texture glBindTexture");

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, width, height, 0, colorFormat, pixelType, bytes);
	checkOpenGLErrors("Texture::Texture glTexImage2D");
	glGenerateMipmap(texType);
	checkOpenGLErrors("Texture::Texture glGenerateMipmap");

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
	checkOpenGLErrors("Texture::Texture glBindTexture");

	std::cout << "Texture loaded: " << filename << std::endl;
}

Texture::~Texture()
{
	Delete();
}

void Texture::texUnit(Shader &shader, const char *uniform, GLuint unit)
{
	GLuint tex0Uni = shader.GetUniformLocation(uniform);
	shader.Activate();
	glUniform1i(tex0Uni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

