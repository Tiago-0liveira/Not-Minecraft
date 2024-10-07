#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_content(const char *filename);
void checkCompileErrors(GLuint object, const std::string& type);

class Shader {
public:
	GLuint ID;
	Shader(const char *vertexFile, const char *fragmentFile);
	~Shader();

	void Activate();
	void Delete();

	GLuint GetUniformLocation(const char * str);
};

#endif //SHADER_HPP
