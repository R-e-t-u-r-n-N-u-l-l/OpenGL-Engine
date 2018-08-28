#pragma once

#include "../../window/input.h"
#include "guiObject.h"
#include "../render.h"

namespace engine {

	class Button : public GUIObject {

	private:
		const GLuint* m_textures;
		const int m_button;
		bool m_active;

	public:
		Button(float x, float y, float width, float height, const GLuint textures[3], const int button = 0);

		bool isHovering() const;
		bool isPressed() const;
		bool isReleased() const;
		bool isDown() const;

		void render(int transformationLocation, Shader& shader) override;

		bool isActive() const;

		void setActive(bool active);

	};
}
