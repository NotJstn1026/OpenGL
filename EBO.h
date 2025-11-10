#pragma once
#include "glad/glad.h"
#include "OLObject.h"

class EBO : public OLObject
{
public:
	EBO(GLint* indices, GLsizeiptr size);

	void Bind() const override;
	void Unbind() const override;
	void Delete() const override;

	inline GLuint GetID() const { return m_ID; };

private:
	GLuint m_ID = {};
};