#pragma once

#include <glm/glm.hpp>

namespace Fireworks {

	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

	private:
		// Recalculate View and ProjectionView matrix whenever we change position or rotate.
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		// For GLM, we have to do Projection * View, not the other way around since matrices in OpenGL use column-major notation.
		glm::mat4 m_ProjectionViewMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}
