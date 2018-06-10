#pragma once

#include "../../utilities/primitives.h"
#include "../../models/model.h"

#include "../shader.h"
#include "guiObject.h"

namespace engine {

	class GUI {

	private:
		Shader m_shader;
		Model m_model;
		std::vector<GUIObject*> m_objects;
		int m_transformationLocation;

	public:
		GUI();
		GUI(Shader shader, int transformationLocation);

		void render();
		void render(Model model, GLuint texture, Matrix4f transformation);

		void enableShader();
		void disableShader();

		void addObject(GUIObject* object);
		void clear();

	};
}
