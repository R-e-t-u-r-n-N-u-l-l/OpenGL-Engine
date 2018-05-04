#include "texture.h"
#include "../utilities/fileio.h"

using namespace engine;

Texture::Texture(unsigned char* data, int width, int height, GLuint components) : m_data(data), m_width(width), m_height(height), m_texture(0) {
	switch (components) {
		case 1:
			m_type = GL_RED;
			break;
		case 2:
			m_type = GL_RG;
			break;
		case 3:
			m_type = GL_RGB;
			break;
		case 4:
			m_type = GL_RGBA;
			break;
	}
}

GLuint engine::Texture::getTexture() {
	if (m_texture == 0)
		m_texture = File::dataToTextureID(m_data, m_width, m_height, m_type);

	return m_texture;
}

GLuint Texture::getType() const {
	return m_type;
}

unsigned char* Texture::getData() const {
	return m_data;
}

int Texture::getWidth() const {
	return m_height;
}

int Texture::getHeight() const {
	return m_width;
}
