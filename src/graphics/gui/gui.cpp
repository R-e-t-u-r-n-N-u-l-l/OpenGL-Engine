#include "gui.h"

using namespace engine;

GUI::GUI() : m_shader(Shader(

//Vertex shader
"#version 330 core\n"

"layout(location = 0) in vec3 position;\n"

"out vec2 texCoords;\n"
"uniform mat4 transformation;\n"

"void main() {\n"
"	gl_Position = transformation * vec4(position.xy, -1.0, 1.0);\n"
"	texCoords = vec2(position.x / 2.0 + 0.5, position.y / -2.0 + 0.5);\n"
"}",

//Fragment shader
"#version 330 core\n"

"layout(location = 0) out vec4 color;\n"

"in vec2 texCoords;\n"
"uniform sampler2D image;\n"

"void main() {\n"
"	color = texture(image, texCoords);\n"
"}", true)), m_transformationLocation(m_shader.getUniformLocation("transformation")), m_model(Shape2D::plane().createModel(false, false)) {}


GUI::GUI(Shader& shader, int transformationLocation) : m_shader(shader), m_transformationLocation(transformationLocation), m_model(Shape2D::plane().createModel(false, false)) {}

void GUI::render() {
	enableShader();
	m_model.bind();

	for (GUIObject* g : m_objects)
		if (g && g->isVisible())
			g->render(m_transformationLocation, m_shader);

	m_model.unbind();
	disableShader();
}

void GUI::render(Model model, GLuint texture, Matrix4f transformation) {
	m_shader.setUniformMatrix4f(m_transformationLocation, transformation);
	glBindTexture(GL_TEXTURE_2D, texture);
	Render::render(model);
}

void GUI::enableShader() {
	m_shader.enable();
}

void GUI::disableShader() {
	m_shader.disable();
}

GUIObject* GUI::getObject(int index) const {
	return m_objects[index];
}

void GUI::addObject(GUIObject* object) {
	m_objects.push_back(object);
}

void GUI::clear() {
	m_objects.clear();
}
