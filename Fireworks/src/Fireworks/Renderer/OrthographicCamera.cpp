#include "fzpch.h"
#include "OrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Fireworks {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) 
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {

		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix() {
		// Start w/ the identity matrix --> translate it by m_Position and multiply by the rotation matrix.
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0,0,1));

		// Invert the transform matrix
		m_ViewMatrix = glm::inverse(transform);

		// Recalculate ViewProjection matrix
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}