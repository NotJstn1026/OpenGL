#include "ShaderClass.h"

std::string GetFileContents(const char* filename)
{
	std::ifstream inFile(filename, std::ios::binary);
	if (!inFile)
	{
		throw std::runtime_error("Your error message");
	}

	std::string contents;
	inFile.seekg(0, std::ios::end);
	contents.resize(inFile.tellg());
	inFile.seekg(0, std::ios::beg);
	inFile.read(&contents[0], contents.size());
	inFile.close();
	return(contents);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = GetFileContents(vertexFile);
	std::string fragmentCode = GetFileContents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	m_ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(m_ID);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::Activate() const
{
	glUseProgram(m_ID);
}

// Deletes the Shader Program
void Shader::Delete() const
{
	glDeleteProgram(m_ID);
}