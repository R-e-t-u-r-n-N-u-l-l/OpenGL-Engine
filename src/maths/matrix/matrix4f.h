#pragma once

#include <math.h>
#include <iostream>

#include "../vector/vector3f.h"

namespace engine {

	/*
		Class: Matrix4f

		A class that represents a 4x4 matrix

	*/
	class Matrix4f {

	public:
		/*
			Variable: elements

			An array of 16 elements of the matrix

		*/
		float elements[4 * 4];


		/*
			Constructor: Matrix4f

			Initializes the 4x4 matrix as [0, 0, 0, 0]
										  [0, 0, 0, 0]
										  [0, 0, 0, 0]
										  [0, 0, 0, 0]

		*/
		Matrix4f();

		/*
			Constructor: Matrix4f

			Initializes the 4x4 matrix as [d, 0, 0, 0]
										  [0, d, 0, 0]
										  [0, 0, d, 0]
										  [0, 0, 0, d]

			Parameters:

				d - The diagonal of the matrix

		*/
		Matrix4f(float d);


		/*
			Function: Multiply

			Multiplies this matrix with another matrix

			Parameters:

				in - The matrix that will be multiplied with this matrix

			Returns:

				The two matrices multiplied with eachother
				
		*/
		Matrix4f& multiply(const Matrix4f& in);


		/*
			Function: Orthographic

			Constructs an orthographic projection matrix with the given parameters

			Parameters:

				left - The left point of the projection matrix
				right - The right point of the projection matrix
				bottom - The bottom point of the projection matrix
				top - The top point of the projection matrix
				near - The nearest point of the projection matrix
				far - The farthest point of the projection matrix

			Returns:

				An orthographics projection matrix constructed with the given parameters

		*/
		static Matrix4f ortho(float left, float right, float bottom, float top, float near, float far);

		/*
			Function: Perspective

			Constructs and perspective projection matrix with the given parameters

			Parameters:

				fov - The field of view of the perspective matrix
				aspectRatio - The aspect ratio of the perspective matrix
				near - The nearest point of the perspective matrix
				far - The farthest point of the perspective matrix

			Returns:

				A perspective projection matrix constructed with the given parameters

		*/
		static Matrix4f perspective(float fov, float aspectRatio, float near, float far);


		/*
			Function: Translation

			Constructs a translation matrix with the given translation

			Parameters:

				x - The translation of the matrix on the x-axis
				y - The translation of the matrix on the y-axis
				z - The translation of the matrix on the z-axis

			Returns:

				A translation matrix constructed with the given translation

		*/
		static Matrix4f translation(float x, float y, float z);

		/*
			Function: Translation

			Constructs a translation matrix with the given translation

			Parameters:

				translation - The translation of the matrix

			Returns:

				A translation matrix constructed with the given translation

		*/
		static Matrix4f translation(const Vector3f& translation);


		/*
			Function: Translate

			Translates the given matrix with the given translation

			Parameters:

				x - The translation of the matrix on the x-axis
				y - The translation of the matrix on the y-axis
				z - The translation of the matrix on the z-axis
				dest - The destination matrix, which will be translated

		*/
		static Matrix4f& translate(float x, float y, float z, Matrix4f& dest);

		/*
			Function: Translate

			Translates the given matrix with the given translation

			Parameters:

				translation - The translation of the matrix
				dest - The destination matrix, which will be translated

		*/
		static Matrix4f& translate(const Vector3f& translation, Matrix4f& dest);


		/*
			Function: Translate

			Translates this matrix with the given translation

			Parameters:

				x - The translation of the matrix on the x-axis
				y - The translation of the matrix on the y-axis
				z - The translation of the matrix on the z-axis

		*/
		Matrix4f& translate(float x, float y, float z);

		/*
			Function: Translate

			Translates this matrix with the given translation

			Parameters:

				translation - The translation of the matrix

		*/
		Matrix4f& translate(const Vector3f& translation);


		/*
			Function: Rotation
		*/
		static Matrix4f rotation(float angle, float x, float y, float z);
		static Matrix4f rotation(float angle, const Vector3f& axis);

		static void rotate(float angle, float x, float y, float z, Matrix4f& dest);
		static void rotate(float angle, const Vector3f& axis, Matrix4f& dest);

		void rotate(float angle, float x, float y, float z);
		void rotate(float angle, const Vector3f& axis);

		static Matrix4f scaling(float x, float y, float z);
		static Matrix4f scaling(const Vector3f& scale);

		static void scale(float x, float y, float z, Matrix4f& dest);
		static void scale(const Vector3f& scale, Matrix4f& dest);

		void scale(float x, float y, float z);
		void scale(const Vector3f& scale);

		static Matrix4f lookingAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
		static Matrix4f lookingAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);

		static void lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ, Matrix4f& dest);
		static void lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up, Matrix4f& dest);

		void lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
		void lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);

		static void invert(Matrix4f& dest);
		static Matrix4f invert(const Matrix4f& matrix);
		void invert();

		static Matrix4f multiply(Matrix4f left, const Matrix4f& right);
		friend Matrix4f operator*(Matrix4f matrix1, const Matrix4f& matrix2);

		friend std::ostream& operator<<(std::ostream& stream, const Matrix4f& matrix);

		float get(int x, int y);
		void set(int x, int y, float value);
	};
}