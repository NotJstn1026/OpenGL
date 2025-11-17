#include "Camera.h"

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), uniform), 1, GL_FALSE, glm::value_ptr(m_cameraMatrix));
}

void Camera::UpdateMatrix()
{

	// Makes camera look in the right direction from the right position
	m_view = glm::lookAt(m_position, m_position + m_orientation, m_up);
	// Adds perspective to the scene
	m_projection = glm::perspective(glm::radians(M_FOVDEG), (float)m_width / m_height, M_NEARPLANE, M_FARPLANE);

	// Sets new camera matrix
	m_cameraMatrix = m_projection * m_view;
}

void Camera::Inputs(GLFWwindow* window)
{
	float velocity = m_speed;

	// Calculate the "right" vector only once
	const glm::vec3 right = glm::normalize(glm::cross(m_orientation, m_up));

	// Start with an empty movement vector
	glm::vec3 moveDirection(0.0f);

	// Add directions based on key presses
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		moveDirection += m_orientation; // Forward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		moveDirection -= m_orientation; // Backward
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		moveDirection -= right; // Left
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		moveDirection += right; // Right
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		moveDirection += m_up; // Up
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		moveDirection -= m_up; // Down

	// Apply movement if any key was pressed.
	if (glm::length(moveDirection) > 0.0f)
	{
		m_position += glm::normalize(moveDirection) * velocity;
	}

	// Mouse input
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides the mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera jump on first click
		if (m_firstClick)
		{
			glfwSetCursorPos(window, (m_width / 2.0), (m_height / 2.0));
			m_firstClick = false;
		}

		// Get the current mouse coordinates
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Calculate the rotation offsets
		float rotX = m_sensitivity * (float)(mouseY - (m_height * .5)) / m_height;
		float rotY = m_sensitivity * (float)(mouseX - (m_width * .5)) / m_width;

		// Sets the new orientation
		glm::vec3 newOrientation = glm::rotate(m_orientation, glm::radians(-rotX), right);

		// Only set the new orientation if it doesn't exceed the pitch limits
		// Angle calculate the angle between two vectors
		if (abs(glm::angle(newOrientation, m_up) - glm::radians(M_MAX_PITCH)) <= glm::radians(M_MIN_PITCH))
		{
			m_orientation = newOrientation;
		}

		// Rotate the orientation for the camera yaw
		m_orientation = glm::rotate(m_orientation, glm::radians(-rotY), m_up);

		// Reset the mouse cursor to the middle so it doesn't hit the edge
		glfwSetCursorPos(window, (m_width * .5), (m_height * .5));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Shows the mouse cursor again
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Resets m_firstClick so the next click is centered again
		m_firstClick = true;
	}
}
