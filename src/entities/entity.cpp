#include "entity.h"

using namespace engine;

Entity::Entity() : m_model(Model(0, 0, 0, 0)), m_empty(true) {
	m_scale = Vector3f(1.0f, 1.0f, 1.0f);
}

Entity::Entity(Model model) : m_model(model), m_empty(false) {
	m_scale = Vector3f(1.0f, 1.0f, 1.0f);
}

Entity::Entity(Vector3f position, Vector3f rotation, Vector3f scale) : m_position(position), m_rotation(rotation), m_scale(scale), m_model(Model(0, 0, 0, 0, 0, 0)), m_empty(true) {}
Entity::Entity(Model model, Vector3f position, Vector3f rotation, Vector3f scale) : m_model(model), m_position(position), m_rotation(rotation), m_scale(scale), m_empty(false) {}


void Entity::translate(Vector3f translation) {
	m_position.add(translation);
}

void Entity::rotate(Vector3f rotation) {
	m_rotation.add(rotation);
}

void Entity::scale(Vector3f scale) {
	m_scale.add(scale);
}

void Entity::scale(float scale) {
	m_scale.add(scale, scale, scale);
}

void Entity::translate(float x, float y, float z) {
	m_position.add(x, y, z);
}

void Entity::rotate(float x, float y, float z) {
	m_rotation.add(x, y, z);
}

void Entity::scale(float x, float y, float z) {
	m_scale.add(x, y, z);
}

void Entity::bind() const {
	m_model.bind();
}

void Entity::unbind() const {
	m_model.unbind();
}

Model Entity::getModel() const {
	return m_model;
}

Vector3f Entity::getPosition() const {
	return m_position;
}

Vector3f Entity::getRotation() const {
	return m_rotation;
}

Vector3f Entity::getScale() const {
	return m_scale;
}

AABB Entity::getBoundingBox() const {
	return m_boundingBox;
}

bool Entity::isEmpty() const {
	return m_empty;
}

bool Entity::collsionWithEntity(const Entity& entity) {
	return m_boundingBox.AABBCollision(entity.getBoundingBox());
}

Matrix4f Entity::createTransformationMatrix() const {
	return Maths::createTransformationMatrix(m_position, m_rotation, m_scale);
}

void Entity::setModel(Model model) {
	m_model = model;
	if (!m_empty)
		m_empty = false;
}

void Entity::setPosition(Vector3f position) {
	m_position = position;
}

void Entity::setRotation(Vector3f rotation) {
	m_rotation = rotation;
}

void Entity::setScale(Vector3f scale) {
	m_scale = scale;
}

void Entity::setScale(float scale) {
	m_scale = Vector3f(scale, scale, scale);
}

void Entity::setBoundingBox(AABB box) {
	m_boundingBox = box;
}