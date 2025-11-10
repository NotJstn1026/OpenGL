#pragma once
#include <glad/glad.h>
#include <stb/std_image.h>
#include "ShaderClass.h"
#include "OLObject.h"

class Texture : public OLObject
{
public:
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind() const override;
	void Unbind() const override;
	void Delete() const override;
	inline GLuint GetID() const { return m_ID; };
	inline GLenum GetType() const { return m_Type; };
private:
	const int M_COLORCHANNELS = 4;

	GLuint m_ID = {};
	GLenum m_Type;
};

