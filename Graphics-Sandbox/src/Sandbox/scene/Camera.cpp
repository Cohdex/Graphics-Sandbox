#include "pch.h"

#include <Sandbox/scene/camera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace sbx
{
	Camera::Camera(const glm::vec3& position, float yaw, float pitch)
		: m_position(position), m_yaw(yaw), m_pitch(pitch)
	{
		recalculateVectors();
	}

	void Camera::setYaw(float yaw)
	{
		m_yaw = yaw;
		recalculateVectors();
	}

	void Camera::setPitch(float pitch)
	{
		m_pitch = pitch;
		recalculateVectors();
	}

	void Camera::setFov(float fov)
	{
		m_fov = fov;
	}

	void Camera::setAspectRatio(float aspectRatio)
	{
		m_aspectRatio = aspectRatio;
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		glm::mat4 viewMatrix;
		viewMatrix[0] = glm::vec4(m_right, 0);
		viewMatrix[1] = glm::vec4(m_up, 0);
		viewMatrix[2] = glm::vec4(-m_forward, 0);
		viewMatrix = glm::transpose(viewMatrix);
		viewMatrix = glm::translate(viewMatrix, m_position);

		return viewMatrix;
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		return glm::perspective(m_fov, m_aspectRatio, 0.1f, 100.0f);
	}

	void Camera::recalculateVectors()
	{
		float radYaw = glm::radians(m_yaw);
		float radPitch = glm::radians(m_pitch);

		float cosPitch = glm::cos(radPitch);
		m_forward = glm::vec3(glm::sin(radYaw) * cosPitch, glm::sin(radPitch), -glm::cos(radYaw) * cosPitch);
		m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0, 1, 0)));
		m_up = glm::cross(m_right, m_forward);
	}
}
