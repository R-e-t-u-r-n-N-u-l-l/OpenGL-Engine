#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

#include "vector/vector2f.h"
#include "vector/vector3f.h"
#include "vector/vector4f.h"
#include "matrix/matrix4f.h"

namespace engine {

	/*
		Class: Maths

		A class that contains useful mathematical functions and includes vector and matrix classes
		All functions are static and thus the class doesn't need to be initialized

	*/
	class Maths {

	public:

		/*
			Function: Create transformation matrix

			Constructs a transformation matrix with the given parameters

			Parameters:

				translation - The translation of the transformation matrix
				rotation - The rotation of the transformation matrix
				scale - The scale of the transformation matrix

			Returns:

				A transformation matrix constructed with the given parameters

			Example:
				
				Matrix4f transformationMatrix = Maths::createTransformationMatrix(Vector3f(10.0f, 2.0f, 5.0f), Vector3f(0.0f, M_PI, 0.0f), Vector3f(2.0f));

		*/
		static Matrix4f createTransformationMatrix(const Vector3f& translation, const Vector3f& rotation, const Vector3f& scale) {
			Matrix4f matrix(1.0f);

			matrix.translate(translation);
			matrix.rotate(rotation.x, Vector3f(1.0f, 0.0f, 0.0f));
			matrix.rotate(rotation.y, Vector3f(0.0f, 1.0f, 0.0f));
			matrix.rotate(rotation.z, Vector3f(0.0f, 0.0f, 1.0f));
			matrix.scale(scale);

			return matrix;
		}

		/*
			Function: Create view matrix

			Constructs a view matrix with the given parameters

			Parameters:

				position - The position of the view matrix
				rotation - The rotation of the view matrix

			Returns:

				A view matrix constructed with the given parameters

			Example:

				Matrix4f viewMatrix = Maths::createViewMatrix(Vector3f(3.0f, 5.0f, 3.0f), Vector3f(M_PI / 2.0f, M_PI * 1.5f, 0.0f));

		*/
		static Matrix4f createViewMatrix(const Vector3f& position, const Vector3f& rotation) {
			Matrix4f matrix(1.0f);

			matrix.rotate(rotation.x, Vector3f(1.0f, 0.0f, 0.0f));
			matrix.rotate(rotation.y, Vector3f(0.0f, 1.0f, 0.0f));
			matrix.rotate(rotation.z, Vector3f(0.0f, 0.0f, 1.0f));

			Vector3f pos = Vector3f(-position.x, -position.y, -position.z);
			matrix.translate(pos);

			return matrix;
		}
		
		/*
			Function: Create ray

			Casts a ray with the given rotation

			Parameters:

				rotation - The rotation which the ray will be cast from

			Returns:

				A ray cast from the given rotation

			Example:

				Vector3f ray = Maths::createRay(Vector3f(M_PI / 2.0f));

		*/
		static Vector3f createRay(const Vector3f& rotation) {
			Vector3f ray;
			ray.x = sin(rotation.y) * cos(rotation.x);
			ray.y = -sin(rotation.x);
			ray.z = -cos(rotation.y) * cos(rotation.x);

			ray.normalize();

			return ray;
		}

		/*
			Function: Clamp

			Clamps a value between a minimum and a maximum value

			Parameters:

				value - The input value which will be clamped
				min - The minimum clamp value
				max - The maximum clamp value

			Returns:

				The input value clamped between the minimum and maximum value

			Example:

				float value = Maths::clamp(10.0f, 1.0f, 9.0f);
				
				value will be 9.0f

		*/
		static float clamp(float value, float min, float max) {
			return value < min ? min : (value > max ? max : value);
		}

		/*
			Function: Minimum

			Looks for the minimum value of two numbers

			Parameters:

				a - The first input value
				b - The second input value

			Returns:

				The smallest input value

			Example:

				float min = Maths::min(2.0f, 1.4f);

				min will be 1.4f

		*/
		static float min(float a, float b) {
			return a < b ? a : b;
		}

		/*
			Function: Maximum

			Looks for the maximum value of two numbers

			Parameters:

				a - The first input value
				b - The second input value

			Returns:

				The largest input value

			Example:

				float max = Maths::max(2.0f, 1.4f);

				max will be 2.0f

		*/
		static float max(float a, float b) {
			return a > b ? a : b;
		}
		
		/*
			Function: Map

			Maps a value which is between the first two numbers between the second two other numbers

			Parameters:

				value - The input value
				min1 - The first minimum value
				max1 - The first maximum value
				min2 - The second minimum value
				max2 - The second maximum value

			Returns:

				The mapped value

			Example:

				float value = Maths::map(0.3f, 0.0f, 1.0f, 10.0f, 20.0f);

				value will be 13.0f

		*/
		static float map(float value, float min1, float max1, float min2, float max2) {
			return (value - min1) / (max1 - min1) * (max2 - min2) + min2;
		}

		/*
			Function: Linear inperpolate

			Interpolates a value with linear interpolation

			Parameters:

				current - The current value
				target - The target value
				lerp - The cerp factor 

			Returns:

				The interpolated value

			Example:

				float lerp = Maths::lerp(2.0f, 10.0f, 0.33f);

				lerp will be 4.64f

		*/
		static float lerp(float current, float target, float lerp) {
			return (1 - lerp) * current + lerp * target;
		}

		/*
			Function: Cosine inperpolate

			Interpolates a value with cosine interpolation
			Used for smoother interpolation than linear interpolation

			Parameters:

				current - The current value
				target - The target value
				cerp - The lerp factor

			Returns:

				The interpolated value

			Example:

				float cerp = Maths::cerp(2.0f, 10.0f, 0.33f);

				cerp will be 3.96383f

		*/
		static float cerp(float current, float target, float cerp) {
			float a = (float)(1.0f - cos(cerp * M_PI)) * 0.5f;
			return current * (1.0f - a) + target * a;
		}
	};
}
