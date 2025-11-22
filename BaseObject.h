/*****************************************************************************
* Project: OpenGL
* File : BaseObject.h
* Date : 18.11.2025
* Author : Justin Martin (JM)
*
* The BaseObject class represents a standard 3D object in the scene.
* It inherits from GLObject and implements the specific rendering logic
* for objects that interact with light sources. It supports diffuse and
* specular textures and handles the setup of shader uniforms required
* for lighting calculations.
******************************************************************************/

#pragma once
#include "GLObject.h"

class LightObject;

/// <summary>
/// Represents a standard renderable 3D object that supports lighting.
/// Inherits from GLObject and adds functionality to interact with a LightObject.
/// </summary>
class BaseObject :
	public GLObject
{
public:
	/// <summary>
	/// Constructor with vertices, indices, camera, and a light object.
	/// Shader must be set separately.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indices">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_lightObject">Pointer to the light object affecting this mesh.</param>
	BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, LightObject* a_lightObject)
		: GLObject(a_vertecies, a_indices, a_camera)
	{
		m_lightObject = a_lightObject;
		Initialize();
	};

	/// <summary>
	/// Constructor with vertices, indices, camera, existing shader, and a light object.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indices">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_shader">Pointer to an existing Shader object.</param>
	/// <param name="a_lightObject">Pointer to the light object affecting this mesh.</param>
	BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, Shader* a_shader, LightObject* a_lightObject)
		: GLObject(a_vertecies, a_indices, a_camera, a_shader)
	{
		m_lightObject = a_lightObject;
		Initialize();
	};

	/// <summary>
	/// Constructor that loads a new shader from file paths and sets the light object.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indices">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_vertexPath">File path to the vertex shader.</param>
	/// <param name="a_fragmentPath">File path to the fragment shader.</param>
	/// <param name="a_lightObject">Pointer to the light object affecting this mesh.</param>
	BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, LightObject* a_lightObject)
		: GLObject(a_vertecies, a_indices, a_camera, a_vertexPath, a_fragmentPath)
	{
		m_lightObject = a_lightObject;
		Initialize();
	};

	/// <summary>
	/// Constructor that loads shader, diffuse texture, and sets the light object.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indices">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_vertexPath">File path to the vertex shader.</param>
	/// <param name="a_fragmentPath">File path to the fragment shader.</param>
	/// <param name="a_texturePath">File path to the diffuse texture.</param>
	/// <param name="a_lightObject">Pointer to the light object affecting this mesh.</param>
	BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath, LightObject* a_lightObject)
		: GLObject(a_vertecies, a_indices, a_camera, a_vertexPath, a_fragmentPath, a_texturePath)
	{
		m_lightObject = a_lightObject;
		Initialize();
	};

	/// <summary>
	/// Constructor that loads shader, diffuse texture, specular texture, and sets the light object.
	/// </summary>
	/// <param name="a_vertecies">Pointer to the vector of vertex data.</param>
	/// <param name="a_indices">Pointer to the vector of index data.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_vertexPath">File path to the vertex shader.</param>
	/// <param name="a_fragmentPath">File path to the fragment shader.</param>
	/// <param name="a_texturePath">File path to the diffuse texture.</param>
	/// <param name="a_specularTexPath">File path to the specular map texture.</param>
	/// <param name="a_lightObject">Pointer to the light object affecting this mesh.</param>
	BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath, std::string a_specularTexPath, LightObject* a_lightObject)
		: GLObject(a_vertecies, a_indices, a_camera, a_vertexPath, a_fragmentPath, a_texturePath, a_specularTexPath)
	{
		m_lightObject = a_lightObject;
		Initialize();
	}

	/// <summary>
	/// Initializes the object's OpenGL buffers, textures, and shader uniforms.
	/// </summary>
	/// <returns>0 on success, otherwise an error code.</returns>
	const int Initialize(void) override;

	/// <summary>
	/// Updates the object's logic (e.g., transformations).
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Update(void) override;

	/// <summary>
	/// Renders the object to the screen, applying lighting and textures.
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Draw(void) override;

	/// <summary>
	/// Cleans up OpenGL resources associated with this object.
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Finalize(void) override;

protected:
	/// <summary>
	/// The shininess factor for specular highlights (higher = smaller, sharper highlight).
	/// </summary>
	float m_shininess = 16.0f;

	/// <summary>
	/// Pointer to the light object that illuminates this BaseObject.
	/// </summary>
	LightObject* m_lightObject = nullptr;
};