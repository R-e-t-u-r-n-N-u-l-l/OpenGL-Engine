#include "font.h"

using namespace engine;

Font::Font(Shader shader, float scale, VertexArray vao, const char* texturePath, const char* fontPath) :
	m_shader(shader), m_vao(vao), m_ibo(IndexBuffer(new GLuint[6]{ 0, 1, 2, 3, 4, 5 }, 6)) {

	setFont(scale, texturePath, fontPath);
}

Font::Font(float scale, const char* texturePath, const char* fontPath) : m_shader(Shader(

	//Vertex shader
	"#version 330 core\n"

	"layout(location = 0) in vec2 position;\n"
	"layout(location = 1) in vec2 texCoords;\n"

	"out vec2 coords;\n"

	"uniform vec2 location;\n"

	"void main() {\n"
	"	gl_Position = vec4(position + location * vec2(2.0, -2.0) + vec2(-1.0, 1.0), -1.0, 1.0);\n"
	"	coords = texCoords;\n"
	"}",

	//Fragment shader
	"#version 330 core\n"

	"layout(location = 0) out vec4 color;\n"

	"in vec2 coords;\n"

	"uniform vec3 textColor;\n"
	"uniform vec3 borderColor;\n"
	"uniform sampler2D image;\n"

	"void main() {\n"
	"	vec4 raw = texture(image, coords);\n"
	"	color = vec4((1.0 - raw.x) * borderColor + raw.x * textColor, raw.a);\n"
	"}", true)), m_ibo(IndexBuffer(1500)) {

	m_vao.append(0, InstancedRender::createEmptyVBO(1000, 2), 2);
	m_vao.append(1, InstancedRender::createEmptyVBO(1000, 2), 2);

	setFont(scale, texturePath, fontPath);
}

void Font::render(const std::string& text) {
	GLfloat* vertices = new GLfloat[4 * text.length() * 2];
	GLfloat* texCoords = new GLfloat[4 * text.length() * 2];
	GLuint* indices = new GLuint[6 * text.length()];

	generateBuffers(text, vertices, texCoords, indices);

	m_ibo.update(6 * text.length(), indices);
	m_vao.bind();
	m_ibo.bind();
	m_vao.updateBuffer(0, 2, 4 * text.length(), vertices);
	m_vao.updateBuffer(1, 2, 4 * text.length(), texCoords);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	engine::Render::renderNoBind(6 * text.length());
	m_ibo.unbind();
	m_vao.unbind();

	delete[] vertices;
	delete[] texCoords;
	delete[] indices;
}

void Font::enableShader() {
	m_shader.enable();
}

void Font::disableShader() {
	m_shader.disable();
}

void Font::generateBuffers(const std::string& text, GLfloat*& vertices, GLfloat*& texCoords, GLuint*& indices) {
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
}

Character Font::getCharacterById(int id) const {
	for (Character c : m_characters)
		if (c.id == id)
			return c;

	return m_characters[0];
}

Shader& Font::getShader() {
	return m_shader;
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
