#include "Texture.h"

Texture::Texture(const char* a_image, GLenum a_texType, GLuint a_slot, GLenum a_format, GLenum a_pixelType)
{
	// Assigns the type of the texture ot the texture object
	m_type = a_texType;

	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);

	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(a_image, &widthImg, &heightImg, &numColCh, M_COLORCHANNELS);

	if(bytes == NULL)
	{
		throw std::runtime_error("Failed to load texture image: " + std::string(a_image));
	}

	// Generates an OpenGL texture object
	glGenTextures(1, &m_ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(a_slot);
	m_unit = a_slot;
	glBindTexture(a_texType, m_ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(a_texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(a_texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(a_texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(a_texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(a_texType, 0, GL_RGBA, widthImg, heightImg, 0, a_format, a_pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(a_texType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(a_texType, 0);
}

void Texture::texUnit(Shader& a_shader, const char* a_uniform, GLuint a_unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(a_shader.GetID(), a_uniform);
	// Shader needs to be activated before changing the value of a uniform
	a_shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, a_unit);
}

void Texture::Bind() const
{
	glActiveTexture(m_unit);
	glBindTexture(m_type, m_ID);
}

void Texture::Unbind() const
{
	glBindTexture(m_type, 0);
}

void Texture::Delete() const
{
	glDeleteTextures(1, &m_ID);
}