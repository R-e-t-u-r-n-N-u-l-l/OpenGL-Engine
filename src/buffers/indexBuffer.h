#pragma once

#include <GL/glew.h>

namespace engine {

	class IndexBuffer {

	private:
		GLuint m_buffer;
		GLsizei m_length;

	public:
		IndexBuffer(GLuint* data, GLuint length);
		IndexBuffer(GLuint maxLength);

		void update(GLuint length, GLuint* data);

		void bind() const;
		void unbind() const;

		const GLsizei length() const;
	};
}
