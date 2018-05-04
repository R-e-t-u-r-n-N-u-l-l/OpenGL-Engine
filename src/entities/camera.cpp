#include "camera.h"

using namespace engine;

Camera::Camera(Vector3f position, int width, int height) : m_position(position) {
	m_width = width;
	m_height = height;
}

void Camera::focusOnEntity(const Entity& entity, const Vector3f& offset, float distance, float rotation) {
	float dx = distance * cos(m_rotation.x);
	float dy = distance * sin(m_rotation.x);

	float a = entity.getRotation().y + rotation;

	float dx1 = dx * sin(a);
	float dz1 = dx * cos(a);

	m_position.y = entity.getPosition().y + dy + offset.y;
	m_position.x = entity.getPosition().x - dx1 + offset.x;
	m_position.z = entity.getPosition().z - dz1 + offset.z;

	m_rotation.y = M_PI - a;
}

void Camera::basicMovement(float speed) {
	float dx = 0.0f;
	float dz = 0.0f;
	float dy = 0.0f;

	if (Input::keyDown(GLFW_KEY_W)) {
		dx += speed * sin(m_rotation.y);
		dz -= speed * cos(m_rotation.y);
	} if (Input::keyDown(GLFW_KEY_S)) {
		dx -= speed * sin(m_rotation.y);
		dz += speed * cos(m_rotation.y);
	} if (Input::keyDown(GLFW_KEY_A)) {
		dx -= speed * sin(m_rotation.y + 1.552f);
		dz += speed * cos(m_rotation.y + 1.552f);
	} if (Input::keyDown(GLFW_KEY_D)) {
		dx += speed * sin(m_rotation.y + 1.552f);
		dz -= speed * cos(m_rotation.y + 1.552f);
	} if (Input::keyDown(GLFW_KEY_Q))
		dy += speed;
	if (Input::keyDown(GLFW_KEY_E))
		dy -= speed;

	move(dx, dy, dz);

	m_rotation.x = (Input::mouseY - m_height / 2) / m_height;
	m_rotation.y = (Input::mouseX - m_width / 2) / m_width;
}

void Camera::move(float x, float y, float z) {
	move(Vector3f(x, y, z));
}

void Camera::move(Vector3f translation) {
	m_position.add(translation);
}

void Camera::setPosition(Vector3f position) {
	m_position = position;
}

void Camera::setRotation(Vector3f rotation) {
	m_rotation = rotation;
}

void Camera::setPitch(float pitch) {
	m_rotation.x = pitch;
}

void Camera::setYaw(float yaw) {
	m_rotation.y = yaw;
}

void Camera::setRoll(float roll) {
	m_rotation.z = roll;
}

Vector3f Camera::getPosition() const {
	return m_position;
}

Vector3f Camera::getRotation() const {
	return m_rotation;
}

float Camera::getPitch() const {
	return m_rotation.x;
}

float Camera::getYaw() const {
	return m_rotation.y;
}

float Camera::getRoll() const {
	return m_rotation.z;
}
