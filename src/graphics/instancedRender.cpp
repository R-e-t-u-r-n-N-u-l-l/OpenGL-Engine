#include "instancedRender.h"
#include <iostream>
using namespace engine;

InstancedRender::InstancedRender(GLuint vao) : m_vao(vao) {}

void InstancedRender::updateVBO(int index, int dataSize, int instances, GLfloat* data) {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[index]);
	glBufferData(GL_ARRAY_BUFFER, dataSize * instances * sizeof(GLfloat), 0, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize * instances * sizeof(GLfloat), data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstancedRender::bind() const {
	for(GLuint i : m_attributes)
		glEnableVertexAttribArray(i);
}

void InstancedRender::unbind() const {
	for (GLuint i : m_attributes)
		glDisableVertexAttribArray(i);
}

void InstancedRender::addInstancedAttribute(GLuint attribute, int dataSize, int maxInstances, int stride, int offset) {
	m_attributes.push_back(attribute);
	GLuint vbo = createEmptyVBO(dataSize * maxInstances);
	m_vbos.push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, dataSize, GL_FLOAT, GL_FALSE, dataSize * sizeof(GLfloat), (void*)offset);
	glVertexAttribDivisor(attribute, 1);
	glDisableVertexAttribArray(attribute);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint InstancedRender::createEmptyVBO(int length) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), 0, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}

int InstancedRender::getVBOLength() const {
	return m_vbos.size();
}
