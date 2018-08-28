#include "buffer.h"

using namespace engine;

Buffer::Buffer(GLfloat* data, GLsizei length, GLuint dimensions) : m_length(length), m_dimensions(dimensions) {
	glGenBuffers(1, &m_buffer);
	bind();
	glBufferData(GL_ARRAY_BUFFER, dimensions * length * sizeof(data[0]), data, GL_STATIC_DRAW);
	unbind();
}

void Buffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void Buffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Buffer::getID() const {
	return m_buffer;
}

GLuint Buffer::getLength() const {
	return m_length;
}

GLuint Buffer::getDimensions() const {
	return m_dimensions;
}
