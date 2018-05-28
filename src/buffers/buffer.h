#pragma once

#include <GL/glew.h>

namespace engine {

	class Buffer {

	private:
		GLuint m_buffer;
		GLuint m_length;
		GLuint m_dimensions;

	public:
		Buffer(GLfloat* data, GLsizei length, GLuint dimensions);

		void bind() const;
		void unbind() const;

		GLuint getID() const;
		GLuint getLength() const;
		GLuint getDimensions() const;
	};
}
