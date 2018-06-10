#include "matrix4f.h"

using namespace engine;

Matrix4f::Matrix4f() {
	for (int i = 0; i < 4 * 4; i++)
		elements[i] = 0.0f;
}

Matrix4f::Matrix4f(float d) {
	for (int i = 0; i < 4 * 4; i++)
		elements[i] = 0.0f;

	elements[0 + 0 * 4] = d;
	elements[1 + 1 * 4] = d;
	elements[2 + 2 * 4] = d;
	elements[3 + 3 * 4] = d;
}

Matrix4f& Matrix4f::multiply(const Matrix4f& in) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			float sum = 0.0f;
			for (int e = 0; e < 4; e++) 
				sum += elements[j + e * 4] * in.elements[e + i * 4];
			
			elements[j + i * 4] = sum;
		}
	}

	return *this;
}

Matrix4f Matrix4f::ortho(float left, float right, float bottom, float top, float near, float far) {
	Matrix4f matrix(1.0f);

	matrix.elements[0 + 0 * 4] = 2.0f / (right - left);
	matrix.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	matrix.elements[2 + 2 * 4] = 2.0f / (near - far);

	matrix.elements[0 + 3 * 4] = (right + left) / (left - right);
	matrix.elements[1 + 3 * 4] = (top + bottom) / (bottom - top);
	matrix.elements[2 + 3 * 4] = (far + near) / (near - far);

	return matrix;
}

Matrix4f Matrix4f::perspective(float fov, float aspect, float near, float far) {
	Matrix4f matrix;

	matrix.elements[0 + 0 * 4] = 1.0f / (aspect * tan(fov / 2));
	matrix.elements[1 + 1 * 4] = 1.0f / tan(fov / 2);
	matrix.elements[2 + 2 * 4] = (far + near) / (near - far);

	matrix.elements[2 + 3 * 4] = (2 * far * near) / (near - far);

	matrix.elements[3 + 2 * 4] = -1.0f;

	return matrix;
}

Matrix4f Matrix4f::translation(float x, float y, float z) {
	Matrix4f matrix(1.0f);

	matrix.elements[0 + 3 * 4] = x;
	matrix.elements[1 + 3 * 4] = y;
	matrix.elements[2 + 3 * 4] = z;

	return matrix;
}

Matrix4f Matrix4f::translation(const Vector3f& translation) {
	return Matrix4f::translation(translation.x, translation.y, translation.z);
}

Matrix4f& Matrix4f::translate(float x, float y, float z, Matrix4f& dest) {
	dest.elements[0 + 3 * 4] = dest.elements[0 + 0 * 4] * x + dest.elements[0 + 1 * 4] * y + dest.elements[0 + 2 * 4] * z + dest.elements[0 + 3 * 4];
	dest.elements[1 + 3 * 4] = dest.elements[1 + 0 * 4] * x + dest.elements[1 + 1 * 4] * y + dest.elements[1 + 2 * 4] * z + dest.elements[1 + 3 * 4];
	dest.elements[2 + 3 * 4] = dest.elements[2 + 0 * 4] * x + dest.elements[2 + 1 * 4] * y + dest.elements[2 + 2 * 4] * z + dest.elements[2 + 3 * 4];
	dest.elements[3 + 3 * 4] = dest.elements[3 + 0 * 4] * x + dest.elements[3 + 1 * 4] * y + dest.elements[3 + 2 * 4] * z + dest.elements[3 + 3 * 4];

	return dest;
}

Matrix4f& Matrix4f::translate(const Vector3f& translation, Matrix4f& dest) {
	return Matrix4f::translate(translation.x, translation.y, translation.z, dest);
}

Matrix4f& Matrix4f::translate(float x, float y, float z) {
	return translate(x, y, z, *this);
}

Matrix4f& Matrix4f::translate(const Vector3f & translation) {
	return translate(translation.x, translation.y, translation.z, *this);
}

Matrix4f Matrix4f::rotation(float angle, float x, float y, float z) {
	Matrix4f matrix(1.0f);

	float s   = sin(angle);
	float c	  = cos(angle);
	float C   = 1.0f - c;

	matrix.elements[0 + 0 * 4] = x * x * C + c;
	matrix.elements[1 + 0 * 4] = x * y * C + z * s;
	matrix.elements[2 + 0 * 4] = x * z * C - y * s;

	matrix.elements[0 + 1 * 4] = x * y * C - z * s;
	matrix.elements[1 + 1 * 4] = y * y * C + c;
	matrix.elements[2 + 1 * 4] = y * z * C + x * s;

	matrix.elements[0 + 2 * 4] = x * z * C + y * s;
	matrix.elements[1 + 2 * 4] = y * z * C - x * s;
	matrix.elements[2 + 2 * 4] = z * z * C + c;

	return matrix;
}

Matrix4f Matrix4f::rotation(float angle, const Vector3f& axis) {
	return Matrix4f::rotation(angle, axis.x, axis.y, axis.z);
}

Matrix4f& Matrix4f::rotate(float angle, float x, float y, float z, Matrix4f& dest) {
	float s = sin(angle);
	float c = cos(angle);
	float C = 1.0f - c;

	float p00 = x * x * C + c;
	float p01 = x * y * C + z * s;
	float p02 = x * z * C - y * s;
	 
	float p10 = x * y * C - z * s;
	float p11 = y * y * C + c;
	float p12 = y * z * C + x * s;
	 
	float p20 = x * z * C + y * s;
	float p21 = y * z * C - x * s;
	float p22 = z * z * C + c;

	float t00 = dest.elements[0 + 0 * 4] * p00 + dest.elements[0 + 1 * 4] * p01 + dest.elements[0 + 2 * 4] * p02;
	float t01 = dest.elements[1 + 0 * 4] * p00 + dest.elements[1 + 1 * 4] * p01 + dest.elements[1 + 2 * 4] * p02;
	float t02 = dest.elements[2 + 0 * 4] * p00 + dest.elements[2 + 1 * 4] * p01 + dest.elements[2 + 2 * 4] * p02;
	float t03 = dest.elements[3 + 0 * 4] * p00 + dest.elements[3 + 1 * 4] * p01 + dest.elements[3 + 2 * 4] * p02;
	  
	float t10 = dest.elements[0 + 0 * 4] * p10 + dest.elements[0 + 1 * 4] * p11 + dest.elements[0 + 2 * 4] * p12;
	float t11 = dest.elements[1 + 0 * 4] * p10 + dest.elements[1 + 1 * 4] * p11 + dest.elements[1 + 2 * 4] * p12;
	float t12 = dest.elements[2 + 0 * 4] * p10 + dest.elements[2 + 1 * 4] * p11 + dest.elements[2 + 2 * 4] * p12;
	float t13 = dest.elements[3 + 0 * 4] * p10 + dest.elements[3 + 1 * 4] * p11 + dest.elements[3 + 2 * 4] * p12;
							   
	dest.elements[0 + 2 * 4] = dest.elements[0 + 0 * 4] * p20 + dest.elements[0 + 1 * 4] * p21 + dest.elements[0 + 2 * 4] * p22;
	dest.elements[1 + 2 * 4] = dest.elements[1 + 0 * 4] * p20 + dest.elements[1 + 1 * 4] * p21 + dest.elements[1 + 2 * 4] * p22;
	dest.elements[2 + 2 * 4] = dest.elements[2 + 0 * 4] * p20 + dest.elements[2 + 1 * 4] * p21 + dest.elements[2 + 2 * 4] * p22;
	dest.elements[3 + 2 * 4] = dest.elements[3 + 0 * 4] * p20 + dest.elements[3 + 1 * 4] * p21 + dest.elements[3 + 2 * 4] * p22;

	dest.elements[0 + 0 * 4] = t00;
	dest.elements[1 + 0 * 4] = t01;
	dest.elements[2 + 0 * 4] = t02;
	dest.elements[3 + 0 * 4] = t03;
							   
	dest.elements[0 + 1 * 4] = t10;
	dest.elements[1 + 1 * 4] = t11;
	dest.elements[2 + 1 * 4] = t12;
	dest.elements[3 + 1 * 4] = t13;

	return dest;
}

Matrix4f& Matrix4f::rotate(float angle, const Vector3f& axis, Matrix4f& dest) {
	return Matrix4f::rotate(angle, axis.x, axis.y, axis.z, dest);
}

Matrix4f& Matrix4f::rotate(float angle, float x, float y, float z) {
	return rotate(angle, x, y, z, *this);
}

Matrix4f& Matrix4f::rotate(float angle, const Vector3f& axis) {
	return rotate(angle, axis.x, axis.y, axis.z, *this);
}

Matrix4f Matrix4f::scaling(float x, float y, float z) {
	Matrix4f matrix(1.0f);

	matrix.elements[0 + 0 * 4] = x;
	matrix.elements[1 + 1 * 4] = y;
	matrix.elements[2 + 2 * 4] = z;

	return matrix;
}

Matrix4f Matrix4f::scaling(const Vector3f& scale) {
	return Matrix4f::scaling(scale.x, scale.y, scale.z);
}

Matrix4f& Matrix4f::scale(float x, float y, float z, Matrix4f& dest) {
	for (int i = 0; i < 4; i++) {
		dest.elements[i + 0 * 4] *= x;
		dest.elements[i + 1 * 4] *= y;
		dest.elements[i + 2 * 4] *= z;
	}

	return dest;
}

Matrix4f& Matrix4f::scale(const Vector3f& scale, Matrix4f& dest) {
	return Matrix4f::scale(scale.x, scale.y, scale.z, dest);
}

Matrix4f& Matrix4f::scale(float x, float y, float z) {
	return scale(x, y, z, *this);
}

Matrix4f& Matrix4f::scale(const Vector3f& scale) {
	return Matrix4f::scale(scale.x, scale.y, scale.z, *this);
}

Matrix4f Matrix4f::lookingAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
	Matrix4f matrix(1.0f);
	matrix.lookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	return matrix;
}

Matrix4f Matrix4f::lookingAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up) {
	Matrix4f matrix(1.0f);
	matrix.lookAt(eye, center, up);
	return matrix;
}

Matrix4f& Matrix4f::lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ, Matrix4f& dest) {
	return Matrix4f::lookAt(Vector3f(eyeX, eyeY, eyeZ), Vector3f(centerX, centerY, centerZ), Vector3f(upX, upY, upZ), dest);
}	 
	 
Matrix4f& Matrix4f::lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up, Matrix4f& dest) {
	Vector3f zAxis = Vector3f::normalize(Vector3f::subtract(eye, center));
	Vector3f xAxis = Vector3f::normalize(Vector3f::cross(up, zAxis));
	Vector3f yAxis = Vector3f::cross(zAxis, xAxis);

	dest.elements[0 + 0 * 4] = xAxis.x;
	dest.elements[1 + 0 * 4] = yAxis.x;
	dest.elements[2 + 0 * 4] = zAxis.x;
	dest.elements[0 + 1 * 4] = xAxis.y;
	dest.elements[1 + 1 * 4] = yAxis.y;
	dest.elements[2 + 1 * 4] = zAxis.y;
	dest.elements[0 + 2 * 4] = xAxis.z;
	dest.elements[1 + 2 * 4] = yAxis.z;
	dest.elements[2 + 2 * 4] = zAxis.z;
	dest.elements[0 + 3 * 4] = -Vector3f::dot(xAxis, eye);
	dest.elements[1 + 3 * 4] = -Vector3f::dot(yAxis, eye);
	dest.elements[2 + 3 * 4] = -Vector3f::dot(zAxis, eye);

	return dest;
}	 
	 
Matrix4f& Matrix4f::lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
	return Matrix4f::lookAt(Vector3f(eyeX, eyeY, eyeZ), Vector3f(centerX, centerY, centerZ), Vector3f(upX, upY, upZ), *this);
}	 
	 
Matrix4f& Matrix4f::lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up) {
	return Matrix4f::lookAt(eye, center, up, *this);
}

Matrix4f& Matrix4f::invert(const Matrix4f& matrix) {
	Matrix4f dest(matrix);

	float a = dest.elements[0 + 0 * 4] * dest.elements[1 + 1 * 4] - dest.elements[1 + 0 * 4] * dest.elements[0 + 1 * 4];
	float b = dest.elements[0 + 0 * 4] * dest.elements[2 + 1 * 4] - dest.elements[2 + 0 * 4] * dest.elements[0 + 1 * 4];
	float c = dest.elements[0 + 0 * 4] * dest.elements[3 + 1 * 4] - dest.elements[3 + 0 * 4] * dest.elements[0 + 1 * 4];
	float d = dest.elements[1 + 0 * 4] * dest.elements[2 + 1 * 4] - dest.elements[2 + 0 * 4] * dest.elements[1 + 1 * 4];
	float e = dest.elements[1 + 0 * 4] * dest.elements[3 + 1 * 4] - dest.elements[3 + 0 * 4] * dest.elements[1 + 1 * 4];
	float f = dest.elements[2 + 0 * 4] * dest.elements[3 + 1 * 4] - dest.elements[3 + 0 * 4] * dest.elements[2 + 1 * 4];
	float g = dest.elements[0 + 2 * 4] * dest.elements[1 + 3 * 4] - dest.elements[1 + 2 * 4] * dest.elements[0 + 3 * 4];
	float h = dest.elements[0 + 2 * 4] * dest.elements[1 + 3 * 4] - dest.elements[2 + 2 * 4] * dest.elements[0 + 3 * 4];
	float i = dest.elements[0 + 2 * 4] * dest.elements[3 + 3 * 4] - dest.elements[3 + 2 * 4] * dest.elements[0 + 3 * 4];
	float j = dest.elements[1 + 2 * 4] * dest.elements[2 + 3 * 4] - dest.elements[2 + 2 * 4] * dest.elements[1 + 3 * 4];
	float k = dest.elements[1 + 2 * 4] * dest.elements[3 + 3 * 4] - dest.elements[3 + 2 * 4] * dest.elements[1 + 3 * 4];
	float l = dest.elements[2 + 2 * 4] * dest.elements[3 + 3 * 4] - dest.elements[3 + 2 * 4] * dest.elements[2 + 3 * 4];
	float det = a * l - b * k + c * j + d * i - e * h + f * g;
	det = 1.0f / det;
	float nm00 = (dest.elements[1 + 1 * 4] * l - dest.elements[2 + 1 * 4] * k + dest.elements[3 + 1 * 4] * j) * det;;
	float nm01 = (-dest.elements[1 + 0 * 4] * l + dest.elements[2 + 0 * 4] * k - dest.elements[3 + 0 * 4] * j) * det;;
	float nm02 = (dest.elements[1 + 3 * 4] * f - dest.elements[2 + 3 * 4] * e + dest.elements[3 + 3 * 4] * d) * det;;
	float nm03 = (-dest.elements[1 + 2 * 4] * f + dest.elements[2 + 2 * 4] * e - dest.elements[3 + 2 * 4] * d) * det;;
	float nm10 = (-dest.elements[0 + 1 * 4] * l + dest.elements[2 + 1 * 4] * i - dest.elements[3 + 1 * 4] * h) * det;;
	float nm11 = (dest.elements[0 + 0 * 4] * l - dest.elements[2 + 0 * 4] * i + dest.elements[3 + 0 * 4] * h) * det;;
	float nm12 = (-dest.elements[0 + 3 * 4] * f + dest.elements[2 + 3 * 4] * c - dest.elements[3 + 3 * 4] * b) * det;;
	float nm13 = (dest.elements[0 + 2 * 4] * f - dest.elements[2 + 2 * 4] * c + dest.elements[3 + 2 * 4] * b) * det;;
	float nm20 = (dest.elements[0 + 1 * 4] * k - dest.elements[1 + 1 * 4] * i + dest.elements[3 + 1 * 4] * g) * det;;
	float nm21 = (-dest.elements[0 + 0 * 4] * k + dest.elements[1 + 0 * 4] * i - dest.elements[3 + 0 * 4] * g) * det;;
	float nm22 = (dest.elements[0 + 3 * 4] * e - dest.elements[1 + 0 * 4] * c + dest.elements[3 + 0 * 4] * a) * det;;
	float nm23 = (-dest.elements[0 + 2 * 4] * e + dest.elements[1 + 2 * 4] * c - dest.elements[3 + 2 * 4] * a) * det;;
	float nm30 = (-dest.elements[0 + 1 * 4] * j + dest.elements[1 + 1 * 4] * h - dest.elements[2 + 1 * 4] * g) * det;;
	float nm31 = (dest.elements[0 + 0 * 4] * j - dest.elements[1 + 0 * 4] * h + dest.elements[2 + 0 * 4] * g) * det;;
	float nm32 = (-dest.elements[0 + 3 * 4] * d + dest.elements[1 + 3 * 4] * b - dest.elements[2 + 3 * 4] * a) * det;;
	float nm33 = (dest.elements[0 + 2 * 4] * d - dest.elements[1 + 2 * 4] * b + dest.elements[2 + 2 * 4] * a) * det;;
	dest.elements[0 + 0 * 4] = nm00;
	dest.elements[1 + 0 * 4] = nm01;
	dest.elements[2 + 0 * 4] = nm02;
	dest.elements[3 + 0 * 4] = nm03;
	dest.elements[0 + 1 * 4] = nm10;
	dest.elements[1 + 1 * 4] = nm11;
	dest.elements[2 + 1 * 4] = nm12;
	dest.elements[3 + 1 * 4] = nm13;
	dest.elements[0 + 2 * 4] = nm20;
	dest.elements[1 + 2 * 4] = nm21;
	dest.elements[2 + 2 * 4] = nm22;
	dest.elements[3 + 2 * 4] = nm23;
	dest.elements[0 + 3 * 4] = nm30;
	dest.elements[1 + 3 * 4] = nm31;
	dest.elements[2 + 3 * 4] = nm32;
	dest.elements[3 + 3 * 4] = nm33;

	return dest;
}

Matrix4f& Matrix4f::invert() {
	*this = Matrix4f::invert(*this);
	return *this;
}

Matrix4f Matrix4f::multiply(Matrix4f left, const Matrix4f& right) {
	return left.multiply(right);
}

Matrix4f engine::operator*(Matrix4f left, const Matrix4f& right) {
	return left.multiply(right);
}

std::ostream& engine::operator<<(std::ostream& stream, const Matrix4f& matrix) {
	stream << "Matrix4f[" << matrix.elements[0 + 0 * 4] << ", " << matrix.elements[1 + 0 * 4] << ", " << matrix.elements[2 + 0 * 4] << ", " << matrix.elements[3 + 0 * 4] << "]" << std::endl
		   << "        [" << matrix.elements[0 + 1 * 4] << ", " << matrix.elements[1 + 1 * 4] << ", " << matrix.elements[2 + 1 * 4] << ", " << matrix.elements[3 + 1 * 4] << "]" << std::endl
		   << "        [" << matrix.elements[0 + 2 * 4] << ", " << matrix.elements[1 + 2 * 4] << ", " << matrix.elements[2 + 2 * 4] << ", " << matrix.elements[3 + 2 * 4] << "]" << std::endl
		   << "        [" << matrix.elements[0 + 3 * 4] << ", " << matrix.elements[1 + 3 * 4] << ", " << matrix.elements[2 + 3 * 4] << ", " << matrix.elements[3 + 3 * 4] << "]";
	return stream;
}

float Matrix4f::get(int x, int y) {
	return elements[y + x * 4];
}

void Matrix4f::set(int x, int y, float value) {
	elements[y + x * 4] = value;
}
