#pragma once
#include "glad/glad.h"
#include "Vertex.h"
#include "OLObject.h"

class VBO : public OLObject
{
public:

	/// <summary>
	/// Constructor for the VBO (Vertex Buffer Object).
	/// Generates a buffer ID, binds it, and uploads the vertex data to the GPU.
	/// </summary>
	/// <param name="vertices">A pointer to the beginning of the vertex data array.</param>
	/// <param name="size">The total size of the vertex data in bytes (e.g., sizeof(vertices)).</param>
	VBO(Vertex* vertices, GLsizeiptr size);

	/// <summary>
	/// Binds this VBO to the GL_ARRAY_BUFFER target, making it the active buffer.
	/// </summary>
	void Bind() const override;

	/// <summary>
	/// Unbinds the currently active VBO from the GL_ARRAY_BUFFER target (binds 0).
	/// </summary>
	void Unbind() const override;

	/// <summary>
	/// Deletes the VBO from GPU memory.
	/// </summary>
	void Delete() const override;

	/// <summary>
	/// Gets the OpenGL handle (ID) of this VBO.
	/// </summary>
	/// <returns>The GLuint ID of the buffer.</returns>
	inline GLuint GetID() const { return m_ID; };

private:
	GLuint m_ID = {};
};

