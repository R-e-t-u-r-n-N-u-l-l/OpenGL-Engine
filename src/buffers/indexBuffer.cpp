#include "indexBuffer.h"

using namespace engine;

IndexBuffer::IndexBuffer(GLuint* data, GLsizei length) : m_length(length) {
	glGenBuffers(1, &m_buffer);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(GLuint), data, GL_STATIC_DRAW);
	unbind();
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const GLsizei IndexBuffer::length() const {
	return m_length;
}
