#include "vector3f.h"

using namespace engine;

Vector3f::Vector3f(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f::Vector3f() : Vector3f(0.0f, 0.0f, 0.0f) {}
Vector3f::Vector3f(float xyz) : Vector3f(xyz, xyz, xyz) {}
Vector3f::Vector3f(Vector2f& in, float z) : Vector3f(in.x, in.y, z) {}

Vector3f& Vector3f::add(const Vector3f& in) {
	return add(in.x, in.y, in.z);
}

Vector3f& Vector3f::subtract(const Vector3f& in) {
	return subtract(in.x, in.y, in.z);
}

Vector3f& Vector3f::multiply(const Vector3f& in) {
	return multiply(in.x, in.y, in.z);
}

Vector3f& Vector3f::divide(const Vector3f& in) {
	return divide(in.x, in.y, in.z);
}

Vector3f& Vector3f::add(float x, float y, float z) {
	this->x += x;
	this->y += y;
	this->z += z;
	return *this;
}

Vector3f& Vector3f::subtract(float x, float y, float z) {
	this->x -= x;
	this->y -= y;
	this->z -= z;
	return *this;
}

Vector3f& Vector3f::multiply(float x, float y, float z) {
	this->x *= x;
	this->y *= y;
	this->z *= z;
	return *this;
}

Vector3f& Vector3f::divide(float x, float y, float z) {
	this->x /= x;
	this->y /= y;
	this->z /= z;
	return *this;
}

bool Vector3f::equals(const Vector3f& in) {
	return x == in.x && y == in.y && z == in.z;
}

float Vector3f::dot(const Vector3f& in) {
	return dot(*this, in);
}

void Vector3f::normalize() {
	float l = length();
	x /= l;
	y /= l;
	z /= l;
}

Vector3f Vector3f::cross(const Vector3f& in) {
	return cross(*this, in);
}

float Vector3f::lengthSquared() const {
	return x * x + y * y + z * z;
}

float Vector3f::length() const {
	return sqrt(lengthSquared());
}

Vector2f Vector3f::xy() const {
	return Vector2f(x, y);
}

float Vector3f::dot(const Vector3f& left, const Vector3f& right) {
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector3f& Vector3f::normalize(const Vector3f& in) {
	Vector3f out(in);
	out.normalize();
	return out;
}

Vector3f Vector3f::cross(const Vector3f& left, const Vector3f& right) {
	return Vector3f(left.y * right.z - right.y * left.z, left.z * right.x - right.z * left.x, left.x * right.y - right.x * left.y);
}

Vector3f Vector3f::add(const Vector3f& left, const Vector3f& right) {
	Vector3f out(left);
	out.add(right);
	return out;
}

Vector3f Vector3f::subtract(const Vector3f& left, const Vector3f& right) {
	Vector3f out(left);
	out.subtract(right);
	return out;
}

Vector3f Vector3f::multiply(const Vector3f& left, const Vector3f& right) {
	Vector3f out(left);
	out.multiply(right);
	return out;
}

Vector3f Vector3f::divide(const Vector3f& left, const Vector3f& right) {
	Vector3f out(left);
	out.divide(right);
	return out;
}

std::ostream& engine::operator<<(std::ostream& stream, const Vector3f& vector) {
	stream << "Vector3f(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}

Vector3f engine::operator+(const Vector3f& left, const Vector3f& right) {
	return Vector3f::add(left, right);
}

Vector3f engine::operator-(const Vector3f& left, const Vector3f& right) {
	return Vector3f::subtract(left, right);
}

Vector3f engine::operator*(const Vector3f& left, const Vector3f& right) {
	return Vector3f::multiply(left, right);
}

Vector3f engine::operator/(const Vector3f& left, const Vector3f& right) {
	return Vector3f::divide(left, right);
}
