#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize((in.tellg()));
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = vertexCode.c_str();

	// create vertex shader from source code
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // unsigned GL int. stores the shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader); // compile shader to machine code
	// create fragment shader from source code
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER); // unsigned GL int. stores the shader
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader); // compile shader to machine code

	// wrap the shaders in order to uset them later
	ID = glCreateProgram(); // create shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	// clear the shader source code
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);

}