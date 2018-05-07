#pragma once

#include "../../utilities/primitives.h"
#include "../../maths/maths.h"
#include "../../models/model.h"
#include "../shader.h"
#include "../render.h"

namespace engine {

	class GUIObject {

	private:
		Matrix4f m_transformation;
		Model m_model;

	public:
		GUIObject(GLuint texture, float x, float y, float width, float height);
		GUIObject(GLuint texture, float x, float y, Vector2f scale);
		GUIObject(GLuint texture, Vector2f position, Vector2f scale);
		GUIObject(GLuint texture, Vector2f position, float width, float height);

		void render(int transformationLocation, Shader& shader);

	};
}
