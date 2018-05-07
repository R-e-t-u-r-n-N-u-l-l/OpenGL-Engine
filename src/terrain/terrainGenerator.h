#pragma once

#include <vector>

#include "../maths/maths.h"
#include "../models/model.h"
#include "../maths/random/noise.h"
#include "../utilities/time.h"
#include "terrain.h"
#include "../graphics/render.h"
#include "../graphics/shader.h"

namespace engine {

	class TerrainGenerator {

	private:
		const int CHUNK_SIZE;
		const int VERTEX_COUNT;
		const int OCTAVES;
		const float AMPLITUDE;
		const float ROUGHNESS;

		long m_seed;

		int m_xOffset, m_zOffset;

		std::vector<Terrain> m_terrain;
		std::vector<std::vector<float>> m_heights;

		Model generateTerrainModel();
		Vector3f calculateNormal(Noise noise, float x, float z) const;
		float generateHeight(Noise noise, int x, int z) const;

	public:
		TerrainGenerator(int chunkSize = 128, int vertexCount = 64, int seed = 0, float heightFactor = 10.0f, float roughness = 0.2f, int octaves = 1);

		void render(Shader& shader, int transformationLocation);

		void addTerrain(GLuint texture, int x, int z);

		float getHeight(float x, float z);

		const int getChunkSize() const;
		const int getVertexCount() const;
	};
}
