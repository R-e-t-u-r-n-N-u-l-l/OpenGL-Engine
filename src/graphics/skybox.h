#pragma once

#include "shader.h"
#include "render.h"
#include "../models/model.h"
#include "../utilities/fileio.h"
#include "../utilities/primitives.h"

namespace engine {

	class Skybox {

	private:
		Shader m_shader;
		Model m_cubeModel;
		float m_size;

		int m_projectionLocation;
		int m_viewMatrixLocation;

	public:
		Skybox(float size, const char* paths[6]);
		Skybox(const char* vertex, const char* fragment, int projectionLocation, int viewMatrixLocation, float size, const char* paths[6]);

		void render(const Matrix4f& projection, const Vector3f& rotation);

		static Model createCubeMapModel(float size);

	};
}
