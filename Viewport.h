#pragma once
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stb/std_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "IObject.h"
#include "Texture.h"
#include "Camera.h"
#include "BaseObject.h"
#include "LightObject.h"
#include "Skybox.h"

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

	/// <summary>
	/// Sets up the vertex data for the 3D objects in the scene.
	/// </summary>
	void SetVertexData();

	const int m_versionMajor = 4;
	const int m_versionMinor = 6;

	const int m_windowHeight = -1;
	const int m_windowWidth = -1;
	std::string m_title = "";

	GLFWwindow* m_window = nullptr;

	Camera* m_camera = nullptr;

	Skybox* m_skybox = nullptr;

	BaseObject* m_pyramid = nullptr;
	BaseObject* m_plank = nullptr;

	Shader* m_lightShader = nullptr;
	LightObject* m_lightObject = nullptr;

	Texture* m_texture = nullptr;

	std::vector<Vertex>* m_pyramidVertices = nullptr;
	std::vector<GLint>* m_pyramidIndices = nullptr;
	std::vector<Vertex>* m_floorVertices = nullptr;
	std::vector<GLint>* m_floorIndices = nullptr;
	std::vector<Vertex>* m_lightVertices = nullptr;
	std::vector<GLint>* m_lightIndices = nullptr;
	std::vector<Vertex>* m_skyboxVertices = nullptr;
	std::vector<GLint>* m_skyboxIndices = nullptr;

};