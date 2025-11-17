#include "LightObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int LightObject::Initialize(void)
{
    // Create VAO/VBO/EBO for the light's visual geometry (small cube)
    m_lightVAO = new VAO();
    m_lightVAO->Bind();

    m_lightVBO = new VBO(m_vertecies->data(), static_cast<GLsizeiptr>(m_vertecies->size() * sizeof(Vertex)));
    m_lightEBO = new EBO(m_indices->data(), static_cast<GLsizeiptr>(m_indices->size() * sizeof(GLint)));

    // Only position attribute is required by the light draw shader
    m_lightVAO->LinkAttribute(*m_lightVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Position));

    m_lightVAO->Unbind();
    m_lightVBO->Unbind();
    m_lightEBO->Unbind();

    return 0;
}

const int LightObject::Update(void)
{
    // Nothing dynamic by default; user can move light externally via setters
    return 0;
}

const int LightObject::Draw(void)
{
    // Draw the visual representation of the light (the small cube)
    if (!m_shaderProgram) return -1;

    m_shaderProgram->Activate();

    // Build model matrix to place the cube at light position
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_position);

    // Upload model and color to the light draw shader
    GLint locModel = glGetUniformLocation(m_shaderProgram->GetID(), "model");
    if (locModel >= 0) glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));

    GLint locColor = glGetUniformLocation(m_shaderProgram->GetID(), "lightColor");
    if (locColor >= 0) glUniform4f(locColor, m_color.r, m_color.g, m_color.b, 1.0f);

    // Camera matrix
    if (m_camera)
        m_camera->Matrix(*m_shaderProgram, "cameraMatrix");

    // Bind and draw cube
    m_lightVAO->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices->size()), GL_UNSIGNED_INT, 0);

    return 0;
}

const int LightObject::Finalize(void)
{
    if (m_lightEBO) m_lightEBO->Delete();
    if (m_lightVBO) m_lightVBO->Delete();
    if (m_lightVAO) m_lightVAO->Delete();

    delete m_lightEBO; m_lightEBO = nullptr;
    delete m_lightVBO; m_lightVBO = nullptr;
    delete m_lightVAO; m_lightVAO = nullptr;
    return 0;
}

void LightObject::UploadToLightingShader(Shader& lightingShader) const
{
    // Activate the shader that does the scene lighting (object shader)
    lightingShader.Activate();

    // Convert enum to int for uniform
    int typeInt = static_cast<int>(m_type);
    GLint uType = glGetUniformLocation(lightingShader.GetID(), "uLight.type");
    if (uType >= 0) glUniform1i(uType, typeInt);

    // Common parameters
    GLint uColor = glGetUniformLocation(lightingShader.GetID(), "uLight.color");
    if (uColor >= 0) glUniform3f(uColor, m_color.r, m_color.g, m_color.b);

    // Position and direction
    GLint uPos = glGetUniformLocation(lightingShader.GetID(), "uLight.position");
    if (uPos >= 0) glUniform3f(uPos, m_position.x, m_position.y, m_position.z);

    GLint uDir = glGetUniformLocation(lightingShader.GetID(), "uLight.direction");
    if (uDir >= 0) glUniform3f(uDir, m_direction.x, m_direction.y, m_direction.z);

    // Attenuation (used by point and spot)
    GLint uAttA = glGetUniformLocation(lightingShader.GetID(), "uLight.attA");
    if (uAttA >= 0) glUniform1f(uAttA, m_attA);
    GLint uAttB = glGetUniformLocation(lightingShader.GetID(), "uLight.attB");
    if (uAttB >= 0) glUniform1f(uAttB, m_attB);

    // Spot cutoffs (in radians cosine)
    float innerCos = cosf(glm::radians(m_innerCutoffDeg));
    float outerCos = cosf(glm::radians(m_outerCutoffDeg));
    GLint uInner = glGetUniformLocation(lightingShader.GetID(), "uLight.innerCutoff");
    GLint uOuter = glGetUniformLocation(lightingShader.GetID(), "uLight.outerCutoff");
    if (uInner >= 0) glUniform1f(uInner, innerCos);
    if (uOuter >= 0) glUniform1f(uOuter, outerCos);
}