#include "indexBuffer.h"

using namespace engine;

IndexBuffer::IndexBuffer(GLuint* data, GLuint length) : m_length(length) {
	glGenBuffers(1, &m_buffer);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(GLuint), data, GL_STATIC_DRAW);
	unbind();
}

IndexBuffer::IndexBuffer(GLuint maxLength) {
	glGenBuffers(1, &m_buffer);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxLength * sizeof(GLuint), 0, GL_STREAM_DRAW);
	unbind();
}

void IndexBuffer::update(GLuint length, GLuint* data) {
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(GLuint), 0, GL_STREAM_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, length * sizeof(GLuint), data);
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
