#include "button.h"

using namespace engine;

Button::Button(float x, float y, float width, float height, const GLuint textures[3], const int button) : m_textures(textures), m_button(button),
	engine::GUIObject(x, y, width, height) {
}

bool Button::isHovering() const {
	float x = engine::Input::mouseX;
	float y = engine::Input::mouseY;
	return (x > m_position.x * engine::Input::width && x < (m_position.x + m_scale.x) * engine::Input::width && 
			y > m_position.y * engine::Input::height && y < (m_position.y + m_scale.y) * engine::Input::height);
}

bool Button::isPressed() const {
	return isHovering() && engine::Input::mouseButtonPressed(m_button);
}

bool Button::isReleased() const {
	return isHovering() && engine::Input::mouseButtonReleased(m_button);
}

bool Button::isDown() const {
	return isHovering() && engine::Input::mouseButtonDown(m_button);
}

void Button::render(int transformationLocation, Shader& shader) {
	shader.setUniformMatrix4f(transformationLocation, m_transformation);
	if (m_active || isDown())
		glBindTexture(GL_TEXTURE_2D, m_textures[2]);
	else if(isHovering())
		glBindTexture(GL_TEXTURE_2D, m_textures[1]);
	else
		glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	Render::renderNoBind(6);
}

bool Button::isActive() const {
	return m_active;
}

void Button::setActive(bool active) {
	m_active = active;
}
