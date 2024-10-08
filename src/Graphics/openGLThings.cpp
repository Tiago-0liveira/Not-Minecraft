#include <Graphics/openGLThings.hpp>

void checkOpenGLErrors(const std::string& msg)
{
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error in " << msg << ": " << error << std::endl;
	}
}