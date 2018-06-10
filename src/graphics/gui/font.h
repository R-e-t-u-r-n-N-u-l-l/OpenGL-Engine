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
		float xAdvance, width;
		GLuint id;
	};

	class Font {

	private:
		std::vector<Character> m_characters;
		IndexBuffer m_ibo;
		VertexArray m_vao;
		Shader m_shader;
		GLuint m_texture;

		void generateBuffers(const std::string& text, GLfloat*& vertices, GLfloat*& texCoords, GLuint*& indices);

	public:
		Font(Shader shader, float scale, VertexArray vao, const char* texturePath, const char* fontPath);
		Font(float scale, const char* texturePath, const char* fontPath);

		void render(const std::string& text);

		void enableShader();
		void disableShader();

		Character getCharacterById(int id) const;

		Shader& getShader();
		float getTextWidth(const std::string& text) const;

		void setFont(float scale, const char* texturePath, const char* fontPath);
	};
}
