#pragma once

#include <GL/glew.h>

namespace engine {

	class Buffer {

	private:
		GLuint m_buffer;
		GLuint m_length;
		GLuint m_typeCount;

	public:
		Buffer(GLfloat* data, GLsizei length, GLuint typeCount);

		void bind() const;
		void unbind() const;

		GLuint getLength() const;
		GLuint getTypeCount() const;
	};
}
