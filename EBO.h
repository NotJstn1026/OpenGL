#pragma once
#include "glad/glad.h"
#include "OLObject.h"

class EBO : public OLObject
{
public:
	/// <summary>
	/// Constructor for the Element Buffer Object (EBO).
	/// Generates an EBO, binds it and inserts the index data into it.
	/// </summary>
	/// <param name="indices">Pointer to the first element of the index data array.</param>
	/// <param name="size">The total size, in bytes, of the index data.</param>
	EBO(GLint* indices, GLsizeiptr size);

	/// <summary>
	/// Binds the EBO, making it the active element array buffer for
	/// subsequent draw calls (e.g., glDrawElements).
	/// </summary>
	void Bind() const override;

	/// <summary>
	/// Unbinds the EBO (binds 0) to prevent accidental modification.
	/// </summary>
	void Unbind() const override;

	/// <summary>
	/// Deletes the EBO from GPU memory.
	/// </summary>
	void Delete() const override;

	/// <summary>
	/// Gets the OpenGL ID (handle) of this EBO.
	/// </summary>
	/// <returns>The OpenGL buffer ID.</returns>
	inline GLuint GetID() const { return m_ID; };

private:
	GLuint m_ID = {};
};