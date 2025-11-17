#pragma once

#include "IObject.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Vertex.h"
#include "Texture.h"
#include "Camera.h"

class GLObject :
	public IObject
{
public:
	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indicies, Camera* a_camera) : m_vertecies(a_vertecies), m_indices(a_indicies), m_camera(a_camera) {};


	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indicies, Camera* a_camera, Shader* a_shader)
		: m_vertecies(a_vertecies), m_indices(a_indicies), m_shaderProgram(a_shader), m_camera(a_camera) {
	};


	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath)
		: m_vertecies(a_vertecies), m_indices(a_indices), m_camera(a_camera)
	{
		m_shaderProgram = new Shader(a_vertexPath.c_str(), a_fragmentPath.c_str());
	};

	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath) : m_vertecies(a_vertecies), m_indices(a_indices), m_camera(a_camera)
	{
		m_shaderProgram = new Shader(a_vertexPath.c_str(), a_fragmentPath.c_str());
		m_texturePath = new std::string(a_texturePath);
	};

	GLObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath, std::string a_specularTexPath) : m_vertecies(a_vertecies), m_indices(a_indices), m_camera(a_camera)
	{
		m_shaderProgram = new Shader(a_vertexPath.c_str(), a_fragmentPath.c_str());
		m_texturePath = new std::string(a_texturePath);
		m_specularMapPath = new std::string(a_specularTexPath);
	};

	const virtual int Initialize(void) override = 0;
	const virtual int Update(void) override = 0;
	const virtual int Draw(void) override = 0;
	const virtual int Finalize(void) override = 0;

	void LoadShader(std::string a_vertexPath, std::string a_fragmentPath) { m_shaderProgram = new Shader(a_vertexPath.c_str(), a_fragmentPath.c_str()); }
	void SetShader(Shader* a_shader) { m_shaderProgram = a_shader; }
	void SetVertecies(std::vector<Vertex>* a_vertecies) { m_vertecies = a_vertecies; }
	void SetIndicies(std::vector<GLint>* a_indices) { m_indices = a_indices; }
	void SetCamera(Camera* a_camera) { m_camera = a_camera; }
	void SetTexture(std::string* a_texturePath) { m_texturePath = a_texturePath; }
	void SetSpecularMapTexture(std::string* a_specularMapPath) { m_specularMapPath = a_specularMapPath; }

protected:
	Shader* m_shaderProgram = nullptr;
	VAO* m_VAO = nullptr;
	VBO* m_VBO = nullptr;
	EBO* m_EBO = nullptr;
	Texture* m_texture = nullptr;
	Texture* m_specularMapTexture = nullptr;
	Camera* m_camera = nullptr;

	std::vector<Vertex>* m_vertecies;
	std::vector<GLint>* m_indices;

	std::string* m_texturePath = nullptr;
	std::string* m_specularMapPath = nullptr;
};