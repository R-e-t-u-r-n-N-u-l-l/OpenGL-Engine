#pragma once

#include "../../utilities/stringUtils.h"
#include "../../utilities/fileio.h"
#include "../../window/input.h"
#include "../instancedRender.h"
#include "../render.h"
#include "../shader.h"

#include <vector>

namespace engine {

	struct Character {
		GLfloat* vertices = new GLfloat[8];
		GLfloat* texCoords = new GLfloat[8];
		float xAdvance, height;
		GLuint id;
	};

	class Font {

	private:
		std::vector<Character> m_characters;
		IndexBuffer m_ibo;
		VertexArray m_vao;
		Shader m_shader;
		GLuint m_texture;

		void generateBuffers(const std::string& text, float scale, GLfloat*& vertices, GLfloat*& texCoords, GLuint*& indices);

	public:
		Font(Shader shader, VertexArray vao, const char* texturePath, const char* fontPath);
		Font(const char* texturePath, const char* fontPath);

		void render(const std::string& text, float scale);

		void enableShader();
		void disableShader();

		Character getCharacterById(int id) const;

		Shader& getShader();
		GLuint getTexture() const;
		float getTextWidth(const std::string& text, float scale) const;
		float getTextHeight(const std::string& text, float scale) const;

		void setFont(const char* texturePath, const char* fontPath);
	};
}
