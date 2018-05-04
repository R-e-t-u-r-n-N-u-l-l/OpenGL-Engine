#pragma once

#include <iostream>

#include "../vector/vector2f.h"

namespace engine {

	class Vector3f {

	public:
		float x, y, z;

		Vector3f();
		Vector3f(float xyz);
		Vector3f(float x, float y, float z);
		Vector3f(Vector2f& vector, float z);

		Vector3f& add(const Vector3f& in);
		Vector3f& subtract(const Vector3f& in);
		Vector3f& multiply(const Vector3f& in);
		Vector3f& divide(const Vector3f& in);

		Vector3f& add(float x, float y, float z);
		Vector3f& subtract(float x, float y, float z);
		Vector3f& multiply(float x, float y, float z);
		Vector3f& divide(float x, float y, float z);

		bool equals(const Vector3f& in);

		float dot(const Vector3f& in);
		void normalize();
		Vector3f cross(const Vector3f& in);

		float length() const;
		float lengthSquared() const;

		Vector2f xy() const;

		static float dot(const Vector3f& left, const Vector3f& right);
		static Vector3f normalize(Vector3f in);
		static Vector3f cross(const Vector3f& left, const Vector3f& right);

		static Vector3f add(const Vector3f& left, const Vector3f& right);
		static Vector3f subtract(const Vector3f& left, const Vector3f& right);
		static Vector3f multiply(const Vector3f& left, const Vector3f& right);
		static Vector3f divide(const Vector3f& left, const Vector3f& right);

		friend std::ostream& operator<<(std::ostream& stream, const Vector3f& vector);
		friend Vector3f operator+(const Vector3f& left, const Vector3f& right);
		friend Vector3f operator-(const Vector3f& left, const Vector3f& right);
		friend Vector3f operator*(const Vector3f& left, const Vector3f& right);
		friend Vector3f operator/(const Vector3f& left, const Vector3f& right);
	};
}