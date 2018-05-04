#pragma once

#include "../../maths/vector/vector3f.h"

namespace engine {

	class AABB {

	private:
		Vector3f m_min;
		Vector3f m_max;

	public:
		AABB();
		AABB(Vector3f min, Vector3f max);
		AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

		bool pointCollision(const Vector3f& point);
		bool AABBCollision(const AABB& box);

		Vector3f getMin() const;
		Vector3f getMax() const;
	};
}
