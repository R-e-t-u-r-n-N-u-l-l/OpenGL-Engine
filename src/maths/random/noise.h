#pragma once

#include <vector>

#include "../maths.h"
#include "random.h"

namespace engine {

	/*
		Class: Noise

		A class that generates 2D, 3D or 4D perlin-like simplex noise
		Original code for the noise, derived from:
		http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
		Reference to functions and parameters can be found on this pdf

	*/
	class Noise {


	private:

		/*
			Variable: m_perm

			An array of permutations

		*/
		int* m_perm;

		/*
			Variable: m_grad3

			3D gradient

		*/
		const int m_grad3[12][3] = {{1, 1, 0 }, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, {1, 0, 1}, {-1, 0, 1},
									{1, 0, -1}, {-1, 0, -1}, {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}};

		/*
			Variable: m_grad4

			4D gradient

		*/
		const int m_grad4[32][4] = {{0, 1, 1, 1}, {0, 1, 1, -1}, {0, 1, -1, 1}, { 0, 1, -1, -1}, {0, -1, 1, 1}, {0, -1, 1, -1}, {0, -1, -1, 1}, {0, -1, -1, -1},
									{1, 0, 1, 1}, {1, 0, 1, -1}, {1, 0, -1, 1}, {1, 0, -1, -1}, {-1, 0, 1, 1}, {-1, 0,1,-1}, {-1, 0, -1, 1}, {-1, 0, -1, -1},
									{1, 1, 0, 1}, {1, 1, 0, -1}, {1, -1, 0, 1}, {1, -1, 0, -1}, {-1, 1, 0, 1}, {-1, 1, 0, -1}, {-1, -1, 0, 1}, {-1, -1, 0, -1},
									{1, 1, 1, 0}, {1, 1, -1, 0}, {1, -1, 1, 0}, {1, -1, -1, 0}, {-1, 1, 1, 0}, {-1, 1, -1, 0}, {-1, -1, 1, 0}, {-1, -1, -1, 0}};

		/*
			Variable: m_simplex

			Lookup table to traverse the simplex around a given point in 4D

		*/
		const int m_simplex[64][4] = {{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 0, 0, 0}, {0, 2, 3, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 2, 3, 0},
									  {0, 2, 1, 3}, {0, 0, 0, 0}, {0, 3, 1, 2}, {0, 3, 2, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 3, 2, 0},
									  {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
									  {1, 2, 0, 3}, {0, 0, 0, 0}, {1, 3, 0, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {2, 3, 0, 1}, {2, 3, 1, 0},
									  {1, 0, 2, 3}, {1, 0, 3, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {2, 0, 3, 1}, {0, 0, 0, 0}, {2, 1, 3, 0},
									  {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
									  {2, 0, 1, 3}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {3, 0, 1, 2}, {3, 0, 2, 1}, {0, 0, 0, 0}, {3, 1, 2, 0},
									  {2, 1, 0, 3}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {3, 1, 0, 2}, {0, 0, 0, 0}, {3, 2, 0, 1}, {3, 2, 1, 0}};

		/*
			Function: Fast floor
	
			A faster floor function
	
			Parameters:
				
				value - The value to floor
	
			Returns:
	
				The input value floored
	
		*/
		int fastFloor(float value);
		
		/*
			Function: 2D dot product

			Creates the dot product between two 2D vectors

			Parameters:

				g - The first vector, should be 4 in length
				x - The x value of the second vector
				y - The y value of the second vector

			Returns:

				The dot product between the two vectors

		*/
		float dot(const int g[], float x, float y);
		
		/*
			Function: 3D dot product

			Creates the dot product between two 3D vectors

			Parameters:

				g - The first vector, should be 3 in length
				x - The x value of the second vector
				y - The y value of the second vector
				z - The z value of the second vector

			Returns:

				The dot product between the two vectors

		*/
		float dot(const int g[], float x, float y, float z);

		/* 
			Function: 4D dot product

			Creates the dot product between two 4D vectors

			Parameters:

				g - The first vector, should be 4 in length
				x - The x value of the second vector
				y - The y value of the second vector
				z - The z value of the second vector
				w - The w value of the second vector

			Returns:
				
				The dot product between the two vectors

		*/
		float dot(const int g[], float x, float y, float z, float w);

	public:

		/*
			Constructor: Noise

			Initializes the permuation list with the given seed

			Parameters:
				
				seed - Optional seed value for the noise, if unspecified it generates a random seed

		*/
		Noise(int seed = -1);

		/* 
			Function: 2D simplex noise
			
			Generates 2D simplex noise

			Parameters:
				
				x - The x position of the noise
				y - The y position of the noise

			Returns:
				
				A noise value at the given 2D location between -1 and 1

		*/
		float noise2D(float x, float y);
		
		/*
			Function: 3D simplex noise

			Generates 3D simplex noise

			Parameters:

				x - The x position of the noise
				y - The y position of the noise
				z - The z position of the noise

			Returns:

				A noise value at the given 3D location between -1 and 1

		*/
		float noise3D(float x, float y, float z);
		
		/*
			Function: 4D simplex noise

			Generates 4D simplex noise

			Parameters:

				x - The x position of the noise
				y - The y position of the noise
				z - The z position of the noise
				w - The w position of the noise

			Returns:

				A noise value at the given 4D location between -1 and 1

		*/
		float noise4D(float x, float y, float z, float w);
	
	};
}
