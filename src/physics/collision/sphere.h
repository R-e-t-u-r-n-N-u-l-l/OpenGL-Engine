#pragma once

#include "../../maths/maths.h"

namespace engine {

	class Sphere {

	private:
		Vector3f m_center;
		float m_radius;

	public:
		Sphere();
		Sphere(Vector3f center, float radius);
		Sphere(float cx, float cy, float cz, float radius);

		bool pointCollision(const Vector3f& point);
		bool sphereCollision(const Sphere& sphere);

		Vector3f getCenter() const;
		float getRadius() const;
	};
}
