#include "buffer.h"

using namespace engine;

Buffer::Buffer(GLfloat* data, GLsizei length, GLuint typeCount) : m_length(length), m_typeCount(typeCount) {
	glGenBuffers(1, &m_buffer);
	bind();
	glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), data, GL_STATIC_DRAW);
	unbind();
}

void Buffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void Buffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Buffer::getLength() const {
	return m_length;
}

GLuint Buffer::getTypeCount() const {
	return m_typeCount;
}
