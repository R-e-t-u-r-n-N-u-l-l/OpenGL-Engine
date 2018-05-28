#include "vertexArray.h"
#include <iostream>
using namespace engine;

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_array);
}

void VertexArray::append(GLuint attribute, GLuint buffer, GLuint dimensions) {
	bind();
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	m_buffers.push_back(buffer);
	m_attributes.push_back(attribute);

	glVertexAttribPointer(attribute, dimensions, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unbind();
}

void VertexArray::append(GLuint attribute, Buffer* buffer) {
	bind();
	glBindBuffer(GL_ARRAY_BUFFER, buffer->getID());

	m_buffers.push_back(buffer->getID());
	m_attributes.push_back(attribute);

	glVertexAttribPointer(attribute, buffer->getDimensions(), GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unbind();
}

void VertexArray::updateBuffer(GLuint attribute, GLuint dimensions, GLuint length, GLfloat* data) {
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[std::find(m_attributes.begin(), m_attributes.end(), attribute) - m_attributes.begin()]);
	glBufferData(GL_ARRAY_BUFFER, dimensions * length * sizeof(GLfloat), 0, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dimensions * length * sizeof(GLfloat), data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::bind() const {
	glBindVertexArray(m_array);

	for (GLuint i : m_attributes)
		glEnableVertexAttribArray(i);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);

	for (GLuint i : m_attributes)
		glDisableVertexAttribArray(i);
}

GLuint VertexArray::getID() const {
	return m_array;
}
