#pragma once

#include "../shader.h"
#include "guiObject.h"

namespace engine {

	class GUI {

	private:
		Shader m_shader;
		std::vector<GUIObject> m_objects;
		int m_transformationLocation;

	public:
		GUI();
		GUI(const char* vertex, const char* fragment, int transformationLocation);

		void render();
		void render(Model model, GLuint texture, Matrix4f transformation);

		void enableShader();
		void disableShader();

		void addObject(GUIObject object);
		void clear();

	};
}
