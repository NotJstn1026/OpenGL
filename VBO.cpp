#include "VBO.h"

VBO::VBO(Vertex* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &m_ID);

	// Bind the Vertex Buffer Object specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);

	// Insert the positions into the Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() const
{
	glDeleteBuffers(1, &m_ID);
}