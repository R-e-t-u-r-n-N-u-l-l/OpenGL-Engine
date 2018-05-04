#include "light.h"

using namespace engine;

Light::Light(Vector3f position, Vector4f color) :m_color(color) {
	m_position = position;
}

void Light::setColor(Vector4f color) {
	m_color = color;
}

Vector4f Light::getColor() const {
	return m_color;
}
