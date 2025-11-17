#include "BaseObject.h"
#include "LightObject.h"
#include <stb/std_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const int BaseObject::Initialize(void)
{
	if (m_shaderProgram == nullptr)
	{
		// Create a new shader program object
		m_shaderProgram = new Shader("ShaderCode/default.vert", "ShaderCode/default.frag");
	}

	// Create a new Vertex Array Object (VAO)
	m_VAO = new VAO();
	// Bind the VAO to make it active
	m_VAO->Bind();

	// Create a new Vertex Buffer Object (VBO) with our vertex data
	m_VBO = new VBO(m_vertecies->data(), m_vertecies->size() * sizeof(Vertex));
	// Bind the VBO to the array buffer target
	m_VBO->Bind();

	// Create a new Element Buffer Object (EBO) with our index data
	m_EBO = new EBO(m_indices->data(), m_indices->size() * sizeof(GLint));

	// Configure vertex attribute layout 0 (position)
	m_VAO->LinkAttribute(*m_VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	// Configure vertex attribute layout 1 (color)
	m_VAO->LinkAttribute(*m_VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	// Configure vertex attribute layout 2 (texture coordinates)
	m_VAO->LinkAttribute(*m_VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, UV));
	// Configure vertex attribute layout 3 (normal vector)
	m_VAO->LinkAttribute(*m_VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normals));

	m_VAO->Unbind();
	m_VBO->Unbind();
	m_EBO->Unbind();

	glm::vec4 lightColor = glm::vec4(m_lightObject->GetColor(),1.0f);
	glm::vec3 lightPos = m_lightObject->GetPosition();
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	m_shaderProgram->Activate();
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->GetID(), "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(m_shaderProgram->GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(m_shaderProgram->GetID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(m_shaderProgram->GetID(), "shininess"), m_shininess);


	// Define the path to the texture file
	std::string textureDir = "Textures/";
	std::string texturePath = textureDir;
	if (m_texturePath == nullptr)
	{
		texturePath = textureDir + "DefaultTexure.png";
	}
	else
	{
		texturePath = textureDir + *m_texturePath;
	}

	// Create a new texture object from the file
	m_texture = new Texture((texturePath).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	// Tell the shader's "tex0" uniform to use texture unit 0
	m_texture->texUnit(*m_shaderProgram, "tex0", 0);
	m_texture->Bind();

	if (m_specularMapPath != nullptr)
	{
		std::string specularMapPath = textureDir + *m_specularMapPath;
		m_specularMapTexture = new Texture((specularMapPath).c_str(), GL_TEXTURE_2D, GL_TEXTURE1, GL_RED, GL_UNSIGNED_BYTE);
		m_specularMapTexture->texUnit(*m_shaderProgram, "tex1", 1);
		m_specularMapTexture->Bind();
	}

	return 0;
}

const int BaseObject::Update(void)
{
	return 0;
}

const int BaseObject::Draw(void)
{
	m_shaderProgram->Activate();

	glm::mat4 model(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram->GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

	// Camera uniforms
	glm::vec3 camPos = m_camera->GetPosition();
	glUniform3f(glGetUniformLocation(m_shaderProgram->GetID(), "camPos"), camPos.x, camPos.y, camPos.z);
	m_camera->Matrix(*m_shaderProgram, "cameraMatrix");

	if (m_texture) m_texture->Bind();       

	if (m_specularMapTexture) m_specularMapTexture->Bind();

	m_VAO->Bind();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices->size()), GL_UNSIGNED_INT, 0);
	return 0;
}


const int BaseObject::Finalize(void)
{
	if (m_texture)
	{
		m_texture->Delete();
	}
	if (m_EBO)
	{
		m_EBO->Delete();
	}
	if (m_VBO)
	{
		m_VBO->Delete();
	}
	if (m_VAO)
	{
		m_VAO->Delete();
	}
	if (m_shaderProgram)
	{
		m_shaderProgram->Delete();
	}

	delete m_texture;
	delete m_EBO;
	delete m_VBO;
	delete m_VAO;
	delete m_shaderProgram;

	m_texture = nullptr;
	m_EBO = nullptr;
	m_VBO = nullptr;
	m_VAO = nullptr;
	m_shaderProgram = nullptr;

	m_camera = nullptr;
	m_vertecies = nullptr;
	m_indices = nullptr;

	return 0;
}