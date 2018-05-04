#pragma once

#include <iostream>

#include "vector3f.h"
#include "../matrix/matrix4f.h"

namespace engine {

	class Vector4f {

	public:
		float x, y, z, w;

		Vector4f();
		Vector4f(float x, float y, float z, float w);
		Vector4f(Vector3f& vector, float w);

		Vector4f& add(const Vector4f& in);
		Vector4f& subtract(const Vector4f& in);
		Vector4f& multiply(const Vector4f& in);
		Vector4f& divide(const Vector4f& in);

		static Vector4f& multiply(const Matrix4f& matrix, const Vector4f& in);

		bool equals(const Vector4f& in);

		float lengthSquared() const;
		float length() const;

		Vector3f xyz() const;

		static Vector4f add(const Vector4f& left, const Vector4f& right);
		static Vector4f subtract(const Vector4f& left, const Vector4f& right);
		static Vector4f multiply(const Vector4f& left, const Vector4f& right);
		static Vector4f divide(const Vector4f& left, const Vector4f& right);

		friend std::ostream& operator<<(std::ostream& stream, const Vector4f& vector);
		friend Vector4f operator+(const Vector4f& left, const Vector4f& right);
		friend Vector4f operator-(const Vector4f& left, const Vector4f& right);
		friend Vector4f operator*(const Vector4f& left, const Vector4f& right);
		friend Vector4f operator/(const Vector4f& left, const Vector4f& right);
	};
}