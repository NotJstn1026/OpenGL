#pragma once
#include <glad/glad.h>
#include "VBO.h"
#include "OLObject.h"

class VAO : public OLObject
{
public:
	/// <summary>
	/// Constructor for the VAO (Vertex Array Object).
	/// Generates a new VAO ID from OpenGL.
	/// </summary>
	VAO();

	/// <summary>
	/// Destructor for the VAO.
	/// Note: This does NOT automatically delete the VAO from the GPU.
	/// Call Delete() manually before the OpenGL context is destroyed.
	/// </summary>
	~VAO();

	/// <summary>
	/// Configures a vertex attribute for this VAO.
	/// </summary>
	/// <param name="VBO">The Vertex Buffer Object that holds the actual data.</param>
	/// <param name="layout">The layout location in the shader (e.g., "layout(location = 0)").</param>
	/// <param name="numberOfComponents">The number of components for this attribute (e.g., 3 for a vec3).</param>
	/// <param name="type">The data type of the components (e.g., GL_FLOAT).</param>
	/// <param name="stride">The total size (in bytes) of one complete vertex (e.g., sizeof(Vertex)).</param>
	/// <param name="offset">A pointer to the offset (in bytes) of this attribute within the vertex struct (e.g., (void*)offsetof(Vertex, position)).</param>
	void LinkAttribute(VBO& VBO, GLuint layout, GLuint numberOfComponents, GLenum type, GLsizeiptr stride, void* offset);

	/// <summary>
	/// Gets the OpenGL handle (ID) of this VAO.
	/// </summary>
	/// <returns>The GLuint ID of the vertex array.</returns>
	inline GLuint GetID() const { return m_ID; };

	/// <summary>
	/// Binds this VAO, making it the currently active Vertex Array Object.
	/// All subsequent VBO bindings and attribute configurations will be stored in this VAO.
	/// </summary>
	void Bind()const override;

	/// <summary>
	/// Unbinds the currently active VAO (by binding 0).
	/// This is good practice to prevent accidental modifications.
	/// </summary>
	void Unbind()const override;

	/// <summary>
	/// Deletes the VAO from GPU memory.
	/// </summary>
	void Delete()const override;
private:
	GLuint m_ID = {};
};