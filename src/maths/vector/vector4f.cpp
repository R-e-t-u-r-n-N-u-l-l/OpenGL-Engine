#include "vector4f.h"

using namespace engine;

Vector4f::Vector4f(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4f::Vector4f() : Vector4f(0.0f, 0.0f, 0.0f, 0.0f) {}
Vector4f::Vector4f(float xyzw) : Vector4f(xyzw, xyzw, xyzw, xyzw) {}
Vector4f::Vector4f(Vector3f& in, float w) : Vector4f(in.x, in.y, in.z, w) {}
Vector4f::Vector4f(Vector2f& in, float z, float w) : Vector4f(in.x, in.y, z, w) {}

Vector4f& Vector4f::add(const Vector4f& in) {
	x += in.x;
	y += in.y;
	z += in.z;
	w += in.w;
	return *this;
}

Vector4f& Vector4f::subtract(const Vector4f& in) {
	x -= in.x;
	y -= in.y;
	z -= in.z;
	w -= in.w;
	return *this;
}

Vector4f& Vector4f::multiply(const Vector4f& in) {
	x *= in.x;
	y *= in.y;
	z *= in.z;
	w *= in.w;
	return *this;
}

Vector4f& Vector4f::divide(const Vector4f& in) {
	x /= in.x;
	y /= in.y;
	z /= in.z;
	w /= in.w;
	return *this;
}

bool Vector4f::equals(const Vector4f & in) {
	return x == in.x && y == in.y && z == in.z && w == in.w;
}

float Vector4f::dot(const Vector4f& in) {
	return dot(*this, in);
}

void Vector4f::normalize() {
	float l = length();
	x /= l;
	y /= l;
	z /= l;
	w /= l;
}

float Vector4f::lengthSquared() const {
	return x * x + y * y + z * z + w * w;
}

float Vector4f::length() const {
	return sqrt(lengthSquared());
}

Vector2f Vector4f::xy() const {
	return Vector2f(x, y);
}

Vector3f Vector4f::xyz() const {
	return Vector3f(x, y, z);
}

float Vector4f::dot(const Vector4f& left, const Vector4f& right) {
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

Vector4f& Vector4f::normalize(const Vector4f & in) {
	Vector4f out(in);
	out.normalize();
	return out;
}

Vector4f& Vector4f::multiply(const Matrix4f& matrix, const Vector4f& in) {
	Vector4f dest;
	float rx = matrix.elements[0 + 0 * 4] * in.x + matrix.elements[0 + 1 * 4] * in.y + matrix.elements[0 + 2 * 4] * in.z + matrix.elements[0 + 3 * 4] * in.w;
	float ry = matrix.elements[1 + 0 * 4] * in.x + matrix.elements[1 + 1 * 4] * in.y + matrix.elements[1 + 2 * 4] * in.z + matrix.elements[1 + 3 * 4] * in.w;
	float rz = matrix.elements[2 + 0 * 4] * in.x + matrix.elements[2 + 1 * 4] * in.y + matrix.elements[2 + 2 * 4] * in.z + matrix.elements[2 + 3 * 4] * in.w;
	float rw = matrix.elements[3 + 0 * 4] * in.x + matrix.elements[3 + 1 * 4] * in.y + matrix.elements[3 + 2 * 4] * in.z + matrix.elements[3 + 3 * 4] * in.w;
	dest.x = rx;
	dest.y = ry;
	dest.z = rz;
	dest.w = rw;
	return dest;
}

Vector4f Vector4f::add(const Vector4f& left, const Vector4f& right) {
	Vector4f out(left);
	out.add(right);
	return out;
}

Vector4f Vector4f::subtract(const Vector4f& left, const Vector4f& right) {
	Vector4f out(left);
	out.subtract(right);
	return out;
}

Vector4f Vector4f::multiply(const Vector4f& left, const Vector4f& right) {
	Vector4f out(left);
	out.multiply(right);
	return out;
}

Vector4f Vector4f::divide(const Vector4f& left, const Vector4f& right) {
	Vector4f out(left);
	out.divide(right);
	return out;
}

std::ostream& engine::operator<<(std::ostream& stream, const Vector4f& vector) {
	stream << "Vector4f(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
	return stream;
}

Vector4f engine::operator+(const Vector4f& left, const Vector4f& right) {
	return Vector4f::add(left, right);
}

Vector4f engine::operator-(const Vector4f& left, const Vector4f& right) {
	return Vector4f::subtract(left, right);
}

Vector4f engine::operator*(const Vector4f& left, const Vector4f& right) {
	return Vector4f::multiply(left, right);
}

Vector4f engine::operator/(const Vector4f& left, const Vector4f& right) {
	return Vector4f::divide(left, right);
}
