#pragma once
#include "GLObject.h"
class BaseObject :
    public GLObject
{
public:
    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, LightObject* a_lightObject)
		: GLObject(a_vertecies, a_indices, a_camera)
    {
		m_lightObject = a_lightObject;
        Initialize();
    };

    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, Shader* a_shader, LightObject* a_lightObject)
        : GLObject(a_vertecies, a_indices, a_camera, a_shader)
    {
        m_lightObject = a_lightObject;
        Initialize();
    };

    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, LightObject* a_lightObject)
        : GLObject(a_vertecies, a_indices, a_camera, a_vertexPath, a_fragmentPath)
    {
        m_lightObject = a_lightObject;
        Initialize();
    };

    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath, LightObject* a_lightObject)
        : GLObject(a_vertecies, a_indices, a_camera, a_vertexPath, a_fragmentPath, a_texturePath)
    {
        m_lightObject = a_lightObject;
        Initialize();
    };

    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath, std::string a_specularTexPath, LightObject* a_lightObject)
        : GLObject(a_vertecies, a_indices, a_camera, a_vertexPath, a_fragmentPath, a_texturePath, a_specularTexPath)
    {
        m_lightObject = a_lightObject;
        Initialize();
    }

    const int Initialize(void) override;
    const int Update(void) override;
    const int Draw(void) override;
    const int Finalize(void) override;

protected:
	float m_shininess = 16.0f;
    LightObject* m_lightObject = nullptr;
};