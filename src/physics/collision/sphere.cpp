#include "sphere.h"

using namespace engine;

Sphere::Sphere() {
	m_radius = 1;
}

Sphere::Sphere(Vector3f center, float radius) : m_center(center), m_radius(radius) {}

Sphere::Sphere(float cx, float cy, float cz, float radius) : m_radius(radius) {
	m_center = Vector3f(cx, cy, cz);
}

bool Sphere::pointCollision(const Vector3f& point) {
	return (point.x - m_center.x) * (point.x - m_center.x) +
		(point.y - m_center.y) * (point.y - m_center.y) +
		(point.z - m_center.z) * (point.z - m_center.z) < m_radius * m_radius;
}

bool Sphere::sphereCollision(const Sphere& sphere) {
	return (m_center.x - sphere.getCenter().x) * (m_center.x - sphere.getCenter().x) +
		(m_center.y - sphere.getCenter().y) * (m_center.y - sphere.getCenter().y) +
		(m_center.z - sphere.getCenter().z) * (m_center.z - sphere.getCenter().z) < (m_radius + sphere.getRadius()) * (m_radius + sphere.getRadius());
}

Vector3f Sphere::getCenter() const {
	return m_center;
}

float Sphere::getRadius() const {
	return m_radius;
}
