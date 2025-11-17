#pragma once
#include "GLObject.h"
#include "LightType.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
#include <glm/glm.hpp>
// This script was inspired by https://learnopengl.com/Lighting/Light-casters
class LightObject :
    public GLObject
{
public:
    LightObject(std::vector<Vertex>* a_vertices, std::vector<GLint>* a_indices, Camera* a_camera, Shader* a_shader, LightType a_ligthType, const glm::vec3& a_position, 
        const glm::vec3& a_direction = glm::vec3(0.0f, -1.0f, 0.0f), float a_innerCutoffDeg = 12.5f, float a_outerCutoffDeg = 17.5f) : GLObject(a_vertices, a_indices, a_camera, a_shader),
        m_type(a_ligthType), m_position(a_position), m_direction(glm::normalize(a_direction)), m_innerCutoffDeg(a_innerCutoffDeg), m_outerCutoffDeg(a_outerCutoffDeg)
    {
    }

    const int Initialize(void) override;
    const int Update(void) override;
    const int Draw(void) override;
    const int Finalize(void) override;

    // Configure light parameters; call before Draw
    void SetColor(const glm::vec3& a_color) { m_color = a_color; }
    void SetPosition(const glm::vec3& a_postion) { m_position = a_postion; }
    void SetDirection(const glm::vec3& a_direction) { m_direction = glm::normalize(a_direction); }
    void SetType(LightType a_lightType) { m_type = a_lightType; }
    void SetAttenuation(float a_attenuationA, float a_attenuationB) { m_attA = a_attenuationA; m_attB = a_attenuationB; }
    void SetCutoffs(float a_innerDeg, float a_outerDeg) { m_innerCutoffDeg = a_innerDeg; m_outerCutoffDeg = a_outerDeg; }

	glm::vec3 GetPosition() const { return m_position; }
    glm::vec3 GetColor() const { return m_color; }

    // Sends light uniforms into a target lighting shader used by scene objects (not the light-cube shader)
    void UploadToLightingShader(Shader& a_lightShader) const;


protected:
    // Visual drawing resources
    VAO* m_lightVAO = nullptr;
    VBO* m_lightVBO = nullptr;
    EBO* m_lightEBO = nullptr;

    // Light parameters
    LightType m_type = LightType::LT_Point;
    glm::vec3 m_color = {};
    glm::vec3 m_position = glm::vec3(1.5f, 0.5f, 0.0f);
    glm::vec3 m_direction = glm::vec3(0.0f, -1.0f, 0.0f);

    // Attenuation for point/spot
    float m_attA = 3.0f;  // quadratic factor
    float m_attB = 0.7f;  // linear factor

    // Spotlight cutoffs in degrees
    float m_innerCutoffDeg = 12.5f;
    float m_outerCutoffDeg = 17.5f;
};

