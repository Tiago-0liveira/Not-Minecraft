#include <Graphics/Shader.hpp>

std::string get_file_content(const char* filename)
{
	std::cout << "Reading file: " << filename << std::endl;

	// Open the file in binary mode
	std::ifstream in(std::string(PROJECT_ROOT) + "/" + filename, std::ios::binary);
	if (!in) {
		throw std::runtime_error(std::string("Error opening file: ") + strerror(errno));
	}

	// Read the file into a string
	std::string contents;

	// Seek to the end to get file size
	in.seekg(0, std::ios::end);
	std::streamsize size = in.tellg();

	if (size > 0) {
		contents.resize(size); // Resize the string to fit the file size
		in.seekg(0, std::ios::beg); // Seek back to the beginning
		in.read(&contents[0], size); // Read the content into the string
	}

	return contents;
}

void checkCompileErrors(GLuint object, const std::string& type)
{
	GLint success;
	GLchar infoLog[1024];

	if (type == "SHADER") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR\n" << infoLog << "\n";
		}
	}
	else if (type == "PROGRAM") {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, nullptr, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << "\n";
		}
	}
}

Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
	std::string vertexCode = get_file_content(vertexFile);
	std::string fragmentCode = get_file_content(fragmentFile);

	const char *vertexSource = vertexCode.c_str();
	const char *fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "SHADER");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "SHADER");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	Delete();
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

GLuint Shader::GetUniformLocation(const char *str)
{
	return glGetUniformLocation(ID, str);
}