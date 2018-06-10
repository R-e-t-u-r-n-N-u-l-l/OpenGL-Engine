#include "guiObject.h"

using namespace engine;

GUIObject::GUIObject(GLuint texture, float x, float y, float width, float height, float rotation) : m_position(x, y), m_scale(width, height), m_rotation(rotation),
	m_transformation(Maths::createTransformationMatrix(Vector3f((x + width / 2.0f) * 2.0f - 1.0f, -(y + height / 2.0f) * 2.0f + 1.0f, 0.0f),
	Vector3f(0.0f, 0.0f, rotation), Vector3f(width, height, 1.0f))), m_texture(texture), m_visible(true) {}

GUIObject::GUIObject(GLuint texture, Vector2f position, Vector2f scale, float rotation) : GUIObject(texture, position.x, position.y, scale.x, scale.y, rotation) {}
GUIObject::GUIObject(float x, float y, float width, float height, float rotation) : GUIObject(0, x, y, width, height, rotation) {}
GUIObject::GUIObject(Vector2f position, Vector2f scale, float rotation) : GUIObject(0, position.x, position.y, scale.x, scale.y, rotation) {}

void GUIObject::render(int transformationLocation, Shader& shader) {
	shader.setUniformMatrix4f(transformationLocation, m_transformation);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	Render::renderNoBind(6);
}

void GUIObject::updateTransformationMatrix() {
	m_transformation = Maths::createTransformationMatrix(Vector3f((m_position.x + m_scale.x / 2.0f) * 2.0f - 1.0f, -(m_position.y + m_scale.y / 2.0f) * 2.0f + 1.0f, 0.0f),
		Vector3f(0.0f, 0.0f, m_rotation), Vector3f(m_scale.x, m_scale.y, 1.0f));
}

Vector2f GUIObject::getPosition() const {
	return m_position;
}

void GUIObject::setPosition(Vector2f position) {
	m_position = position;
	updateTransformationMatrix();
}

void GUIObject::setPosition(float x, float y) {
	setPosition(Vector2f(x, y));
}

Vector2f GUIObject::getScale() const {
	return m_scale;
}

void GUIObject::setScale(Vector2f scale) {
	m_scale = scale;
	updateTransformationMatrix();
}

void GUIObject::setScale(float x, float y) {
	setScale(Vector2f(x, y));
}

float GUIObject::getRotation() const {
	return m_rotation;
}

void GUIObject::setRotation(float rotation) {
	m_rotation = rotation;
	updateTransformationMatrix();
}

bool GUIObject::isVisible() const {
	return m_visible;
}

void GUIObject::setVisible(bool visible) {
	m_visible = visible;
}
