#pragma once

#include<glad/glad.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include"ShaderType.h"


/// <summary>
/// Reads the entire content of a file into a string.
/// </summary>
/// <param name="filename">The path to the file.</param>
/// <returns>A string containing the file's contents.</returns>
std::string GetFileContents(const char* filename);

class Shader
{
public:
	/// <summary>
	/// Creates a Shader Program from vertex and fragment shader files.
	/// </summary>
	/// <param name="vertexFile">The path to the vertex shader source file.</param>
	/// <param name="fragmentFile">The path to the fragment shader source file.</param>
	Shader(const char* vertexFile, const char* fragmentFile);

	/// <summary>
	/// Activates this Shader Program (calls glUseProgram).
	/// </summary>
	void Activate() const;

	/// <summary>
	/// Deletes this Shader Program (calls glDeleteProgram).
	/// </summary>
	void Delete() const;

	/// <summary>
	/// Gets the OpenGL handle (ID) of this Shader Program.
	/// </summary>
	/// <returns>The GLuint ID of the program.</returns>
	inline GLuint GetID() const { return m_ID; };

	/// <summary>
	/// Checks for shader compilation or program linking errors.
	/// </summary>
	/// <param name="a_shader">The OpenGL ID of the shader or program.</param>
	/// <param name="a_shaderType">The type of shader (VERTEX, FRAGMENT, or PROGRAM).</param>
	void CheckForError(unsigned int a_shader, ShaderType a_shaderType);

	/// <summary>
	/// Converts a ShaderType enum to a string.
	/// </summary>
	/// <param name="a_shaderType">The shader type enum.</param>
	/// <returns>A const char* string representation.</returns>
	const char* ShaderTypeToString(ShaderType a_shaderType);
private:
	GLuint m_ID = {};
};