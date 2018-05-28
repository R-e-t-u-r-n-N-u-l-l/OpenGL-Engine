#pragma once

#include <iostream>

#include "../vector/vector2f.h"

namespace engine {

	/*
		Class: Vector3f

		A class that represents a 3D vector

	*/
	class Vector3f {

	public:

		/*
			Variable: x

			The x value of the vector

			Variable: y

			The y value of the vector

			Variable: z

			The z value of the vector

		*/
		float x, y, z;


		/*
			Constructor: Vector3f

			Initializes the 3D vector as (0, 0, 0)

		*/
		Vector3f();

		/*
			Constructor: Vector3f

			Initializes the 3D vector as (xyz, xyz, xyz)

			Parameters:

				xyz - The value on every axis of the vector

		*/
		Vector3f(float xyz);

		/*
			Constructor: Vector3f

			Initializes the 3D vector as (x, y, z)

			Parameters:

				x - The x value of the vector
				y - The y value of the vector
				z - The z value of the vector

		*/
		Vector3f(float x, float y, float z);

		/*
			Constructor: Vector3f

			Initializes the 3D vector as (in.x, in.y, z)

			Parameters:

				in - The 2D vector that represents the first two values of the vector
				z - The z value of the vector

		*/
		Vector3f(Vector2f& in, float z);


		/*
			Function: Add

			Parameters:

				in - The vector to add to this vector

			Returns:

				The vectors added together

		*/
		Vector3f& add(const Vector3f& in);

		/*
			Function: Subtract

			Parameters:

				in - The vector to subract from this vector

			Returns:

				The other vector subracted from this vector

		*/
		Vector3f& subtract(const Vector3f& in);

		/*
			Function: Multiply

			Parameters:

				in - The vector to multiplie with this vector

			Returns:

				The vectors multiplied together

		*/
		Vector3f& multiply(const Vector3f& in);

		/*
			Function: Divide

			Parameters:

				in - The vector to divide this by

			Returns:

				This vector divided by the other vector

		*/
		Vector3f& divide(const Vector3f& in);


		/*
			Function: Add

			Parameters:

				x - The x value of the vector to add to this vector
				y - The y value of the vector to add to this vector
				z - The z value of the vector to add to this vector

			Returns:

				The vectors added together

		*/
		Vector3f& add(float x, float y, float z);

		/*
			Function: Subtract

			Parameters:

				x - The x value of the vector to substract from this vector
				y - The y value of the vector to substract from this vector
				z - The z value of the vector to substract from this vector

			Returns:

				The other vector subracted from this vector

		*/
		Vector3f& subtract(float x, float y, float z);

		/*
			Function: Multiply

			Parameters:

				x - The x value of the vector to multiplie with this vector
				y - The y value of the vector to multiplie with this vector
				z - The z value of the vector to multiplie with this vector

			Returns:

				The vectors multiplied together

		*/
		Vector3f& multiply(float x, float y, float z);

		/*
			Function: Divide

			Parameters:

				x - The x value of the vector to divide this by
				y - The y value of the vector to divide this by
				z - The z value of the vector to divide this by

			Returns:

				This vector divided by the other vector

		*/
		Vector3f& divide(float x, float y, float z);


		/*
			Function: Equals

			Compares this vector and another vector and checks if they are equal

			Parameters:

				in - The vector that should be compared with this vector

			Returns:

				True if the vectors are equal otherwise false

		*/
		bool equals(const Vector3f& in);


		/*
		Function: Cross product

		Creates the cross product of this vector and another vector

		Parameters:

		in - The other vector

		Returns:

		The cross product of the vectors

		*/
		Vector3f cross(const Vector3f& in);

		/*
			Function: Dot product

			Creates the dot product of this vector and another vector

			Parameters:

				in - The other vector

			Returns:

				The dot product of the vectors

		*/
		float dot(const Vector3f& in);

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


		// STATIC FUNCTIONS


		/*
			Function: Dot product

			Parameters:

				left - The first vector
				right - The second vector

			Returns:

				The dot product of the vectors

		*/
		static float dot(const Vector3f& left, const Vector3f& right);

		/*
			Function: Normalize

			Parameters:

				in - The vector to normalize

			Returns:

				The input vector normalized

		*/
		static Vector3f& normalize(const Vector3f& in);

		/*
			Function: Cross product

			Parameters:

				left - The first vector
				right - The second vector

			Returns:

				The cross product of the vectors

		*/
		static Vector3f cross(const Vector3f& left, const Vector3f& right);


		/*
			Function: Add

			Parameters:

				left - The first vector to add
				right - The second vector to add

			Returns:

				The vectors added together

		*/
		static Vector3f add(const Vector3f& left, const Vector3f& right);

		/*
			Function: Subtract

			Parameters:

				left - The vector that is subtracted by right
				right - The vector that subtracts from left

			Returns:

				The right vector subracted from the left vector

		*/
		static Vector3f subtract(const Vector3f& left, const Vector3f& right);

		/*
			Function: Multiply

			Parameters:

				left - The first vector to multiplie
				right - The second vector to multiplie

			Returns:

				The vectors multiplied together

		*/
		static Vector3f multiply(const Vector3f& left, const Vector3f& right);

		/*
			Function: Divide

			Parameters:

				left - The vector that is divided by right
				right - The vector that divides left

			Returns:

				This left vector divided by the right vector

		*/
		static Vector3f divide(const Vector3f& left, const Vector3f& right);


		/*
			Function: Overload insertion operator

			Overloads the insertion operator so 3D vector can be printed to the console

		*/
		friend std::ostream& operator<<(std::ostream& stream, const Vector3f& vector);
	
		/*
			Function: Overload addition operator

			Overloads the addition operator so 3D vectors can be added together

		*/
		friend Vector3f operator+(const Vector3f& left, const Vector3f& right);

		/*
			Function: Overload subtraction operator

			Overloads the subtraction operator so 3D vectors can be subtracted from eachother

		*/
		friend Vector3f operator-(const Vector3f& left, const Vector3f& right);

		/*
			Function: Overload multiplication operator

			Overloads the multiplication operator so 3D vectors can be multiplied with eachother

		*/
		friend Vector3f operator*(const Vector3f& left, const Vector3f& right);

		/*
			Function: Overload division operator

			Overloads the division operator so 3D vectors can be divided by eachother

		*/
		friend Vector3f operator/(const Vector3f& left, const Vector3f& right);
	};
}