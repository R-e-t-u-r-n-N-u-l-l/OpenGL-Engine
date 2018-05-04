#include "random.h"

using namespace engine;

// See random.h for documentation

// Initialize pseudo random number generator with given seed, if unspecified it generates a random seed
Random::Random(int seed) {
	if (seed != -1)
		m_seed = seed;
	else
		m_seed = Time::timeMillis();
}

// Generates the next seed and returns a new pseudo random value
float Random::next() {
	m_seed = ((m_seed * a + c) % m);
	return (m_seed / (float) m);
}

// Returns the current seed
long Random::getSeed() const {
	return m_seed;
}

// Returns a pseudo random value with the given seed
float Random::next(long seed) {
	seed = ((seed * a + c) % m);
	return (seed / (float)m);
}

// Returns the new seed that would generate with the given seed
long Random::nextSeed(long seed) {
	seed = ((seed * a + c) % m);
	return seed;
}
