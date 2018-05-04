#include "AABB.h"

using namespace engine;

AABB::AABB() {
	m_min = Vector3f(-1.0f, -1.0f, -1.0f);
	m_max = Vector3f(1.0f, 1.0f, 1.0f);
}

AABB::AABB(Vector3f min, Vector3f max) : m_min(min), m_max(max) {}

AABB::AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	m_min = Vector3f(minX, minY, minZ);
	m_max = Vector3f(maxX, maxY, maxZ);
}

bool AABB::pointCollision(const Vector3f& point) {
	return (point.x >= m_min.x && point.x <= m_max.x) &&
		   (point.y >= m_min.y && point.y <= m_max.y) &&
		   (point.z >= m_min.z && point.z <= m_max.z);
}

bool AABB::AABBCollision(const AABB& box) {
	return (box.getMin().x <= m_max.x && box.getMax().x >= m_min.x) &&
		   (box.getMin().y <= m_max.y && box.getMax().y >= m_min.y) &&
		   (box.getMin().z <= m_max.z && box.getMax().z >= m_min.z);
}

Vector3f AABB::getMin() const {
	return m_min;
}

Vector3f AABB::getMax() const {
	return m_max;
}
