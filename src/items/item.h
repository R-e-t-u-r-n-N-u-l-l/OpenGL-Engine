#pragma once

#include <GLFW\glfw3.h>

namespace engine {

	class Item {

	private:
		GLuint m_ID;
		GLuint m_texture;
		GLuint m_maxAmount;

	public:
		Item(int ID = 0, int texture = 0, int maxAmount = 1);

		GLuint getID() const;
		GLuint getTexture() const;
		GLuint getMaxAmount() const;

	};
}
