#include "model.h"

using namespace engine;

Model::Model(GLfloat* vertices, GLuint* indices, GLsizei vertexLength, GLsizei indexLength, GLuint vertexDimensions, GLuint texture) : m_vertexLength(vertexLength), m_indexLength(indexLength), m_vao(VertexArray()), m_ibo(IndexBuffer(indices, indexLength)) {
	if (texture <= 0)
		setColor(1.0f, 1.0f, 1.0f, 1.0f);
	else
		m_texture = texture;

	Buffer vbo(vertices, vertexLength, vertexDimensions);
	m_vao.append(&vbo, 0);
}

void Model::appendBuffer(Buffer* buffer, GLuint index) {
	m_vao.append(buffer, index);
}

void Model::bind()  const {
	m_vao.bind();
	m_ibo.bind();
}

void Model::unbind() const {
	m_ibo.unbind();
	m_vao.unbind();
}

void Model::removeTexture() {
	m_texture = NULL;
}

void Model::setTexture(GLuint texture) {
	m_texture = texture;
}

void Model::setColor(float r, float g, float b, float a) {
	m_texture = File::colorToTexture(r, g, b, a);
}

void Model::setColor(Vector4f& color) {
	setColor(color.x, color.y, color.z, color.w);
}

GLuint Model::getTexture() const {
	return m_texture;
}

VertexArray Model::getVAO() const {
	return m_vao;
}

IndexBuffer Model::getIBO() const {
	return m_ibo;
}

GLuint Model::getVertexLength() const {
	return m_vertexLength;
}

GLuint Model::getIndexLength() const {
	return m_indexLength;
}
