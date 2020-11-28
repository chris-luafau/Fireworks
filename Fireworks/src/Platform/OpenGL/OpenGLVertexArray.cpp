#include "fzpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Fireworks {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case Fireworks::ShaderDataType::Float:    return GL_FLOAT;
			case Fireworks::ShaderDataType::Float2:   return GL_FLOAT;
			case Fireworks::ShaderDataType::Float3:   return GL_FLOAT;
			case Fireworks::ShaderDataType::Float4:   return GL_FLOAT;
			case Fireworks::ShaderDataType::Mat3:     return GL_FLOAT;
			case Fireworks::ShaderDataType::Mat4:     return GL_FLOAT;
			case Fireworks::ShaderDataType::Int:      return GL_INT;
			case Fireworks::ShaderDataType::Int2:     return GL_INT;
			case Fireworks::ShaderDataType::Int3:     return GL_INT;
			case Fireworks::ShaderDataType::Int4:     return GL_INT;
			case Fireworks::ShaderDataType::Bool:     return GL_BOOL;
		}

		FZ_CORE_ASSERT(false, "Unknown ShaderDataType.");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		FZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout.")

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
