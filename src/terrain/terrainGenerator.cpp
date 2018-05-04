#include "terrainGenerator.h"

using namespace engine;

TerrainGenerator::TerrainGenerator(int chunkSize, int vertexCount, GLuint seed, float amplitude, float smoothingFactor, int octaves) 
	: CHUNK_SIZE(chunkSize), VERTEX_COUNT(vertexCount), m_seed(seed), AMPLITUDE(amplitude), ROUGHNESS(smoothingFactor), OCTAVES(octaves) {

	if (seed == 0)
		m_seed = Time::timeMillis();
}

void TerrainGenerator::render(Shader& shader, int transformationLocation) {
	for (int i = 0; i < m_terrain.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, m_terrain[i].getModel().getTexture());
		shader.setUniformMatrix4f(transformationLocation, m_terrain[i].createTransformationMatrix(m_terrain[i].getX(), m_terrain[i].getZ(), CHUNK_SIZE));
		engine::Render::renderTerrain(m_terrain[i], CHUNK_SIZE);
	}
}

void TerrainGenerator::addTerrain(GLuint texture, int x, int z) {
	m_xOffset = x * (VERTEX_COUNT - 1);
	m_zOffset = z * (VERTEX_COUNT - 1);
	m_terrain.push_back(Terrain(x, z, generateTerrainModel(), texture));
}

float TerrainGenerator::getHeight(float x, float z) {
	Noise noise(m_seed);
	m_xOffset = floor(x / CHUNK_SIZE);
	m_zOffset = floor(z / CHUNK_SIZE);
	return generateHeight(noise, x - m_xOffset, z - m_zOffset);
}

const int TerrainGenerator::getChunkSize() const {
	return CHUNK_SIZE;
}

const int TerrainGenerator::getVertexCount() const {
	return VERTEX_COUNT;
}

Model TerrainGenerator::generateTerrainModel() {
	int count = VERTEX_COUNT * VERTEX_COUNT;

	GLfloat* vertices = new GLfloat[count * 3];
	GLfloat* texCoords = new GLfloat[count * 2];
	GLfloat* normals = new GLfloat[count * 3];
	GLuint* indices = new GLuint[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)];

	Noise noise(m_seed);

	int vertexPointer = 0;
	m_heights.reserve(VERTEX_COUNT);
	for (int i = 0; i < VERTEX_COUNT; i++) {
		std::vector<float> temp;
		temp.reserve(VERTEX_COUNT);
		for (int j = 0; j < VERTEX_COUNT; j++) {
			vertices[vertexPointer * 3] = (float) j / ((float) VERTEX_COUNT - 1) * CHUNK_SIZE;
			vertices[vertexPointer * 3 + 1] = generateHeight(noise, j, i);
			vertices[vertexPointer * 3 + 2] = (float) i / ((float) VERTEX_COUNT - 1) * CHUNK_SIZE;
			texCoords[vertexPointer * 2] = (float) j / ((float) VERTEX_COUNT - 1);
			texCoords[vertexPointer * 2 + 1] = (float) i / ((float) VERTEX_COUNT - 1);
			Vector3f normal = calculateNormal(noise, j, i);
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
			vertexPointer++;
		}
		m_heights.push_back(temp);
	}

	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	int length = 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1);
	Model model(vertices, indices, count * 3, length);
	model.appendBuffer(&Buffer(texCoords, count * 2, 2), 1);
	model.appendBuffer(&Buffer(normals, count * 3, 3), 2);

	delete vertices;
	delete texCoords;
	delete normals;

	return model;
}

Vector3f TerrainGenerator::calculateNormal(Noise noise, float x, float z) const {
	float left  = generateHeight(noise, x - 1, z);
	float right = generateHeight(noise, x + 1, z);
	float back  = generateHeight(noise, x, z - 1);
	float front = generateHeight(noise, x, z + 1);
	Vector3f normal(left - right, 2.0f, back - front);
	normal.normalize();
	return normal;
}

float TerrainGenerator::generateHeight(Noise noise, int x, int z) const {
	float total = 0;
	float d = (float) pow(2, OCTAVES - 1);
	for (int i = 0; i < OCTAVES; i++) {
		float freq = (float) (pow(2, i) / d);
		float amp = (float) pow(ROUGHNESS, i) * AMPLITUDE;
		total += noise.noise2D((x + m_xOffset) * ROUGHNESS, (z + m_zOffset) * ROUGHNESS) * AMPLITUDE * freq;
	}
	return total;
}
