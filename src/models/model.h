#pragma once

#include "../buffers/buffers.h"
#include "../maths/vector/vector4f.h"
#include "../utilities/fileio.h"

namespace engine {

	class Model {

	private:
		VertexArray m_vao;
		IndexBuffer m_ibo;
		GLuint m_texture;
		GLuint m_vertexLength, m_indexLength;

	public:
		Model(GLfloat* vertices, GLuint* indices, GLsizei vertexLength, GLsizei indexLength, GLuint vertexDimensions = 3, GLuint texture = 0);

		void appendBuffer(Buffer* buffer, GLuint index);

		void bind() const;
		void unbind() const;

		void removeTexture();
		void setTexture(GLuint texture);

		void setColor(float r, float g, float b, float a);
		void setColor(Vector4f& color);

		GLuint getTexture() const;

		VertexArray getVAO() const;
		IndexBuffer getIBO() const;

		GLuint getVertexLength() const;
		GLuint getIndexLength() const;
	};
}
