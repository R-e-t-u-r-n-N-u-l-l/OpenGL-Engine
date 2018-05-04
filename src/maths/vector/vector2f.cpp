#include "vector2f.h"

using namespace engine;

Vector2f::Vector2f() {
	x = 0.0f;
	y = 0.0f;
}

Vector2f::Vector2f(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2f& Vector2f::add(const Vector2f& in) {
	return add(in.x, in.y);
}

Vector2f& Vector2f::subtract(const Vector2f& in) {
	return subtract(in.x, in.y);
}

Vector2f& Vector2f::multiply(const Vector2f& in) {
	return multiply(in.x, in.y);
}

Vector2f& Vector2f::divide(const Vector2f& in) {
	return divide(in.x, in.y);
}

Vector2f& engine::Vector2f::add(float x, float y) {
	this->x += x;
	this->y += y;
	return *this;
}

Vector2f& engine::Vector2f::subtract(float x, float y) {
	this->x -= x;
	this->y -= y;
	return *this;
}

Vector2f& engine::Vector2f::multiply(float x, float y) {
	this->x *= x;
	this->y *= y;
	return *this;
}

Vector2f& engine::Vector2f::divide(float x, float y) {
	this->x /= x;
	this->y /= y;
	return *this;
}

bool Vector2f::equals(const Vector2f & in) {
	return x == in.x && y == in.y;
}

float Vector2f::dot(const Vector2f& in) {
	return dot(*this, in);
}

void Vector2f::normalize() {
	float l = length();
	x /= l;
	y /= l;
}

float Vector2f::lengthSquared() const {
	return x * x + y * y;
}

float Vector2f::length() const {
	return sqrt(lengthSquared());
}

float Vector2f::dot(const Vector2f& left, const Vector2f& right) {
	return left.x * right.x + left.y * right.y;
}

Vector2f Vector2f::normalize(Vector2f in) {
	in.normalize();
	return in;
}

Vector2f Vector2f::add(Vector2f left, const Vector2f& right) {
	return left.add(right);
}

Vector2f Vector2f::subtract(Vector2f left, const Vector2f& right) {
	return left.subtract(right);
}

Vector2f Vector2f::multiply(Vector2f left, const Vector2f& right) {
	return left.multiply(right);
}

Vector2f Vector2f::divide(Vector2f left, const Vector2f& right) {
	return left.divide(right);
}

std::ostream& engine::operator<<(std::ostream& stream, const Vector2f& vector) {
	stream << "Vector2f(" << vector.x << ", " << vector.y << ")";
	return stream;
}

Vector2f engine::operator+(const Vector2f& left, const Vector2f& right) {
	return Vector2f::add(left, right);
}

Vector2f engine::operator-(const Vector2f& left, const Vector2f& right){
	return Vector2f::subtract(left, right);
}

Vector2f engine::operator*(const Vector2f& left, const Vector2f& right) {
	return Vector2f::multiply(left, right);
}

Vector2f engine::operator/(const Vector2f& left, const Vector2f& right) {
	return Vector2f::divide(left, right);
}
