#include "terrain.h"

using namespace engine;

Terrain::Terrain(int x, int z, Model model, GLuint texture) : x(x), z(z), m_model(model) {
	m_model.setTexture(texture);
}

void Terrain::bind() const {
	m_model.bind();
}

void Terrain::unbind() const {
	m_model.unbind();
}

Matrix4f Terrain::createTransformationMatrix(int x, int z, int chunkSize) const {
	return Maths::createTransformationMatrix(Vector3f(x * chunkSize, 0.0f, z * chunkSize), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
}

Model Terrain::getModel() const {
	return m_model;
}

const int Terrain::getX() const {
	return x;
}

const int Terrain::getZ() const {
	return z;
}
