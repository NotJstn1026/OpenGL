#pragma once
#include<string>
#include<glad/glad.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string GetFileContents(const char* filename);

class Shader
{
public:
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate() const;
	// Deletes the Shader Program
	void Delete() const;

	inline GLuint GetID() const { return m_ID; };
	inline void SetID(GLuint a_ID) { m_ID = a_ID; };
private:
	GLuint m_ID = {};
};