#pragma once

#include <iostream>

namespace engine {

	/*
		Class: Vector2f

		A class that represents a 2D vector

	*/
	class Vector2f {

	public:

		/*
			Variable: x

			The x value of the vector

			Variable: y

			The y value of the vector

		*/
		float x, y;


		/*
			Constructor: Vector2f

			Initializes the 2D vector as (0, 0)

		*/
		Vector2f();

		/*
			Constructor: Vector2f

			Initializes the 2D vector as (xy, xy)

			Parameters:

				xy - The value on every axis of the vector

		*/
		Vector2f(float xy);

		/*
			Constructor: Vector2f

			Initializes the 2D vector as (x, y)

			Parameters:

				x - The x value of the vector
				y - The y value of the vector

		*/
		Vector2f(float x, float y);


		/*
			Function: Add

			Parameters:

				in - The vector to add to this vector

			Returns:

				The vectors added together

		*/
		Vector2f& add(const Vector2f& in);

		/*
			Function: Subtract

			Parameters:

				in - The vector to subract from this vector

			Returns:

				The other vector subracted from this vector

		*/
		Vector2f& subtract(const Vector2f& in);

		/*
			Function: Multiply

			Parameters:

				in - The vector to multiplie with this vector

			Returns:

				The vectors multiplied together

		*/
		Vector2f& multiply(const Vector2f& in);

		/*
			Function: Divide

			Parameters:

				in - The vector to divide this by

			Returns:

				This vector divided by the other vector

		*/
		Vector2f& divide(const Vector2f& in);


		/*
			Function: Add

			Parameters:

				x - The x value of the vector to add to this vector
				y - The y value of the vector to add to this vector

			Returns:

				The vectors added together

		*/
		Vector2f& add(float x, float y);

		/*
			Function: Subtract

			Parameters:

				x - The x value of the vector to substract from this vector
				y - The y value of the vector to substract from this vector

			Returns:

				The other vector subracted from this vector

		*/
		Vector2f& subtract(float x, float y);

		/*
			Function: Multiply

			Parameters:

				x - The x value of the vector to multiplie with this vector
				y - The y value of the vector to multiplie with this vector

			Returns:

				The vectors multiplied together

		*/
		Vector2f& multiply(float x, float y);

		/*
			Function: Divide

			Parameters:

				x - The x value of the vector to divide this by
				y - The y value of the vector to divide this by

			Returns:

				This vector divided by the other vector

		*/
		Vector2f& divide(float x, float y);


		/*
			Function: Equals

			Compares this vector and another vector and checks if they are equal

			Parameters:

				in - The vector that should be compared with this vector

			Returns:
				
				True if the vectors are equal otherwise false

		*/
		bool equals(const Vector2f& in);


		/*
			Function: Dot product

			Creates the dot product of this vector and another vector

			Parameters:

				in - The other vector

			Returns:

				The dot product of the vectors

		*/
		float dot(const Vector2f& in);

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


		// STATIC FUNCTIONS

		/*
			Function: Dot product

			Parameters:

				left - The first vector
				right - The second vector

			Returns:

				The dot product of the vectors

		*/
		static float dot(const Vector2f& left, const Vector2f& right);

		/*
			Function: Normalize

			Parameters:

				in - The vector to normalize

			Returns:

				The input vector normalized

		*/
		static Vector2f& normalize(const Vector2f& in);


		/*
			Function: Add

			Parameters:

				left - The first vector to add
				right - The second vector to add

			Returns:

				The vectors added together

		*/
		static Vector2f add(Vector2f left, const Vector2f& right);

		/*
			Function: Subtract

			Parameters:

				left - The vector that is subtracted by right
				right - The vector that subtracts from left

			Returns:

				The right vector subracted from the left vector

		*/
		static Vector2f subtract(Vector2f left, const Vector2f& right);
	
		/*
			Function: Multiply

			Parameters:

				left - The first vector to multiplie
				right - The second vector to multiplie

			Returns:

				The vectors multiplied together

		*/
		static Vector2f multiply(Vector2f left, const Vector2f& right);

		/*
			Function: Divide

			Parameters:

				left - The vector that is divided by right
				right - The vector that divides left

			Returns:

				This left vector divided by the right vector

		*/
		static Vector2f divide(Vector2f left, const Vector2f& right);


		/*
			Function: Overload insertion operator

			Overloads the insertion operator so 2D vector can be printed to the console

		*/
		friend std::ostream& operator<<(std::ostream& stream, const Vector2f& vector);

		/*
			Function: Overload addition operator

			Overloads the addition operator so 2D vectors can be added together

		*/
		friend Vector2f operator+(const Vector2f& left, const Vector2f& right);

		/*
			Function: Overload subtraction operator

			Overloads the subtraction operator so 2D vectors can be subtracted from eachother

		*/
		friend Vector2f operator-(const Vector2f& left, const Vector2f& right);

		/*
			Function: Overload multiplication operator

			Overloads the multiplication operator so 2D vectors can be multiplied with eachother

		*/
		friend Vector2f operator*(const Vector2f& left, const Vector2f& right);

		/*
			Function: Overload division operator

			Overloads the division operator so 2D vectors can be divided by eachother

		*/
		friend Vector2f operator/(const Vector2f& left, const Vector2f& right);
	};
}