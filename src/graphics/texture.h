#pragma once

#include <GL/glew.h>

namespace engine {

	class Texture {

	private:
		unsigned char* m_data;
		int m_width, m_height;
		GLuint m_texture;
		GLuint m_type;

	public:
		Texture(unsigned char* data, int width, int heigh, GLuint components = 3);

		GLuint getTexture();
		GLuint getType() const;
		unsigned char* getData() const;
		int getWidth() const;
		int getHeight() const;

	};
}
