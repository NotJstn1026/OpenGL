/*****************************************************************************
* Project: OpenGL
* File : GLObject.h
* Date : 18.11.2025
* Author : Justin Martin (JM)
*
* The GLObject class is an abstract base class for all renderable objects
* in the OpenGL engine. It provides a common interface (IObject) and
* protected members for core components like shaders, buffers (VAO, VBO, EBO),
* textures, and the camera. It handles the basic setup for passing
* vertex and index data and manages object lifetime through virtual
* Initialize, Update, Draw, and Finalize methods.
*
* History:
* 09.09.25 JM Created
* 18.11.25 JM Added XML documentation comments for all methods
******************************************************************************/

#pragma once

#include "IObject.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Vertex.h"
#include "Texture.h"
#include "Camera.h"

class LightObject;
class Shader;

/// <summary>
/// Abstract base class for any renderable object in the scene.
/// It implements the IObject interface and provides foundational
/// components like buffers, shaders, and textures.
/// </summary>
class GLObject :
	public IObject
{
public:
	/// <summary>
	/// Constructor with vertices, indices, and camera.
	/// Shader must be set separately.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indicies">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indicies, Camera* a_camera) : m_vertecies(a_vertecies), m_indices(a_indicies), m_camera(a_camera) {};

	/// <summary>
	/// Constructor with vertices, indices, camera, and a pre-existing shader.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indicies">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_shader">Pointer to an existing Shader object.</param>
	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indicies, Camera* a_camera, Shader* a_shader)
		: m_vertecies(a_vertecies), m_indices(a_indicies), m_shaderProgram(a_shader), m_camera(a_camera) {
	};

	/// <summary>
	/// Constructor that loads a new shader from file paths.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indices">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_vertexPath">File path to the vertex shader.</param>
	/// <param name="a_fragmentPath">File path to the fragment shader.</param>
	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath)
		: m_vertecies(a_vertecies), m_indices(a_indices), m_camera(a_camera)
	{
		m_shaderProgram = new Shader(a_vertexPath.c_str(), a_fragmentPath.c_str());
	};

	/// <summary>
	/// Constructor that loads a shader and a diffuse texture path.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indices">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_vertexPath">File path to the vertex shader.</param>
	/// <param name="a_fragmentPath">File path to the fragment shader.</param>
	/// <param name="a_texturePath">File path to the diffuse texture.</param>
	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath)
		: m_vertecies(a_vertecies), m_indices(a_indices), m_camera(a_camera)
	{
		m_shaderProgram = new Shader(a_vertexPath.c_str(), a_fragmentPath.c_str());
		m_texturePath = new std::string(a_texturePath);
	};

	/// <summary>
	/// Constructor that loads a shader, diffuse texture path, and specular texture path.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indices">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_vertexPath">File path to the vertex shader.</param>
	/// <param name="a_fragmentPath">File path to the fragment shader.</param>
	/// <param name="a_texturePath">File path to the diffuse texture.</param>
	/// <param name="a_specularTexPath">File path to the specular map texture.</param>
	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath, std::string a_specularTexPath)
		: m_vertecies(a_vertecies), m_indices(a_indices), m_camera(a_camera)
	{
		m_shaderProgram = new Shader(a_vertexPath.c_str(), a_fragmentPath.c_str());
		m_texturePath = new std::string(a_texturePath);
		m_specularMapPath = new std::string(a_specularTexPath);
	};

	/// <summary>
	/// Abstract. Initializes the OpenGL objects (VAO, VBO, EBO) and loads textures.
	/// </summary>
	/// <returns>0 on success, otherwise an error code.</returns>
	const virtual int Initialize(void) override = 0;

	/// <summary>
	/// Abstract. Updates the object's state logic (e.g., physics, animation).
	/// </summary>
	/// <returns>0 on success.</returns>
	const virtual int Update(void) override = 0;

	/// <summary>
	/// Abstract. Renders the object to the screen.
	/// </summary>
	/// <returns>0 on success.</returns>
	const virtual int Draw(void) override = 0;

	/// <summary>
	/// Abstract. Cleans up all allocated OpenGL resources (buffers, textures, shaders).
	/// </summary>
	/// <returns>0 on success.</returns>
	const virtual int Finalize(void) override = 0;

	/// <summary>
	/// Loads and creates a new shader program for this object.
	/// </summary>
	/// <param name="a_vertexPath">File path to the vertex shader.</param>
	/// <param name="a_fragmentPath">File path to the fragment shader.</param>
	void LoadShader(std::string a_vertexPath, std::string a_fragmentPath) { m_shaderProgram = new Shader(a_vertexPath.c_str(), a_fragmentPath.c_str()); }

	/// <summary>
	/// Assigns a pre-existing shader program to this object.
	/// </summary>
	/// <param name="a_shader">Pointer to the shader to use.</param>
	void SetShader(Shader* a_shader) { m_shaderProgram = a_shader; }

	/// <summary>
	/// Sets the vertex data for this object.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	void SetVertecies(std::vector<Vertex>* a_vertecies) { m_vertecies = a_vertecies; }

	/// <summary>
	/// Sets the index data for this object.
	/// </summary>
	/// <param name="a_indices">Pointer to the vector of index data.</param>
	void SetIndicies(std::vector<GLint>* a_indices) { m_indices = a_indices; }

	/// <summary>
	/// Sets the camera this object will use for rendering.
	/// </summary>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	void SetCamera(Camera* a_camera) { m_camera = a_camera; }

	/// <summary>
	/// Sets the file path for the diffuse texture.
	/// </summary>
	/// <param name="a_texturePath">Pointer to the string containing the texture path.</param>
	void SetTexture(std::string* a_texturePath) { m_texturePath = a_texturePath; }

	/// <summary>
	/// Sets the file path for the specular map texture.
	/// </summary>
	/// <param name="a_specularMapPath">Pointer to the string containing the specular map path.</param>
	void SetSpecularMapTexture(std::string* a_specularMapPath) { m_specularMapPath = a_specularMapPath; }

	/// <summary>
	/// Gets a pointer to the shader program used by this object.
	/// </summary>
	/// <returns>A pointer to the Shader object.</returns>
	Shader* GetShaderProgramm() { return m_shaderProgram; };

protected:
	/// <summary>
	/// The shader program used to render this object.
	/// </summary>
	Shader* m_shaderProgram = nullptr;

	/// <summary>
	/// The Vertex Array Object (VAO) that stores buffer configurations.
	/// </summary>
	VAO* m_VAO = nullptr;

	/// <summary>
	/// The Vertex Buffer Object (VBO) that holds vertex data.
	/// </summary>
	VBO* m_VBO = nullptr;

	/// <summary>
	/// The Element Buffer Object (EBO) that holds index data.
	/// </summary>
	EBO* m_EBO = nullptr;

	/// <summary>
	/// The primary (diffuse) texture for this object.
	/// </summary>
	Texture* m_texture = nullptr;

	/// <summary>
	/// The specular map texture for this object.
	/// </summary>
	Texture* m_specularMapTexture = nullptr;

	/// <summary>
	/// Pointer to the scene camera used for rendering.
	/// </summary>
	Camera* m_camera = nullptr;

	/// <summary>
	/// Pointer to the external vector containing vertex data.
	/// </summary>
	std::vector<Vertex>* m_vertecies;

	/// <summary>
	/// Pointer to the external vector containing index data.
	/// </summary>
	std::vector<GLint>* m_indices;

	/// <summary>
	/// Pointer to the string containing the diffuse texture file path.
	/// </summary>
	std::string* m_texturePath = nullptr;

	/// <summary>
	/// Pointer to the string containing the specular map file path.
	/// </summary>
	std::string* m_specularMapPath = nullptr;
};