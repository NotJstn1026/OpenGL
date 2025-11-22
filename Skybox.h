/*****************************************************************************
* Project: OpenGL
* File : Skybox.h
* Date : 18.11.2025
* Author : Justin Martin (JM)
*
* The Skybox class represents a specialized renderable object that simulates
* a vast background environment. It inherits from GLObject and manages the
* loading of a Cubemap texture (6 faces). It overrides the standard Draw
* method to ensure the skybox is rendered correctly behind all other objects
* by manipulating depth testing and view matrices.
*
* History:
* 18.11.25 JM Created
* 18.11.25 JM Added XML documentation comments for all methods
******************************************************************************/

#pragma once
#include "GLObject.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>

class Shader;
class Camera;

/// <summary>
/// Represents a renderable skybox object inheriting from GLObject.
/// This class manages loading cubemap textures, specific shaders,
/// and the rendering logic required to draw a skybox.
/// </summary>
class Skybox : public GLObject
{
public:
	/// <summary>
	/// Constructor for the Skybox class.
	/// Initializes the skybox with a camera and paths to the texture faces.
	/// </summary>
	/// <param name="a_camera">A pointer to the scene camera.</param>
	/// <param name="a_facePaths">A vector of 6 paths to the cubemap faces (Order: Right, Left, Top, Bottom, Front, Back).</param>
	Skybox(Camera* a_camera, std::vector<std::string> a_facePaths);

	/// <summary>
	/// Initializes the skybox (VAO, VBO, EBO, shader, and cubemap texture).
	/// </summary>
	/// <returns>0 on success, otherwise an error code.</returns>
	const int Initialize(void) override;

	/// <summary>
	/// Updates the skybox state.
	/// Usually empty for a static skybox, but can handle rotation.
	/// </summary>
	/// <returns>0 on success, otherwise an error code.</returns>
	const int Update(void) override;

	/// <summary>
	/// Draws the skybox.
	/// Overrides GLObject::Draw to apply special skybox drawing logic
	/// (changing depth function and removing view translation).
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Draw(void) override;

	/// <summary>
	/// Cleans up the skybox resources (VAO, VBO, EBO, shader, texture).
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Finalize(void) override;

private:
	/// <summary>
	/// Loads the 6 images into a single cubemap texture.
	/// </summary>
	/// <returns>0 on success, otherwise an error code.</returns>
	const int LoadCubemap();

	GLuint m_cubemapTextureID = 0; // OpenGL ID for the GL_TEXTURE_CUBE_MAP
	std::vector<std::string> m_facePaths; // Paths to the 6 texture faces

	// Static declarations (kept for reference if needed, though m_ members are used below)
	static std::vector<Vertex> s_skyboxVertices;
	static std::vector<GLint> s_skyboxIndices;

	// Vertices for a cube (Skybox)
	std::vector<Vertex> m_skyboxVertices = std::vector<Vertex>{
		// POSITION                        // COLOR (dummy)        // UV (dummy)       // NORMAL (dummy)
		{ glm::vec3{-1.0f, -1.0f,  1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} }, // 0
		{ glm::vec3{ 1.0f, -1.0f,  1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} }, // 1
		{ glm::vec3{ 1.0f, -1.0f, -1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} }, // 2
		{ glm::vec3{-1.0f, -1.0f, -1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} }, // 3
		{ glm::vec3{-1.0f,  1.0f,  1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} }, // 4
		{ glm::vec3{ 1.0f,  1.0f,  1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} }, // 5
		{ glm::vec3{ 1.0f,  1.0f, -1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} }, // 6
		{ glm::vec3{-1.0f,  1.0f, -1.0f}, glm::vec3{0,0,0}, glm::vec2{0,0}, glm::vec3{0,0,0} }  // 7
	};

	// Indices for drawing the cube triangles
	std::vector<GLint> m_skyboxIndices = std::vector<GLint>{
		// Right
		1, 2, 6, 6, 5, 1,
		// Left
		0, 4, 7, 7, 3, 0,
		// Top
		4, 5, 6, 6, 7, 4,
		// Bottom
		0, 3, 2, 2, 1, 0,
		// Back
		0, 1, 5, 5, 4, 0,
		// Front
		3, 7, 6, 6, 2, 3
	};
};