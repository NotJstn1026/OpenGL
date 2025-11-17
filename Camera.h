#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera
{
public:
	inline Camera(int a_width, int hight, glm::vec3 a_postion){
		m_width = a_width;
		m_height = hight;
		m_position = a_postion;
	}

	inline ~Camera() {};

	/// <summary>
	/// Sends the camera matrix to the Vertex Shader.
	/// </summary>
	/// <param name="shader">Current shader program.</param>
	/// <param name="uniform">Wich uniform variable to send the matrix to.</param>
	void Matrix(Shader& shader, const char* uniform);

	/// <summary>
	/// Updates the camera matrix.
	/// </summary>
	void UpdateMatrix();

	/// <summary>
	/// Handles camera inputs.
	/// </summary>
	/// <param name="window">Window to get inputs from.</param>
	void Inputs(GLFWwindow* window);

	/// <summary>
	/// Gets the current position of the camera.
	/// </summary>
	/// <returns>A vec3 representing the camera position.</returns>
	glm::vec3 GetPosition() const { return m_position; }

	/// <summary>
	/// Gets the current view matrix of the camera.
	/// </summary>
	/// <returns>A mat4 representing the view matrix.</returns>
	glm::mat4 GetViewMatrix() const { return m_view; }

	/// <summary>
	/// Gets the current projection matrix of the camera.
	/// </summary>
	/// <returns>A mat4 representing the projection matrix.</returns>
	glm::mat4 GetProjectionMatrix() const { return m_projection; }

private:

	const float M_MAX_PITCH = 89.0f;
	const float M_MIN_PITCH = 85.0f;

	const float M_FOVDEG = 45.f;
	const float M_NEARPLANE = 0.1f;
	const float M_FARPLANE = 100.0f;

	glm::vec3 m_position = {};
	glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 m_view = glm::mat4(1.0f);
	glm::mat4 m_projection = glm::mat4(1.0f);
	glm::mat4 m_cameraMatrix = glm::mat4(1.0f);

	int m_width = {};
	int m_height = {};

	float m_speed = 0.01f;
	float m_sensitivity = 100.0f;

	bool m_firstClick = true;
};