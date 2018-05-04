#include "font.h"

using namespace engine;

Font::Font(float scale, const char* texturePath, const char* fontPath) {
	setFont(scale, texturePath, fontPath);
}

void Font::render(std::string text, engine::Shader& shader) {
	glBindTexture(GL_TEXTURE_2D, m_texture);
	engine::Render::render(getTextModel(text));
}

Model Font::getTextModel(std::string text) {
	GLfloat* vertices = new GLfloat[4 * text.length() * 2];
	GLfloat* texCoords = new GLfloat[4 * text.length() * 2];
	GLuint* indices = new GLuint[6 * text.length()];

	float xAdvance = 0.0f;

	for (int i = 0; i < text.length(); i++) {
		Character c = getCharacterById(int(text[i]));
		for (int j = 0; j < 8; j++) {
			vertices[i * 8 + j] = c.vertices[j] + (j % 2 == 0 ? xAdvance : 0);
			texCoords[i * 8 + j] = c.texCoords[j];
		}
		indices[i * 6 + 0] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4 + 2;
		indices[i * 6 + 4] = i * 4 + 3;
		indices[i * 6 + 5] = i * 4 + 0;

		xAdvance += c.xAdvance;
	}

	Model model(vertices, indices, 4 * text.length() * 2, 6 * text.length(), 2, m_texture);
	Buffer texBuffer(texCoords, 4 * text.length() * 2, 2);

	model.appendBuffer(&texBuffer, 1);

	delete[] vertices;
	delete[] texCoords;
	delete[] indices;

	return model;
}

Character Font::getCharacterById(int id) const {
	for (Character c : m_characters)
		if (c.id == id)
			return c;

	return m_characters[0];
}

void Font::setFont(float scale, const char* texturePath, const char* fontPath) {
	Texture texture = File::loadTexture(texturePath);
	m_texture = texture.getTexture();
	std::string file = engine::File::loadFileToString(fontPath);

	std::vector<std::string> lines = engine::String::split(file, '\n');

	for (std::string line : lines) {
		Character c;
		if (engine::String::startsWith(line, "char ")) {
			std::vector<std::string> elements = engine::String::split(line, ' ');
			c.id = std::stoi(elements[1].substr(3, elements[1].size()));
			int x = std::stoi(elements[2].substr(2, elements[2].size()));
			int y = std::stoi(elements[3].substr(2, elements[3].size()));
			int width = std::stoi(elements[4].substr(6, elements[4].size()));
			int height = std::stoi(elements[5].substr(7, elements[5].size()));
			int xOffset = std::stoi(elements[6].substr(8, elements[6].size()));
			int yOffset = std::stoi(elements[7].substr(8, elements[7].size()));
			c.xAdvance = (std::stof(elements[8].substr(9, elements[8].size())) * scale) / float(texture.getWidth());
			
			c.texCoords[0] = x / float(texture.getWidth());
			c.texCoords[1] = y / float(texture.getHeight());
			c.texCoords[2] = c.texCoords[0];
			c.texCoords[3] = c.texCoords[1] + height / float(texture.getWidth());
			c.texCoords[4] = c.texCoords[0] + width / float(texture.getHeight());
			c.texCoords[5] = c.texCoords[3];
			c.texCoords[6] = c.texCoords[4];
			c.texCoords[7] = c.texCoords[1];

			float vWidth = width / float(texture.getWidth()) * scale;
			float vHeight = -height / float(texture.getHeight()) * scale;
			float v_xOffset = xOffset / float(texture.getWidth()) * scale;
			float v_yOffset = -yOffset / float(texture.getHeight()) * scale;

			c.vertices[0] = v_xOffset;
			c.vertices[1] = v_yOffset;
			c.vertices[2] = v_xOffset;
			c.vertices[3] = vHeight + v_yOffset;
			c.vertices[4] = vWidth + v_xOffset;
			c.vertices[5] = vHeight + v_yOffset;
			c.vertices[6] = vWidth + v_xOffset;
			c.vertices[7] = v_yOffset;

			m_characters.push_back(c);
		}
	}
}
