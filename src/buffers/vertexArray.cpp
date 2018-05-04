#include "vertexArray.h"
#include <iostream>
using namespace engine;

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_array);
}

void VertexArray::append(Buffer* buffer, GLuint index) {
	bind();
	buffer->bind();

	m_buffers.push_back(buffer);
	m_indices.push_back(index);

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getTypeCount(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer->unbind();
	unbind();
}

void VertexArray::bind() const {
	glBindVertexArray(m_array);

	for (GLuint i : m_indices)
		glEnableVertexAttribArray(i);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);

	for (GLuint i : m_indices)
		glDisableVertexAttribArray(i);
}

GLuint VertexArray::getID() const {
	return m_array;
}
