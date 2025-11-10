#include "ShaderClass.h"
#include<string>

std::string GetFileContents(const char* a_filename)
{
	// Loads the File by filename
	std::ifstream inFile(a_filename, std::ios::binary);
	if (!inFile)
	{
		std::string filename = a_filename;
		throw std::runtime_error("Haven´t found: "+filename);
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

void Shader::CheckForError(unsigned int a_shader, ShaderType a_shaderType)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (a_shaderType != ShaderType::ST_PROGRAM)
	{
		// Check for compilation errors
		glGetShaderiv(a_shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			// Get the error message
			glGetShaderInfoLog(a_shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << ShaderTypeToString(a_shaderType) << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		// Check for linking errors
		glGetProgramiv(a_shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			// Get the error message
			glGetProgramInfoLog(a_shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << ShaderTypeToString(a_shaderType) << "\n" << infoLog << std::endl;
		}
	}
}



const char* Shader::ShaderTypeToString(ShaderType type)
{
	switch (type)
	{
	case ShaderType::ST_VERTEX:
		return "VERTEX";
	case ShaderType::ST_FRAGMENT:
		return "FRAGMENT";
	case ShaderType::ST_PROGRAM:
		return "PROGRAM";
	default:
		return "UNKNOWN";
	}
}