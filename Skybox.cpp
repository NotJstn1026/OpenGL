#include "Skybox.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include <stb/std_image.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Inspired by https://learnopengl.com/Advanced-OpenGL/Cubemaps
Skybox::Skybox(Camera* a_camera, std::vector<std::string> a_facePaths)
    : GLObject(&m_skyboxVertices, &m_skyboxIndices, a_camera),
    m_facePaths(a_facePaths),
    m_cubemapTextureID(0)
{
    if (a_facePaths.size() != 6)
    {
        throw std::runtime_error("SkyboxObject requires exactly 6 texture paths.");
    }
}

const int Skybox::Initialize(void)
{
    // Create Shader
    if (m_shaderProgram == nullptr)
    {
        m_shaderProgram = new Shader("ShaderCode/skybox.vert", "ShaderCode/skybox.frag");
    }

    // Create VAO, VBO, EBO
    m_VAO = new VAO();
    m_VAO->Bind();

    m_VBO = new VBO(m_vertecies->data(), m_vertecies->size() * sizeof(Vertex));
    m_VBO->Bind();

    m_EBO = new EBO(m_indices->data(), m_indices->size() * sizeof(GLint));
    m_EBO->Bind(); // EBO binding is stored in the VAO


    m_VAO->LinkAttribute(*m_VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);


    // Unbind
    m_VAO->Unbind();
    m_VBO->Unbind();
    m_EBO->Unbind();

    // Load the cubemap texture
    if (LoadCubemap() != 0)
    {
        return -1; // Error loading texture
    }

    // Set the sampler uniform to Texture Unit 0
    m_shaderProgram->Activate();
    glUniform1i(glGetUniformLocation(m_shaderProgram->GetID(), "skybox"), 0);

    return 0;
}

const int Skybox::Update(void)
{
    return 0;
}

const int Skybox::LoadCubemap()
{
	// Disable vertical flip for cubemap loading
    stbi_set_flip_vertically_on_load(false);

    glGenTextures(1, &m_cubemapTextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTextureID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(m_facePaths[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            // Determine the format based on the channels
            GLenum format = GL_RGBA;

            // Corresponds to Right, Left, Top, Bottom, Front, Back
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load cubemap texture: " << m_facePaths[i] << std::endl;
            stbi_set_flip_vertically_on_load(true); // Reset it for other textures
            return -1; 
        }
    }

    // Reset the STB flip status to the default for your other textures
    stbi_set_flip_vertically_on_load(true);
    return 0;
}


const int Skybox::Draw(void)
{
    // Change the depth function so the skybox is drawn
    glDepthFunc(GL_LEQUAL);

    m_shaderProgram->Activate();

    // Remove the translation from the View matrix so the skybox follows the camera
    glm::mat4 view = glm::mat4(glm::mat3(m_camera->GetViewMatrix()));
    glm::mat4 projection = m_camera->GetProjectionMatrix();

    // Send the matrices to the skybox shader
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the skybox
    m_VAO->Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTextureID);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices->size()), GL_UNSIGNED_INT, 0);

    m_VAO->Unbind();

    // Reset the depth function to the default
    glDepthFunc(GL_LESS);

    return 0;
}

const int Skybox::Finalize(void)
{
    // Delete the cubemap texture manually
    glDeleteTextures(1, &m_cubemapTextureID);
    m_cubemapTextureID = 0;

    return 0;
}