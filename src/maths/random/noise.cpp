#include "noise.h"

using namespace engine;

// See noise.h for documentation

Noise::Noise(int seed) {
	// Initialize pseudo random number generator with given seed, if unspecified it generates a random seed
	Random random(seed);

	int* p = new int[256];
	// Generate pseudo random numbers
	for (int i = 0; i < 256; i++)
		p[i] = int(random.next() * 255);

	m_perm = new int[512];
	// Put pseudo random numbers in an array of permutations
	for (int i = 0; i < 512; i++) 
		m_perm[i] = p[i & 255];
}

// Faster floor function
int Noise::fastFloor(float value) {
	return value > 0 ? int(value) : int(value) - 1;
}

// 2D dot product
float Noise::dot(const int g[], float x, float y) {
	return g[0] * x + g[1] * y;
}

// 3D dot product
float Noise::dot(const int g[], float x, float y, float z) {
	return g[0] * x + g[1] * y + g[2] * z;
}

// 4D dot product
float Noise::dot(const int g[], float x, float y, float z, float w) {
	return g[0] * x + g[1] * y + g[2] * z + g[3] * w;
}

// 2D simplex noise
float Noise::noise2D(float x, float y) {
	float n0, n1, n2; 
	const float F2 = 0.5f * (sqrt(3.0f) - 1.0f);
	float s = (x + y) * F2;
	int i = fastFloor(x + s);
	int j = fastFloor(y + s);
	const float G2 = (3.0f - sqrt(3.0f)) / 6.0f;
	float t = (i + j) * G2;
	float X0 = i - t;
	float Y0 = j - t;
	float x0 = x - X0;
	float y0 = y - Y0;

	int i1, j1;
	if (x0 > y0) { i1 = 1; j1 = 0; } 
	else { i1 = 0; j1 = 1; }

	float x1 = x0 - i1 + G2;
	float y1 = y0 - j1 + G2;
	float x2 = x0 - 1.0f + 2.0f * G2;
	float y2 = y0 - 1.0f + 2.0f * G2;

	int ii = i & 255;
	int jj = j & 255;
	int gi0 = m_perm[ii + m_perm[jj]] % 12;
	int gi1 = m_perm[ii + i1 + m_perm[jj + j1]] % 12;
	int gi2 = m_perm[ii + 1 + m_perm[jj + 1]] % 12;

	float t0 = 0.5f - x0 * x0 - y0 * y0;
	if (t0 < 0) n0 = 0.0f;
	else {
		t0 *= t0;
		n0 = t0 * t0 * dot(m_grad3[gi0], x0, y0);
	}

	float t1 = 0.5f - x1 * x1 - y1 * y1;
	if (t1 < 0) n1 = 0.0f;
	else {
		t1 *= t1;
		n1 = t1 * t1 * dot(m_grad3[gi1], x1, y1);
	}

	float t2 = 0.5 - x2 * x2 - y2 * y2;
	if (t2 < 0) n2 = 0.0;
	else {
		t2 *= t2;
		n2 = t2 * t2 * dot(m_grad3[gi2], x2, y2);
	}

	return 70.0f * (n0 + n1 + n2);
}

// 3D simplex noise
float Noise::noise3D(float x, float y, float z) {
	float n0, n1, n2, n3;
	const float F3 = 1.0f / 3.0f;
	float s = (x + y + z) * F3;
	int i = fastFloor(x + s);
	int j = fastFloor(y + s);
	int k = fastFloor(z + s);
	const float G3 = 1.0f / 6.0f;
	float t = (i + j + k) * G3;
	float X0 = i - t;
	float Y0 = j - t;
	float Z0 = k - t;
	float x0 = x - X0;
	float y0 = y - Y0;
	float z0 = z - Z0;

	int i1, j1, k1;
	int i2, j2, k2;
	if (x0 >= y0) {
		if (y0 >= z0) { i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 1; k2 = 0; }
		else if (x0 >= z0) { i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 0; k2 = 1; }
		else { i1 = 0; j1 = 0; k1 = 1; i2 = 1; j2 = 0; k2 = 1; }
	}
	else {
		if (y0 < z0) { i1 = 0; j1 = 0; k1 = 1; i2 = 0; j2 = 1; k2 = 1; }
		else if (x0 < z0) { i1 = 0; j1 = 1; k1 = 0; i2 = 0; j2 = 1; k2 = 1; }
		else { i1 = 0; j1 = 1; k1 = 0; i2 = 1; j2 = 1; k2 = 0; }
	}

	float x1 = x0 - i1 + G3;
	float y1 = y0 - j1 + G3;
	float z1 = z0 - k1 + G3;
	float x2 = x0 - i2 + 2.0f * G3;
	float y2 = y0 - j2 + 2.0f * G3;
	float z2 = z0 - k2 + 2.0f * G3;
	float x3 = x0 - 1.0f + 3.0f * G3;
	float y3 = y0 - 1.0f + 3.0f * G3;
	float z3 = z0 - 1.0f + 3.0f * G3;

	int ii = i & 255;
	int jj = j & 255;
	int kk = k & 255;
	int gi0 = m_perm[ii + m_perm[jj + m_perm[kk]]] % 12;
	int gi1 = m_perm[ii + i1 + m_perm[jj + j1 + m_perm[kk + k1]]] % 12;
	int gi2 = m_perm[ii + i2 + m_perm[jj + j2 + m_perm[kk + k2]]] % 12;
	int gi3 = m_perm[ii + 1 + m_perm[jj + 1 + m_perm[kk + 1]]] % 12;

	float t0 = 0.5f - x0 * x0 - y0 * y0 - z0 * z0;
	if (t0 < 0) n0 = 0.0f;
	else {
		t0 *= t0;
		n0 = t0 * t0 * dot(m_grad3[gi0], x0, y0, z0);
	}

	float t1 = 0.6f - x1 * x1 - y1 * y1 - z1 * z1;
	if (t1 < 0) n1 = 0.0f;
	else {
		t1 *= t1;
		n1 = t1 * t1 * dot(m_grad3[gi1], x1, y1, z1);
	}

	float t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2;
	if (t2 < 0) n2 = 0.0f;
	else {
		t2 *= t2;
		n2 = t2 * t2 * dot(m_grad3[gi2], x2, y2, z2);
	}

	float t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3;
	if (t3 < 0) n3 = 0.0f;
	else {
		t3 *= t3;
		n3 = t3 * t3 * dot(m_grad3[gi3], x3, y3, z3);
	}

	return 32.0f * (n0 + n1 + n2 + n3);
}

// 4D m_simplex noise
float Noise::noise4D(float x, float y, float z, float w) {
	const float F4 = (sqrt(5.0f) - 1.0f) / 4.0f;
	const float G4 = (5.0f - sqrt(5.0f)) / 20.0f;
	float n0, n1, n2, n3, n4;
	float s = (x + y + z + w) * F4;
	int i = fastFloor(x + s);
	int j = fastFloor(y + s);
	int k = fastFloor(z + s);
	int l = fastFloor(w + s);
	float t = (i + j + k + l) * G4;
	float X0 = i - t;
	float Y0 = j - t;
	float Z0 = k - t;
	float W0 = l - t;
	float x0 = x - X0;
	float y0 = y - Y0;
	float z0 = z - Z0;
	float w0 = w - W0;

	int c1 = (x0 > y0) ? 32 : 0;
	int c2 = (x0 > z0) ? 16 : 0;
	int c3 = (y0 > z0) ? 8 : 0;
	int c4 = (x0 > w0) ? 4 : 0;
	int c5 = (y0 > w0) ? 2 : 0;
	int c6 = (z0 > w0) ? 1 : 0;
	int c = c1 + c2 + c3 + c4 + c5 + c6;
	int i1, j1, k1, l1;
	int i2, j2, k2, l2;
	int i3, j3, k3, l3;

	i1 = m_simplex[c][0] >= 3 ? 1 : 0;
	j1 = m_simplex[c][1] >= 3 ? 1 : 0;
	k1 = m_simplex[c][2] >= 3 ? 1 : 0;
	l1 = m_simplex[c][3] >= 3 ? 1 : 0;

	i2 = m_simplex[c][0] >= 2 ? 1 : 0;
	j2 = m_simplex[c][1] >= 2 ? 1 : 0;
	k2 = m_simplex[c][2] >= 2 ? 1 : 0;
	l2 = m_simplex[c][3] >= 2 ? 1 : 0;

	i3 = m_simplex[c][0] >= 1 ? 1 : 0;
	j3 = m_simplex[c][1] >= 1 ? 1 : 0;
	k3 = m_simplex[c][2] >= 1 ? 1 : 0;
	l3 = m_simplex[c][3] >= 1 ? 1 : 0;

	float x1 = x0 - i1 + G4;
	float y1 = y0 - j1 + G4;
	float z1 = z0 - k1 + G4;
	float w1 = w0 - l1 + G4;
	float x2 = x0 - i2 + 2.0f * G4;
	float y2 = y0 - j2 + 2.0f * G4;
	float z2 = z0 - k2 + 2.0f * G4;
	float w2 = w0 - l2 + 2.0f * G4;
	float x3 = x0 - i3 + 3.0f * G4;
	float y3 = y0 - j3 + 3.0f * G4;
	float z3 = z0 - k3 + 3.0f * G4;
	float w3 = w0 - l3 + 3.0f * G4;
	float x4 = x0 - 1.0f + 4.0f * G4; 
	float y4 = y0 - 1.0f + 4.0f * G4;
	float z4 = z0 - 1.0f + 4.0f * G4;
	float w4 = w0 - 1.0f + 4.0f * G4;
	
	int ii = i & 255;
	int jj = j & 255;
	int kk = k & 255;
	int ll = l & 255;
	int gi0 = m_perm[ii + m_perm[jj + m_perm[kk + m_perm[ll]]]] % 32;
	int gi1 = m_perm[ii + i1 + m_perm[jj + j1 + m_perm[kk + k1 + m_perm[ll + l1]]]] % 32;
	int gi2 = m_perm[ii + i2 + m_perm[jj + j2 + m_perm[kk + k2 + m_perm[ll + l2]]]] % 32;
	int gi3 = m_perm[ii + i3 + m_perm[jj + j3 + m_perm[kk + k3 + m_perm[ll + l3]]]] % 32;
	int gi4 = m_perm[ii + 1 + m_perm[jj + 1 + m_perm[kk + 1 + m_perm[ll + 1]]]] % 32;

	float t0 = 0.5f - x0 * x0 - y0 * y0 - z0 * z0 - w0 * w0;
	if (t0 < 0)
		n0 = 0.0f;
	else {
		t0 *= t0;
		n0 = t0 * t0 * dot(m_grad4[gi0], x0, y0, z0, w0);
	}

	float t1 = 0.6f - x1 * x1 - y1 * y1 - z1 * z1 - w1 * w1;
	if (t1 < 0) 
		n1 = 0.0f;
	else {
		t1 *= t1;
		n1 = t1 * t1 * dot(m_grad4[gi1], x1, y1, z1, w1);
	}

	float t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2 - w2 * w2;
	if (t2 < 0)
		n2 = 0.0f;
	else {
		t2 *= t2;
		n2 = t2 * t2 * dot(m_grad4[gi2], x2, y2, z2, w2);
	}

	float t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3 - w3 * w3;
	if (t3 < 0)
		n3 = 0.0f;
	else {
		t3 *= t3;
		n3 = t3 * t3 * dot(m_grad4[gi3], x3, y3, z3, w3);
	}

	float t4 = 0.6f - x4 * x4 - y4 * y4 - z4 * z4 - w4 * w4;
	if (t4 < 0)
		n4 = 0.0f;
	else {
		t4 *= t4;
		n4 = t4 * t4 * dot(m_grad4[gi4], x4, y4, z4, w4);
	}

	return 27.0f * (n0 + n1 + n2 + n3 + n4);
}
