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

			Casts a ray from (0, 0, 0) with the given rotation

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
			Function: Create ray

			Casts a ray from the given mouse position

			Parameters:

				projectionMatrix - The projection matrix used for the screen
				viewMatrix - The view matrix used for the screen
				mouse - The mouse x and y values in a 2D vector
				screenSize - The screen width and height in a 2D vector

			Returns:

				A ray cast from the mouse position

			Example:

				Vector3f ray = Maths::createRay(projectionMatrix, viewMatrix, Vector2f(314, 159), Vector2f(1280, 720));

		*/
		static Vector3f createRay(const Matrix4f& projectionMatrix, const Matrix4f& viewMatrix, const int mouseX, const int mouseY, const int width, const int height) {
			float mX = mouseX * 2.0f / width - 1.0f;
			float mY = 1.0f - mouseY * 2.0f / height;

			Vector4f clipCoords(mX, mY, -1.0f, 1.0f);
			Matrix4f iProjectionMatrix = Matrix4f::invert(projectionMatrix);
			Vector4f eyeCoords = Vector4f::multiply(iProjectionMatrix, clipCoords);
			eyeCoords = eyeCoords / eyeCoords.w;
			eyeCoords = Vector4f(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
			Matrix4f iViewMatrix = Matrix4f::invert(viewMatrix);
			Vector4f rawRay1 = Vector4f::multiply(viewMatrix, eyeCoords);
			Vector4f rawRay2 = Vector4f::multiply(iViewMatrix, eyeCoords);

			Vector3f ray = rawRay2.xyz();
			ray.normalize();
			return ray;
		}

		static Vector3f createRay(const Matrix4f& projectionMatrix, const Matrix4f& viewMatrix, const Vector2f& mouse, const Vector2f& screenSize) {
			return createRay(projectionMatrix, viewMatrix, mouse.x, mouse.y, screenSize.x, screenSize.y);
		}

		static Vector3f createRay(const Vector3f& cameraLookAt, const Vector3f& cameraPosition, const Vector3f& cameraUp, const double fov, const double nearClip, const int x, const int y, const int width, const int height) {
			float mouseX = x / (width / 2.0f) - 1.0f;
			float mouseY = 1.0f - y / (height / 2.0f);

			Vector3f view = cameraLookAt - cameraPosition;
			view.normalize();

			Vector3f h = Vector3f::cross(view, cameraUp);
			h.normalize();

			Vector3f v = Vector3f::cross(h, view);
			v.normalize();

			const double fovr = fov * M_PI / 180.0f;
			const double vLength = tan(fovr / 2.0f) * nearClip;
			const double hLength = vLength * (width / height);

			v.multiply(vLength);
			h.multiply(hLength);

			Vector3f ray = view * nearClip + h * mouseX + v * mouseY;
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

		/*
			Function: RGB to HSL

			Converts a RGB color format to a HSL color format

			Parameters:

				R - The R value of the RGB color which will be converted
				G - The G value of the RGB color which will be converted
				B - The B value of the RGB color which will be converted

			Returns:

				The RGB color converted to a HSL color

			Example:

				Maths::RGBtoHSL(0.3f, 0.5f, 0.6f);

				HSL will be Vector3f(0.56f, 0.33f, 0.45f);

		*/
		static Vector3f RGBtoHSL(float R, float G, float B) {
			Vector3f HSL;

			float min = Maths::min(R, Maths::min(G, B));
			float max = Maths::max(R, Maths::max(G, B));

			HSL.z = (max + min) / 2.0f;

			if (min == max)
				HSL.y = HSL.x = 0.0f;
			else {
				float d = max - min;
				HSL.y = HSL.z > 0.5f ? d / (2 - max - min) : d / (max + min);

				if (max == R)
					HSL.x = (G - B) / d + (G < B ? 6 : 0);
				else if (max == G)
					HSL.x = (B - R) / d + 2;
				else
					HSL.x = (R - G) / d + 4;

				HSL.x /= 6;
			}

			return HSL;
		}

		/*
			Function: RGB to HSL

			Converts a RGB color format to a HSL color format

			Parameters:

				RGB - The RGB color which will be converted

			Returns:
				
				The RGB color converted to a HSL color

			Example:

				Maths::RGBtoHSL(Vector3f(0.3f, 0.5f, 0.6f));

				HSL will be Vector3f(0.56f, 0.33f, 0.45f);

		*/
		static Vector3f RGBtoHSL(Vector3f RGB) {
			return RGBtoHSL(RGB.x, RGB.y, RGB.z);
		}
	};
}
