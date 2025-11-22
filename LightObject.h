/*****************************************************************************
* Project: OpenGL
* File : LightObject.h
* Date : 18.11.2025
* Author : Justin Martin (JM)
*
* The LightObject class represents a light source in the 3D scene.
* It inherits from GLObject to render a visual representation (e.g., a cube)
* of the light source itself. Its primary function, however, is to manage
* light properties (color, position, direction, type) and upload these
* parameters to the shaders of other objects to enable dynamic lighting calculations.
* It supports various light types such as Point, Directional, and Spot lights.
******************************************************************************/

#pragma once
#include "GLObject.h"
#include "LightType.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
#include <glm/glm.hpp>

// This script was inspired by https://learnopengl.com/Lighting/Light-casters

/// <summary>
/// Represents a light source in the scene that can also be rendered visually.
/// Manages lighting parameters and uniforms for shaders.
/// </summary>
class LightObject :
	public GLObject
{
public:
	/// <summary>
	/// Constructor for the LightObject.
	/// </summary>
	/// <param name="a_vertices">Pointer to the vertex data for the light's visual mesh.</param>
	/// <param name="a_indices">Pointer to the index data for the light's visual mesh.</param>
	/// <param name="a_camera">Pointer to the scene camera.</param>
	/// <param name="a_shader">Pointer to the shader used to render the light object itself.</param>
	/// <param name="a_ligthType">The type of light (Point, Spot, Directional).</param>
	/// <param name="a_position">Initial position of the light.</param>
	/// <param name="a_direction">Initial direction of the light (default is down).</param>
	/// <param name="a_innerCutoffDeg">Inner cutoff angle for spotlights in degrees (default 12.5).</param>
	/// <param name="a_outerCutoffDeg">Outer cutoff angle for spotlights in degrees (default 17.5).</param>
	LightObject(std::vector<Vertex>* a_vertices, std::vector<GLint>* a_indices, Camera* a_camera, Shader* a_shader, LightType a_ligthType, const glm::vec3& a_position,
		const glm::vec3& a_direction = glm::vec3(0.0f, -1.0f, 0.0f), float a_innerCutoffDeg = 12.5f, float a_outerCutoffDeg = 17.5f) : GLObject(a_vertices, a_indices, a_camera, a_shader),
		m_type(a_ligthType), m_position(a_position), m_direction(glm::normalize(a_direction)), m_innerCutoffDeg(a_innerCutoffDeg), m_outerCutoffDeg(a_outerCutoffDeg)
	{
	}

	/// <summary>
	/// Initializes the light's visual components (VAO, VBO, EBO).
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Initialize(void) override;

	/// <summary>
	/// Updates the light object logic.
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Update(void) override;

	/// <summary>
	/// Renders the visual representation of the light source (e.g., the glowing cube).
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Draw(void) override;

	/// <summary>
	/// Cleans up OpenGL resources associated with the light object.
	/// </summary>
	/// <returns>0 on success.</returns>
	const int Finalize(void) override;

	// Configure light parameters; call before Draw

	/// <summary>
	/// Sets the color of the light.
	/// </summary>
	/// <param name="a_color">RGB color vector.</param>
	void SetColor(const glm::vec3& a_color) { m_color = a_color; }

	/// <summary>
	/// Sets the world position of the light.
	/// </summary>
	/// <param name="a_postion">XYZ position vector.</param>
	void SetPosition(const glm::vec3& a_postion) { m_position = a_postion; }

	/// <summary>
	/// Sets the direction the light is pointing (relevant for Spot and Directional lights).
	/// </summary>
	/// <param name="a_direction">Direction vector (will be normalized).</param>
	void SetDirection(const glm::vec3& a_direction) { m_direction = glm::normalize(a_direction); }

	/// <summary>
	/// Sets the type of the light.
	/// </summary>
	/// <param name="a_lightType">Enum value for light type (e.g., LT_Point).</param>
	void SetType(LightType a_lightType) { m_type = a_lightType; }

	/// <summary>
	/// Configures the attenuation factors for light falloff.
	/// </summary>
	/// <param name="a_attenuationA">Quadratic attenuation factor.</param>
	/// <param name="a_attenuationB">Linear attenuation factor.</param>
	void SetAttenuation(float a_attenuationA, float a_attenuationB) { m_attA = a_attenuationA; m_attB = a_attenuationB; }

	/// <summary>
	/// Configures the cutoff angles for spotlights to create soft edges.
	/// </summary>
	/// <param name="a_innerDeg">Inner angle in degrees (full brightness).</param>
	/// <param name="a_outerDeg">Outer angle in degrees (fades to zero).</param>
	void SetCutoffs(float a_innerDeg, float a_outerDeg) { m_innerCutoffDeg = a_innerDeg; m_outerCutoffDeg = a_outerDeg; }

	/// <summary>
	/// Gets the current world position of the light.
	/// </summary>
	/// <returns>Position vector.</returns>
	glm::vec3 GetPosition() const { return m_position; }

	/// <summary>
	/// Gets the current color of the light.
	/// </summary>
	/// <returns>Color vector.</returns>
	glm::vec3 GetColor() const { return m_color; }

	/// <summary>
	/// Sends light uniforms (color, pos, type, etc.) into a target lighting shader used by scene objects.
	/// </summary>
	/// <param name="a_lightShader">Reference to the shader program of the scene objects.</param>
	void UploadToLightingShader(Shader& a_lightShader) const;


protected:
	/// <summary>
	/// VAO for the visual representation of the light.
	/// </summary>
	VAO* m_lightVAO = nullptr;

	/// <summary>
	/// VBO for the visual representation of the light.
	/// </summary>
	VBO* m_lightVBO = nullptr;

	/// <summary>
	/// EBO for the visual representation of the light.
	/// </summary>
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