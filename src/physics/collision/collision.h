#pragma once

#include "../../maths/maths.h"
#include "AABB.h"
#include "Sphere.h"

namespace engine {

	namespace Collision {

		static bool pointSphereCollision(const Vector3f& point, const Sphere& sphere) {
			return (point.x - sphere.getCenter().x) * (point.x - sphere.getCenter().x) +
				(point.y - sphere.getCenter().y) * (point.y - sphere.getCenter().y) +
				(point.z - sphere.getCenter().z) * (point.z - sphere.getCenter().z) < sphere.getRadius() * sphere.getRadius();
		}

		static bool sphereCollision(const Sphere& sphere1, const Sphere& sphere2) {
			return (sphere1.getCenter().x - sphere2.getCenter().x) * (sphere1.getCenter().x - sphere2.getCenter().x) +
				(sphere1.getCenter().y - sphere2.getCenter().y) * (sphere1.getCenter().y - sphere2.getCenter().y) +
				(sphere1.getCenter().z - sphere2.getCenter().z) * (sphere1.getCenter().z - sphere2.getCenter().z) < (sphere1.getRadius() + sphere2.getRadius()) * (sphere1.getRadius() + sphere2.getRadius());
		}

		static bool pointABBBCollision(const AABB& box, const Vector3f& point) {
			return (point.x >= box.getMin().x && point.x <= box.getMax().x) &&
				(point.y >= box.getMin().y && point.y <= box.getMax().y) &&
				(point.z >= box.getMin().z && point.z <= box.getMax().z);
		}

		static bool AABBCollision(const AABB& box1, const AABB& box2) {
			return (box1.getMin().x <= box2.getMax().x && box1.getMax().x >= box2.getMin().x) &&
				(box1.getMin().y <= box2.getMax().y && box1.getMax().y >= box2.getMin().y) &&
				(box1.getMin().z <= box2.getMax().z && box1.getMax().z >= box2.getMin().z);
		}

		static bool sphereAABBCollision(const AABB& box, const Sphere& sphere) {
			float x = Maths::max(box.getMin().x, Maths::min(sphere.getCenter().x, box.getMax().x));
			float y = Maths::max(box.getMin().y, Maths::min(sphere.getCenter().y, box.getMax().y));
			float z = Maths::max(box.getMin().z, Maths::min(sphere.getCenter().z, box.getMax().z));

			return (x - sphere.getCenter().x) * (x - sphere.getCenter().x) +
				(y - sphere.getCenter().y) * (y - sphere.getCenter().y) +
				(z - sphere.getCenter().z) * (z - sphere.getCenter().z) < sphere.getRadius() * sphere.getRadius();
		}

		static bool sphereLineCollision(const Vector3f& p, const Vector3f& dist, const Sphere& sphere, Vector3f& intersection) {
			Vector3f m = Vector3f::subtract(p, sphere.getCenter());
			float b = Vector3f::dot(m, dist);
			float c = Vector3f::dot(m, m) - sphere.getRadius() * sphere.getRadius();

			if (c > 0.0f && b > 0.0f)
				return false;
			float d = b * b - c;

			if (d < 0.0f)
				return false;

			float t = -b - sqrt(d);

			t = Maths::max(0.0f, t);
			intersection = Vector3f::add(p, Vector3f(t * d, t * d, t * d));

			return true;
		}

		static bool sphereLineCollision(const Vector3f& p, const Vector3f& dist, const Sphere& sphere) {
			Vector3f v;
			return sphereLineCollision(p, dist, sphere, v);
		}
	}
}
