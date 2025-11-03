#include "EBO.h"

EBO::EBO(GLint* indicies, GLsizeiptr size)
{
	glGenBuffers(1, &m_ID);

	// Bind the Vertex Buffer Object specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

	// Insert the positions into the Vertex Buffer Object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_STATIC_DRAW);
}

void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() const
{
	glDeleteBuffers(1, &m_ID);
}