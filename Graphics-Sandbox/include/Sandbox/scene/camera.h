#pragma once

#include <glm/glm.hpp>

namespace sbx
{
	class Camera
	{
		friend class FloatReference;

	private:
		glm::vec3 m_position;
		float m_yaw;
		float m_pitch;
		glm::vec3 m_forward;
		glm::vec3 m_right;
		glm::vec3 m_up;

		float m_fov;
		float m_aspectRatio;

		void recalculateVectors();

	public:
		Camera(const glm::vec3& position, float yaw, float pitch);

		inline glm::vec3& position() { return m_position; }

		inline const glm::vec3& getPosition() const { return m_position; }
		inline const glm::vec3& getForward() const { return m_forward; }
		inline const glm::vec3& getRight() const { return m_right; }
		inline const glm::vec3& getUp() const { return m_up; }
		inline const float& getYaw() const { return m_yaw; }
		inline const float& getPitch() const { return m_pitch; }

		void setYaw(float yaw);
		void setPitch(float pitch);

		void setFov(float fov);
		void setAspectRatio(float aspectRatio);

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;
	};
}
