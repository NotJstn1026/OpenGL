#pragma once
#include <glad/glad.h>
#include "VBO.h"
class VAO
{
public:
	VAO();
	~VAO();
	void LinkVBO(VBO& VBO, GLuint layout);
	GLuint GetID() const { return m_ID; };
	void SetID(GLuint a_ID) { m_ID = a_ID; };
	void Bind();
	void Unbind();
	void Delete();
private:
	GLuint m_ID = {};
};