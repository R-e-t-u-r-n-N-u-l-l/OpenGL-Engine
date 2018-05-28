#pragma once

#include <iostream>

#include "vector3f.h"
#include "../matrix/matrix4f.h"

namespace engine {

	/*
		Class: Vector4f

		A class that represents a 4D vector

	*/
	class Vector4f {

	public:

		/*
			Variable: x

			The x value of the vector

			Variable: y

			The y value of the vector

			Variable: z

			The z value of the vector

			Variable: w

			The w value of the vector

		*/
		float x, y, z, w;


		/*
			Constructor: Vector4f

			Initializes the 4D vector as (0, 0, 0, 0)

		*/
		Vector4f();

		/*
			Constructor: Vector4f

			Initializes the 4D vector as (xyzw, xyzw, xyzw, xyzw)

			Parameters:

			xyzw - The value on every axis of the vector

		*/
		Vector4f(float xyzw);

		/*
			Constructor: Vector4f

			Initializes the 4D vector as (x, y, z, w)

			Parameters:

				x - The x value of the vector
				y - The y value of the vector
				z - The z value of the vector
				w - The w value of the vector

		*/
		Vector4f(float x, float y, float z, float w);

		/*
			Constructor: Vector4f

			Initializes the 4D vector as (in.x, in.y, in.z, w)

			Parameters:

				in - The 3D vector that represents the first three values of the vector
				w - The w value of the vector

		*/
		Vector4f(Vector3f& vector, float w);


		/*
			Constructor: Vector4f

			Initializes the 4D vector as (in.x, in.y, z, w)

			Parameters:

				in - The 2D vector that represents the first two values of the vector
				z - The z value of the vector
				w - The w value of the vector

		*/
		Vector4f(Vector2f& vector, float z, float w);

		/*
			Function: Add

			Parameters:

				in - The vector to add to this vector

			Returns:

				The vectors added together

		*/
		Vector4f& add(const Vector4f& in);

		/*
			Function: Subtract

			Parameters:

				in - The vector to subract from this vector

			Returns:

				The other vector subracted from this vector

		*/
		Vector4f& subtract(const Vector4f& in);

		/*
			Function: Multiply

			Parameters:

				in - The vector to multiplie with this vector

			Returns:

				The vectors multiplied together

		*/
		Vector4f& multiply(const Vector4f& in);

		/*
			Function: Divide

			Parameters:

				in - The vector to divide this by

			Returns:

				This vector divided by the other vector

		*/
		Vector4f& divide(const Vector4f& in);


		/*
			Function: Equals

			Compares this vector and another vector and checks if they are equal

			Parameters:

				in - The vector that should be compared with this vector

			Returns:

				True if the vectors are equal otherwise false

		*/
		bool equals(const Vector4f& in);


		/*
			Function: Dot product

			Creates the dot product of this vector and another vector

			Parameters:

				in - The other vector

			Returns:

				The dot product of the vectors

		*/
		float dot(const Vector4f& in);

		/*
			Function: Normalize

			Normalizes this vector

		*/
		void normalize();
		
		/*
			Function: Length squared

			Returns:

				The length of this vector squared

		*/
		float lengthSquared() const;

		/*
			Function: Length

			Returns:

				The length of this vector

		*/
		float length() const;

		/*
			Function: XY

			Returns:

				The x and y value of this vector in a 2D vector

		*/
		Vector2f xy() const;

		/*
			Function: XYZ

			Returns:
				
				The x, y and z value of this vector in a 3D vector

		*/
		Vector3f xyz() const;
		
		
		// STATIC FUNCTIONS

		/*
			Function: Dot product

			Parameters:

				left - The first vector
				right - The second vector

			Returns:

				The dot product of the vectors

		*/
		static float dot(const Vector4f& left, const Vector4f& right);

		/*
			Function: Normalize

			Parameters:

				in - The vector to normalize

			Returns:

				The input vector normalized

		*/
		static Vector4f& normalize(const Vector4f& in);

		
		/*
			Function: Multiply

			Parameters:

				matrix - The 4x4 matrix to multiply with the vector
				in - The 4D vector to multiply with the matrix

			Returns:

				The 4x4 matrix multiplied with the 4D vector

		*/
		static Vector4f& multiply(const Matrix4f& matrix, const Vector4f& in);


		/*
			Function: Add

			Parameters:

				left - The first vector to add
				right - The second vector to add

			Returns:

				The vectors added together

		*/
		static Vector4f add(const Vector4f& left, const Vector4f& right);

		/*
			Function: Subtract

			Parameters:

				left - The vector that is subtracted by right
				right - The vector that subtracts from left

			Returns:

				The right vector subracted from the left vector

		*/
		static Vector4f subtract(const Vector4f& left, const Vector4f& right);

		/*
			Function: Multiply

			Parameters:

				left - The first vector to multiplie
				right - The second vector to multiplie

			Returns:

				The vectors multiplied together

		*/
		static Vector4f multiply(const Vector4f& left, const Vector4f& right);

		/*
			Function: Divide

			Parameters:

				left - The vector that is divided by right
				right - The vector that divides left

			Returns:

				This left vector divided by the right vector

		*/
		static Vector4f divide(const Vector4f& left, const Vector4f& right);


		/*
			Function: Overload insertion operator

			Overloads the insertion operator so 4D vector can be printed to the console

		*/
		friend std::ostream& operator<<(std::ostream& stream, const Vector4f& vector);
	
		/*
			Function: Overload addition operator

			Overloads the addition operator so 4D vectors can be added together

		*/
		friend Vector4f operator+(const Vector4f& left, const Vector4f& right);

		/*
			Function: Overload subtraction operator

			Overloads the subtraction operator so 4D vectors can be subtracted from eachother

		*/
		friend Vector4f operator-(const Vector4f& left, const Vector4f& right);

		/*
			Function: Overload multiplication operator

			Overloads the multiplication operator so 4D vectors can be multiplied with eachother

		*/
		friend Vector4f operator*(const Vector4f& left, const Vector4f& right);

		/*
			Function: Overload division operator

			Overloads the division operator so 4D vectors can be divided by eachother

		*/
		friend Vector4f operator/(const Vector4f& left, const Vector4f& right);
	};
}