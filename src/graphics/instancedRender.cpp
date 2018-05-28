#include "instancedRender.h"
#include <iostream>
using namespace engine;

InstancedRender::InstancedRender(VertexArray vao) : m_vao(vao) {}

void InstancedRender::bind() const {
	for(GLuint i : m_attributes)
		glEnableVertexAttribArray(i);
}

void InstancedRender::unbind() const {
	for (GLuint i : m_attributes)
		glDisableVertexAttribArray(i);
}

void InstancedRender::addInstancedAttribute(GLuint attribute, int dimensions, int maxInstances, int divisor, int stride, int offset) {
	m_attributes.push_back(attribute);
	GLuint vbo = createEmptyVBO(maxInstances, dimensions);
	m_vbos.push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(m_vao.getID());
	glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, dimensions, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)offset);
	glVertexAttribDivisor(attribute, divisor);
	glDisableVertexAttribArray(attribute);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void InstancedRender::updateAttribute(GLuint attribute, GLuint dimensions, GLuint instances, GLfloat* data) {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[attribute]);
	glBufferData(GL_ARRAY_BUFFER, dimensions * instances * sizeof(GLfloat), 0, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dimensions * instances * sizeof(GLfloat), data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int InstancedRender::getVBOLength() const {
	return m_vbos.size();
}

VertexArray InstancedRender::getVAO() const {
	return m_vao;
}

GLuint InstancedRender::createEmptyVBO(GLuint length, GLuint dimensions) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, dimensions * length * sizeof(GLfloat), 0, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}
