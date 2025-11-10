#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &m_ID);
}

VAO::~VAO()
{
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkAttribute(VBO &VBO, GLuint layout, GLuint numberOfComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numberOfComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind() const
{
	glBindVertexArray(m_ID);
}

// Unbinds the VAO
void VAO::Unbind() const
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete() const
{
	glDeleteVertexArrays(1, &m_ID);
}