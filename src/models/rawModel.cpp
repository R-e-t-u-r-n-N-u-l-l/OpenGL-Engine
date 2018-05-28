#include "rawModel.h"
#include <iostream>

using namespace engine;

void RawModel::pushVertex(Vector3f vertex) {
	m_vertices.push_back(vertex);
}

void RawModel::popVertex() {
	m_vertices.pop_back();
}

void RawModel::setVertex(unsigned int index, Vector3f vertex) {
	if(index > 0 && index < m_vertices.size())
		m_vertices[index] = vertex;
}

void RawModel::removeVertex(unsigned int index) {
	if (index > 0 && index < m_vertices.size())
		m_vertices.erase(m_vertices.begin() + index);
}

void RawModel::pushNormal(Vector3f normal) {
	m_normals.push_back(normal);
}

void RawModel::popNormal() {
	m_normals.pop_back();
}

void RawModel::setNormal(unsigned int index, Vector3f normal) {
	if (index > 0 && index < m_normals.size())
		m_normals[index] = normal;
}

void RawModel::removeNormal(unsigned int index) {
	if (index > 0 && index < m_normals.size())
		m_normals.erase(m_normals.begin() + index);
}

void RawModel::pushTexCoord(Vector2f texCoord) {
	m_texCoords.push_back(texCoord);
}

void RawModel::popTexCoord() {
	m_texCoords.pop_back();
}

void RawModel::setTexCoord(unsigned int index, Vector2f texCoord) {
	if (index > 0 && index < m_texCoords.size())
		m_texCoords[index] = texCoord;
}

void RawModel::removeTexCoord(unsigned int index) {
	if (index > 0 && index < m_texCoords.size())
		m_texCoords.erase(m_texCoords.begin() + index);
}

void RawModel::pushIndex(int index) {
	m_indices.push_back(index);
}

void RawModel::popIndex() {
	m_indices.pop_back();
}

void RawModel::setIndex(unsigned int i, int index) {
	if (i > 0 && i < m_indices.size())
		m_indices[i] = index;
}

void RawModel::removeIndex(unsigned int i) {
	if (i > 0 && i < m_indices.size())
		m_indices.erase(m_indices.begin() + i);
}

Vector3f engine::RawModel::getVertex(int index) {
	if (index > 0 && index < m_vertices.size())
		return m_vertices[index];
	else
		return Vector3f();
}

Vector3f engine::RawModel::getNormal(int index) {
	if (index > 0 && index < m_normals.size())
		return m_normals[index];
	else
		return Vector3f();
}

Vector2f engine::RawModel::getTexCoord(int index) {
	if (index > 0 && index < m_texCoords.size())
		return m_texCoords[index];
	else
		return Vector2f();
}

GLuint engine::RawModel::getIndex(int index) {
	if (index > 0 && index < m_indices.size())
		return m_indices[index];
	else
		return 0;
}

Model RawModel::createModel(bool tc, bool n, GLuint texture) {
	Model model(vertices(), indices(), m_vertices.size(), m_indices.size(), 3, texture);

	if (texCoordLength() > 0 && tc) {
		Buffer texBuffer(texCoords(), m_texCoords.size(), 2);
		model.appendBuffer(&texBuffer, 1);
	}

	if (normalLength() > 0 && n) {
		Buffer normalBuffer(normals(), m_normals.size(), 3);
		model.appendBuffer(&normalBuffer, 2);
	}

	return model;
}

int RawModel::vertexLength() const {
	return m_vertices.size();
}

int RawModel::normalLength() const {
	return m_normals.size();
}

int RawModel::texCoordLength() const {
	return m_texCoords.size();
}

int RawModel::indexLength() const {
	return m_indices.size();
}

GLfloat* RawModel::vertices() const {
	GLfloat* vertices = new GLfloat[m_vertices.size() * 3];

	for (unsigned int i = 0; i < m_vertices.size(); i++) {
		vertices[i * 3 + 0] = m_vertices[i].x;
		vertices[i * 3 + 1] = m_vertices[i].y;
		vertices[i * 3 + 2] = m_vertices[i].z;
	}

	return vertices;
}

GLfloat* RawModel::normals() const {
	GLfloat* normals = new GLfloat[m_normals.size() * 3];

	for (unsigned int i = 0; i < m_normals.size(); i++) {
		normals[i * 3 + 0] = m_normals[i].x;
		normals[i * 3 + 1] = m_normals[i].y;
		normals[i * 3 + 2] = m_normals[i].z;
	}

	return normals;
}

GLfloat* RawModel::texCoords() const {
	GLfloat* texCoords = new GLfloat[m_texCoords.size() * 3];

	for (unsigned int i = 0; i < m_texCoords.size(); i++) {
		texCoords[i * 2 + 0] = m_texCoords[i].x;
		texCoords[i * 2 + 1] = m_texCoords[i].y;
	}

	return texCoords;
}

GLuint* RawModel::indices() const {
	GLuint* indices = new GLuint[m_indices.size()];

	for (unsigned int i = 0; i < m_indices.size(); i++)
		indices[i] = m_indices[i];

		return indices;
}
