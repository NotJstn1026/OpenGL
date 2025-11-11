#pragma once
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stb/std_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "IObject.h"
#include "Texture.h"
#include "Camera.h"

class Viewport : public IObject {
public:

	/// <summary>
	/// Constructs a new Viewport object with window parameters.
	/// </summary>
	/// <param name="a_windowWidth">The desired width of the window.</param>
	/// <param name="a_windowHeight">The desired height of the window.</param>
	/// <param name="a_title">The title to be displayed on the window's title bar.</param>
	inline Viewport(const int a_windowWidth, const int a_windowHeight, const std::string a_title) :
		m_windowHeight(a_windowHeight), m_windowWidth(a_windowWidth), m_title(a_title) {
	}

	/// <summary>
	/// Initializes GLFW, GLAD, creates the window, and sets up all OpenGL objects.
	/// This includes loading shaders, creating buffers (VAO, VBO, EBO),
	/// and setting vertex attributes.
	/// </summary>
	/// <returns>0 on success, non-zero on failure.</returns>
	const int Initialize(void) override;

	/// <summary>
	/// Runs the main application loop.
	/// </summary>
	/// <returns>0 once the loop terminates.</returns>
	const int Update(void) override;

	/// <summary>
	/// Renders a single frame.
	/// Clears the screen, activates shaders
	/// and swaps the front/back buffers.
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Draw(void) override;

	/// <summary>
	/// Cleans up all allocated resources.
	/// Deletes all OpenGL objects (Shader, VAO, VBO, EBO) and
	/// terminates the GLFW context.
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Finalize(void) override;

	/// <summary>
	/// Gets a pointer to the underlying GLFW window.
	/// </summary>
	/// <returns>A pointer to the GLFWwindow object.</returns>
	inline struct GLFWwindow* GetWindow() { return m_window; }

private:
	const int m_versionMajor = 4;
	const int m_versionMinor = 6;

	const int m_windowHeight = -1;
	const int m_windowWidth = -1;
	std::string m_title = "";

	GLFWwindow* m_window = nullptr;



	Camera* m_camera = nullptr;

	//Needs to be in a object
	Shader* m_shaderProgramm = nullptr;
	VAO* m_vao = nullptr;
	VBO* m_vbo = nullptr;
	EBO* m_ebo = nullptr;


	Shader* m_lightShader = nullptr;
	VAO* m_lightVAO = nullptr;
	VBO* m_lightVBO = nullptr;
	EBO* m_lightEBO = nullptr;

	Texture* m_texture = nullptr;

	std::vector<Vertex> m_vertices =
	{
		// POSITION                     // COLOR                       // TexCoord          // NORMAL
		// Bottom side
		{ glm::vec3{-0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, -1.0f, 0.0f} },
		{ glm::vec3{-0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 5.0f}, glm::vec3{0.0f, -1.0f, 0.0f} },
		{ glm::vec3{ 0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 5.0f}, glm::vec3{0.0f, -1.0f, 0.0f} },
		{ glm::vec3{ 0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{0.0f, -1.0f, 0.0f} },

		// Left Side
		{ glm::vec3{-0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{-0.8f, 0.5f,  0.0f} },
		{ glm::vec3{-0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{-0.8f, 0.5f,  0.0f} },
		{ glm::vec3{ 0.0f, 0.8f,  0.0f}, glm::vec3{0.92f, 0.86f, 0.76f}, glm::vec2{2.5f, 5.0f}, glm::vec3{-0.8f, 0.5f,  0.0f} },

		// Non-facing side
		{ glm::vec3{-0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{ 0.0f, 0.5f, -0.8f} },
		{ glm::vec3{ 0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{ 0.0f, 0.5f, -0.8f} },
		{ glm::vec3{ 0.0f, 0.8f,  0.0f}, glm::vec3{0.92f, 0.86f, 0.76f}, glm::vec2{2.5f, 5.0f}, glm::vec3{ 0.0f, 0.5f, -0.8f} },

		// Right side
		{ glm::vec3{ 0.5f, 0.0f, -0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{ 0.8f, 0.5f,  0.0f} },
		{ glm::vec3{ 0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{ 0.8f, 0.5f,  0.0f} },
		{ glm::vec3{ 0.0f, 0.8f,  0.0f}, glm::vec3{0.92f, 0.86f, 0.76f}, glm::vec2{2.5f, 5.0f}, glm::vec3{ 0.8f, 0.5f,  0.0f} },

		// Facing side
		{ glm::vec3{ 0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{5.0f, 0.0f}, glm::vec3{ 0.0f, 0.5f,  0.8f} },
		{ glm::vec3{-0.5f, 0.0f,  0.5f}, glm::vec3{0.83f, 0.70f, 0.44f}, glm::vec2{0.0f, 0.0f}, glm::vec3{ 0.0f, 0.5f,  0.8f} },
		{ glm::vec3{ 0.0f, 0.8f,  0.0f}, glm::vec3{0.92f, 0.86f, 0.76f}, glm::vec2{2.5f, 5.0f}, glm::vec3{ 0.0f, 0.5f,  0.8f} }
	};

	std::vector<GLint> m_indices =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};

	std::vector<Vertex> lightVertices =
	{
		// POSITION (verschoben um +1.0f auf der X-Achse)
		// COLOR (default)             // TexCoord (default)    // NORMAL (default)
		{ glm::vec3{ 0.9f, -0.1f,  0.1f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 0.9f, -0.1f, -0.1f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 1.1f, -0.1f, -0.1f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 1.1f, -0.1f,  0.1f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 0.9f,  0.1f,  0.1f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 0.9f,  0.1f, -0.1f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 1.1f,  0.1f, -0.1f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} },
		{ glm::vec3{ 1.1f,  0.1f,  0.1f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec2{0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f} }
	};

	std::vector<GLint> lightIndices =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

};

