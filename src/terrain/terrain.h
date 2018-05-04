#pragma once

#include "../models/model.h"
#include "../maths/maths.h"

namespace engine {

	class Terrain {

	private:
		const int x, z;

		Model m_model;

	public:
		Terrain(int x, int z, Model model, GLuint texture);

		void bind() const;
		void unbind() const;

		Matrix4f createTransformationMatrix(int x, int z, int chunkSize) const;

		Model getModel() const;

		const int getX() const;
		const int getZ() const;
	};
}
