#pragma once

#include <GL/glew.h>

namespace engine {

	class Texture {

	private:
		unsigned char* m_data;
		int m_width, m_height;
		GLuint m_id;
		GLuint m_type;

	public:
		Texture();
		Texture(unsigned char* data, int width, int heigh, GLuint components = 3);

		void bind();
		void unbind();

		GLuint getID();
		GLuint getType() const;
		unsigned char* getData() const;
		int getWidth() const;
		int getHeight() const;

	};
}
