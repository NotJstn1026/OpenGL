#pragma once
#include <glad/glad.h>

class OLObject
{
public:

	virtual ~OLObject() = default;
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
	virtual void Delete() const = 0;
};