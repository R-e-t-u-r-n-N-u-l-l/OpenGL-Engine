#pragma once

#include <GL/glew.h>
#include <vector>

#include "../entities/entity.h"
#include "../maths/matrix/matrix4f.h"
#include "../terrain/terrain.h"
#include "instancedRender.h"

namespace engine {

	class Render {

	public:
		static void clear();
		static void renderTerrain(const Terrain& terrain, int chunkSize);

		static void render(const Entity& entity);
		static void render(const Model& model);

		static void renderBatch(InstancedRender& ir, const std::vector<Entity>& entities);
		static void renderBatch(InstancedRender& ir, const Model& model, int length);

		static void enableWireFrame();
		static void disableWireFrame();

		static void enableFaceCulling();
		static void disableFaceCulling();

	};
}