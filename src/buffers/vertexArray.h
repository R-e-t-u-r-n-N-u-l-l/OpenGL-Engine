#pragma once

#include <vector>
#include <GL/glew.h>

#include "buffer.h"

namespace engine {

	class VertexArray {

	private:
		GLuint m_array;
		std::vector<GLuint> m_buffers;
		std::vector<GLuint> m_attributes;

	public:
		VertexArray();

		void append(GLuint attribute, GLuint buffer, GLuint dimensions);
		void append(GLuint attribute, Buffer* buffer);

		void updateBuffer(GLuint attribute, GLuint dimensions, GLuint length, GLfloat* data);
		
		void bind() const;
		void unbind() const;

		GLuint getID() const;
	};
}