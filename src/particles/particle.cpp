#include "particle.h"

using namespace engine;

Particle::Particle(Vector3f position, Vector3f rotation, Vector3f scale, Vector3f velocity, float gravity, float life) : 
	m_position(position), m_rotation(rotation), m_scale(scale), m_velocity(velocity), m_gravity(gravity), m_life(life), m_current(0) {}

bool Particle::update() {
	accelerate(0, m_gravity, 0);
	translate(m_velocity);
	return ++m_current < m_life;
}

void Particle::translate(const Vector3f& translation) {
	m_position.add(translation);
}

void Particle::rotate(const Vector3f& rotation) {
	m_rotation.add(rotation);
}

void Particle::scale(const Vector3f& scale) {
	m_scale.add(scale);
}

void Particle::accelerate(const Vector3f& velocity) {
	m_velocity.add(velocity);
}

void Particle::scale(float scale) {
	m_scale.add(scale, scale, scale);
}

void Particle::translate(float x, float y, float z) {
	m_position.add(x, y, z);
}

void Particle::rotate(float x, float y, float z) {
	m_rotation.add(x, y, z);
}

void Particle::scale(float x, float y, float z) {
	m_scale.add(x, y, z);
}

void Particle::accelerate(float x, float y, float z) {
	m_velocity.add(x, y, z);
}

Vector3f Particle::getPosition() const {
	return m_position;
}

Vector3f Particle::getRotation() const {
	return m_rotation;
}

Vector3f Particle::getScale() const {
	return m_scale;
}

Vector3f Particle::getVelocity() const {
	return m_velocity;
}

float Particle::getLife() const {
	return m_life;
}

float Particle::getGravity() const {
	return m_gravity;
}

Matrix4f engine::Particle::createTransformationMatrix(const Matrix4f& viewMatrix) const {
	Matrix4f matrix(1.0f);

	matrix.translate(m_position);
	matrix.elements[0 * 4 + 0] = viewMatrix.elements[0 * 4 + 0];
	matrix.elements[1 * 4 + 0] = viewMatrix.elements[0 * 4 + 1];
	matrix.elements[2 * 4 + 0] = viewMatrix.elements[0 * 4 + 2];
	matrix.elements[0 * 4 + 1] = viewMatrix.elements[1 * 4 + 0];
	matrix.elements[1 * 4 + 1] = viewMatrix.elements[1 * 4 + 1];
	matrix.elements[2 * 4 + 1] = viewMatrix.elements[1 * 4 + 2];
	matrix.elements[0 * 4 + 2] = viewMatrix.elements[2 * 4 + 0];
	matrix.elements[1 * 4 + 2] = viewMatrix.elements[2 * 4 + 1];
	matrix.elements[2 * 4 + 2] = viewMatrix.elements[2 * 4 + 2];
	
	matrix.rotate(m_rotation.x, Vector3f(1.0f, 0.0f, 0.0f));
	matrix.rotate(m_rotation.y, Vector3f(0.0f, 1.0f, 0.0f));
	matrix.rotate(m_rotation.z, Vector3f(0.0f, 0.0f, 1.0f));
	matrix.scale(m_scale);
	
	return matrix;
}

void Particle::setPosition(Vector3f position) {
	m_position = position;
}

void Particle::setRotation(Vector3f rotation) {
	m_rotation = rotation;
}

void Particle::setVelocity(Vector3f velocity) {
	m_velocity = velocity;
}

void Particle::setScale(Vector3f scale) {
	m_scale = scale;
}

void Particle::setPosition(float x, float y, float z) {
	m_position = Vector3f(x, y, z);
}

void Particle::setRotation(float x, float y, float z) {
	m_rotation = Vector3f(x, y, z);
}

void Particle::setVelocity(float x, float y, float z) {
	m_velocity = Vector3f(x, y, z);
}

void Particle::setScale(float x, float y, float z) {
	m_scale = Vector3f(x, y, z);
}

void Particle::setScale(float scale) {
	m_scale = Vector3f(scale, scale, scale);
}
