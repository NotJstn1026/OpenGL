#pragma once
#include "GLObject.h"
class BaseObject :
    public GLObject
{
public:
    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera)
        : GLObject(a_vertecies, a_indices, a_camera)
    {
        Initialize();
    };

    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, Shader* a_shader)
        : GLObject(a_vertecies, a_indices, a_camera, a_shader)
    {
        Initialize();
    };

    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath)
        : GLObject(a_vertecies, a_indices, a_camera, a_vertexPath, a_fragmentPath)
    {
        Initialize();
    };

    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath)
        : GLObject(a_vertecies, a_indices, a_camera, a_vertexPath, a_fragmentPath, a_texturePath)
    {
        Initialize();
    };

    BaseObject(std::vector<Vertex>* a_vertecies, std::vector<GLint>* a_indices, Camera* a_camera, std::string a_vertexPath, std::string a_fragmentPath, std::string a_texturePath, std::string a_specularTexPath)
        : GLObject(a_vertecies, a_indices, a_camera, a_vertexPath, a_fragmentPath, a_texturePath, a_specularTexPath)
    {
        Initialize();
    }

    const int Initialize(void) override;
    const int Update(void) override;
    const int Draw(void) override;
    const int Finalize(void) override;

protected:
	float m_shininess = 16.0f;
};