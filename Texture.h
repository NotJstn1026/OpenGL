#pragma once
#include <glad/glad.h>
#include <stb/std_image.h>
#include "Shader.h"
#include "OLObject.h"

class Texture : public OLObject
{
public:
	/// <summary>
	/// Constructor for the Texture class.
	/// Loads an image, creates and uploads the OpenGL texture data.
	/// </summary>
	/// <param name="a_image">File path to the image.</param>
	/// <param name="a_texType">The OpenGL texture type (e.g., GL_TEXTURE_2D).</param>
	/// <param name="a_slot">The texture slot (e.g., GL_TEXTURE0) to activate.</param>
	/// <param name="a_format">The format of the source image (e.g., GL_RGBA).</param>
	/// <param name="a_pixelType">The data type of the pixel data (e.g., GL_UNSIGNED_BYTE).</param>
	Texture(const char* a_image, GLenum a_texType, GLuint a_slot, GLenum a_format, GLenum a_pixelType);

	/// <summary>
	/// Assigns a texture unit (e.g., 0) to a sampler uniform (e.g., "tex0") in the shader.
	/// </summary>
	/// <param name="shader">The shader program containing the uniform.</param>
	/// <param name="uniform">The name of the sampler uniform in the shader.</param>
	/// <param name="unit">The texture unit ID (0, 1, 2, etc.) to assign.</param>
	void texUnit(Shader& a_shader, const char* a_uniform, GLuint a_unit);

	/// <summary>
	/// Binds the texture, making it active for subsequent rendering operations.
	/// </summary>
	void Bind() const override;

	/// <summary>
	/// Unbinds the texture (binds 0) to prevent accidental modification.
	/// </summary>
	void Unbind() const override;

	/// <summary>
	/// Deletes the texture from GPU memory.
	/// </summary>
	void Delete() const override;

	/// <summary>
	/// Gets the OpenGL ID (handle) of this texture.
	/// </summary>
	/// <returns>The OpenGL texture ID.</returns>
	inline GLuint GetID() const { return m_ID; };

	/// <summary>
	/// Gets the OpenGL type of this texture (e.g., GL_TEXTURE_2D).
	/// </summary>
	/// <returns>The OpenGL texture type.</returns>
	inline GLenum GetType() const { return m_type; };

private:
	/// <summary>
	/// The 4 is to force the number of color channels to 4 (RGBA)
	/// </summary>
	const int M_COLORCHANNELS = 4;

	GLuint m_ID = {};
	GLenum m_type = {};
	GLuint m_unit = {};
};

