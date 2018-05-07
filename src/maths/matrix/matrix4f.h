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

			Returns:

				The given matrix translated with the given translation

		*/
		static Matrix4f& translate(float x, float y, float z, Matrix4f& dest);

		/*
			Function: Translate

			Translates the given matrix with the given translation

			Parameters:

				translation - The translation of the matrix
				dest - The destination matrix, which will be translated

			Returns:

				The given matrix translated with the given translation

		*/
		static Matrix4f& translate(const Vector3f& translation, Matrix4f& dest);


		/*
			Function: Translate

			Translates this matrix with the given translation

			Parameters:

				x - The translation of the matrix on the x-axis
				y - The translation of the matrix on the y-axis
				z - The translation of the matrix on the z-axis

			Returns:

				This matrix translated with the given translation

		*/
		Matrix4f& translate(float x, float y, float z);

		/*
			Function: Translate

			Translates this matrix with the given translation

			Parameters:

				translation - The translation of the matrix

			Returns:

				This matrix translated with the given translation

		*/
		Matrix4f& translate(const Vector3f& translation);


		/*
			Function: Rotation

			Constructs a rotation matrix with the given rotation parameters

			Parameters:

				angle - The angle of rotation
				x - The scale of the rotation on the x-axis
				y - The scale of the rotation on the y-axis
				z - The scale of the rotation on the z-axis

			Returns:

				A rotation matrix constructed with the given rotation parameters

		*/
		static Matrix4f rotation(float angle, float x, float y, float z);

		/*
			Function: Rotation

			Constructs a rotation matrix with the given rotation parameters

			Parameters:

				angle - The angle of rotation
				axis - The scale of the rotation on the xyz-axes

			Returns:

				A rotation matrix constructed with the given rotation parameters

		*/
		static Matrix4f rotation(float angle, const Vector3f& axis);


		/*
			Function: Rotate

			Rotates the given matrix with the given rotation parameters

			Parameters:

				angle - The angle of rotation
				x - The scale of the rotation on the x-axis
				y - The scale of the rotation on the y-axis
				z - The scale of the rotation on the z-axis
				dest - The destination matrix, which will be rotated

			Returns:

				The given matrix rotated with the given rotation parameters

		*/
		static Matrix4f& rotate(float angle, float x, float y, float z, Matrix4f& dest);

		/*
			Function: Rotate

			Rotates the given matrix with the given rotation parameters

			Parameters:

				angle - The angle of rotation
				axis - The scale of the rotation on the xyz-axes
				dest - The destination matrix, which will be rotated

			Returns:

				The given matrix rotated with the given rotation parameters

		*/
		static Matrix4f& rotate(float angle, const Vector3f& axis, Matrix4f& dest);


		/*
			Function: Rotate

			Rotates this matrix with the given rotation parameters

			Parameters:

				angle - The angle of rotation
				x - The scale of the rotation on the x-axis
				y - The scale of the rotation on the y-axis
				z - The scale of the rotation on the z-axis

			Returns:

				This matrix rotated with the given rotation parameters

		*/
		Matrix4f& rotate(float angle, float x, float y, float z);

		/*
			Function: Rotate

			Rotates this matrix with the given rotation parameters

			Parameters:

				angle - The angle of rotation
				axis - The scale of the rotation on the xyz-axes

			Returns:

				This matrix rotated with the given rotation parameters

		*/
		Matrix4f& rotate(float angle, const Vector3f& axis);


		/*
			Function: Scaling

			Constructs a scale matrix with the given scale

			Parameters:

				x - The scale of the matrix on the x-axis
				y - The scale of the matrix on the y-axis
				z - The scale of the matrix on the z-axis

			Returns:

				A scale matrix constructed with the given scale

		*/
		static Matrix4f scaling(float x, float y, float z);

		/*
			Function: Scaling

			Constructs a scale matrix with the given scale

			Parameters:

				scale - The scale of the matrix

			Returns:

				A scale matrix constructed with the given scale

		*/
		static Matrix4f scaling(const Vector3f& scale);


		/*
			Function: Scaling

			Scales the given matrix with the given scale

			Parameters:

				x - The scale of the matrix on the x-axis
				y - The scale of the matrix on the y-axis
				z - The scale of the matrix on the z-axis
				dest - The destination matrix, which will be scaled

			Returns:

				The given matrix scaled with the given scale

		*/
		static Matrix4f& scale(float x, float y, float z, Matrix4f& dest);

		/*
			Function: Scaling

			Scales the given matrix with the given scale

			Parameters:

				scale - The scale of the matrix
				dest - The destination matrix, which will be scaled

			Returns:

				The given matrix scaled with the given scale

		*/
		static Matrix4f& scale(const Vector3f& scale, Matrix4f& dest);


		/*
			Function: Rotate

			Scales this matrix with the given scale

			Parameters:

				x - The scale of the matrix on the x-axis
				y - The scale of the matrix on the y-axis
				z - The scale of the matrix on the z-axis

			Returns:

				This matrix scaled with the given scale

		*/
		Matrix4f& scale(float x, float y, float z);

		/*
			Function: Rotate

			Scales this matrix with the given scale

			Parameters:

				scale - The scale of the matrix

			Returns:

				This matrix scaled with the given scale

		*/
		Matrix4f& scale(const Vector3f& scale);


		/*
			Function: Looking at

			Constructs a matrix that looks at a vector from an eye vector

			Parameters:

				eyeX - The x position of the eye vector
				eyeY - The y position of the eye vector
				eyeZ - The z position of the eye vector
				centerX - The x position of the vector the matrix looks at
				centerY - The y position of the vector the matrix looks at
				centerZ - The z position of the vector the matrix looks at
				upX - The x value of the up vector of the eye
				upY - The y value of the up vector of the eye
				upZ - The z value of the up vector of the eye

			Returns:

				A matrix that looks at a vector from an eye vector
				
		*/
		static Matrix4f lookingAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

		/*
			Function: Looking at

			Constructs a matrix that looks at a vector from an eye vector

			Parameters:

				eye - The eye vector
				center - The center vector of the point the matrix looks at
				up - The up vector of the eye

			Returns:

				A matrix that looks at a vector from an eye vector

		*/
		static Matrix4f lookingAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);


		/*
			Function: Looking at

			Converts the given matrix to look at a vector from an eye vector

			Parameters:

				eyeX - The x position of the eye vector
				eyeY - The y position of the eye vector
				eyeZ - The z position of the eye vector
				centerX - The x position of the vector the matrix looks at
				centerY - The y position of the vector the matrix looks at
				centerZ - The z position of the vector the matrix looks at
				upX - The x value of the up vector of the eye
				upY - The y value of the up vector of the eye
				upZ - The z value of the up vector of the eye
				dest - The destination matrix, which will be converted

			Returns:

				The given matrix that looks at a vector from an eye vector

		*/
		static Matrix4f& lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ, Matrix4f& dest);

		/*
			Function: Looking at

			Converts the given matrix to look at a vector from an eye vector

			Parameters:

				eye - The eye vector
				center - The center vector of the point the matrix looks at
				up - The up vector of the eye
				dest - The destination matrix, which will be converted

			Returns:

				The given matrix that looks at a vector from an eye vector

		*/
		static Matrix4f& lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up, Matrix4f& dest);


		/*
			Function: Looking at

			Converts this matrix to look at a vector from an eye vector

			Parameters:

				eyeX - The x position of the eye vector
				eyeY - The y position of the eye vector
				eyeZ - The z position of the eye vector
				centerX - The x position of the vector the matrix looks at
				centerY - The y position of the vector the matrix looks at
				centerZ - The z position of the vector the matrix looks at
				upX - The x value of the up vector of the eye
				upY - The y value of the up vector of the eye
				upZ - The z value of the up vector of the eye

			Returns:

				This matrix that looks at a vector from an eye vector

		*/
		Matrix4f& lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

		/*
			Function: Looking at

			Converts this matrix to look at a vector from an eye vector

			Parameters:

				eye - The eye vector
				center - The center vector of the point the matrix looks at
				up - The up vector of the eye

			Returns:

				This matrix that looks at a vector from an eye vector

		*/
		Matrix4f& lookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);


		/*
			Function: Invert

			Constructs an inverted matrix from the given matrix

			Parameters:
				
				dest - The matrix that will be inverted

			Returns:

				The given matrix inverted

		*/
		static Matrix4f& invert(const Matrix4f& matrix);

		/*
			Function: Invert

			Inverts this matrix

			Returns:

				This matrix inverted

		*/
		Matrix4f& invert();


		/*
			Function: Multiply

			Multiplies two matrices with eachother

			Parameters:

				left - The first matrix to multiplie
				right - The second matrix to multiplie

			Returns:

				The two matrices multiplied together

		*/
		static Matrix4f multiply(Matrix4f left, const Matrix4f& right);

		/*
			Function: Overload multiplication operator

			Overloads the multiplication operator so matrices can be multiplied with eachother

		*/
		friend Matrix4f operator*(Matrix4f left, const Matrix4f& right);

		/*
			Function: Overload insertion operator

			Overloads the insertion operator so matrices can be printed to the console

		*/
		friend std::ostream& operator<<(std::ostream& stream, const Matrix4f& matrix);

		/*
			Function: Get

			Gets the element of this matrix at the given location

			Parameters:

				x - The x location on the matrix
				y - The y location on the matrix

			Returns:

				The element at the given location

		*/
		float get(int x, int y);

		/*
			Function: Get

			Sets the element of this matrix at the given location to the given value

			Parameters:

				x - The x location on the matrix
				y - The y location on the matrix
				value - The value to set on this matrix

		*/
		void set(int x, int y, float value);
	};
}