#pragma once

#include <vector>
#include <GL/glew.h>

#include "buffer.h"

namespace engine {

	class VertexArray {

	private:
		GLuint m_array;
		std::vector<Buffer*> m_buffers;
		std::vector<GLuint> m_indices;

	public:
		VertexArray();

		void append(Buffer* buffer, GLuint index);
		
		void bind() const;
		void unbind() const;

		GLuint getID() const;
	};
}