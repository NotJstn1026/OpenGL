#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "IObject.h"
#include <string>

class Viewport : public IObject {
public:
	inline Viewport(const int a_windowWidth, const int a_windowHeight, const std::string a_title) : 
		m_windowHeight(a_windowHeight), m_windowWidth(a_windowWidth), m_title(a_title) { }

	const int Initialize(void) override;
	const int Update(void) override;
	const int Draw(void) override;
	const int Finalize(void) override;

	inline struct GLFWwindow* GetWindow() { return m_window; }

private:
	const int m_versionMajor = 4;
	const int m_versionMinor = 6;

	const int m_windowHeight = -1;
	const int m_windowWidth = -1;
	std::string m_title = "";

	GLFWwindow* m_window = nullptr;

	Shader* m_shaderProgramm = nullptr;
	VAO* m_vao = nullptr;
	VBO* m_vbo = nullptr;
	EBO* m_ebo = nullptr;
};

