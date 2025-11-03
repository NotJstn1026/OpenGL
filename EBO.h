#pragma once
#include "glad/glad.h"
class EBO
{
public:
	EBO(GLint* indices, GLsizeiptr size);

	void Bind() const;
	void Unbind() const;
	void Delete() const;

	inline GLuint GetID() const { return m_ID; };
	inline void SetID(GLuint a_ID) { m_ID = a_ID; };

private:
	GLuint m_ID = {};
};