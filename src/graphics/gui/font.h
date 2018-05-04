#pragma once

#include "../../utilities/stringUtils.h"
#include "../../utilities/fileio.h"
#include "../render.h"
#include "../shader.h"

#include <vector>

namespace engine {

	struct Character {
		GLfloat* vertices = new GLfloat[8];
		GLfloat* texCoords = new GLfloat[8];
		float xAdvance;
		GLuint id;
	};

	class Font {

	private:
		std::vector<Character> m_characters;
		GLuint m_texture;

	public:
		Font(float scale, const char* texturePath, const char* fontPath);

		void render(std::string text, engine::Shader& shader);

		Model getTextModel(std::string text);

		Character getCharacterById(int id) const;

		void setFont(float scale, const char* texturePath, const char* fontPath);
	};
}
