#include "input.h"

using namespace engine;

GLFWwindow* Input::m_window;
bool Input::m_keys[GLFW_KEY_LAST];
bool Input::m_buttons[GLFW_MOUSE_BUTTON_LAST];
double Input::mouseX, Input::mouseY;
double Input::scrollX, Input::scrollY;
double Input::mouse_dx, Input::mouse_dy;
double Input::scroll_dx, Input::scroll_dy;
int Input::width, Input::height;

Input::Input(GLFWwindow* window) {
	m_window = window;
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

Input::~Input() {}

void Input::update() {
	for (int i = 0; i < GLFW_KEY_LAST; i++)
		m_keys[i] = keyDown(i);

	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		m_buttons[i] = mouseButtonDown(i);

	mouse_dx = 0;
	mouse_dy = 0;
	scroll_dx = 0;
	scroll_dy = 0;
}

bool Input::mouseMoved() {
	return mouse_dx != 0 || mouse_dy != 0;
}

void Input::mouse_move_callback(GLFWwindow* window, double xPos, double yPos) {
	mouse_dx = mouseX - xPos;
	mouse_dy = mouseY - yPos;
	mouseX = xPos;
	mouseY = yPos;
}

void Input::scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	scroll_dx = scrollX + xOffset;
	scroll_dy = scrollY + yOffset;
	scrollX = xOffset;
	scrollY = yOffset;
}

bool Input::keyDown(unsigned key) {
	return glfwGetKey(m_window, key) != GLFW_RELEASE;
}

bool Input::keyPressed(unsigned key) {
	return (keyDown(key) && !m_keys[key]);
}

bool Input::keyReleased(unsigned key) {
	return (!keyDown(key) && m_keys[key]);
}

bool Input::mouseButtonDown(unsigned button) {
	return glfwGetMouseButton(m_window, button) != GLFW_RELEASE;
}

bool Input::mouseButtonPressed(unsigned button) {
	return (mouseButtonDown(button) && !m_buttons[button]);
}

bool Input::mouseButtonReleased(unsigned button) {
	return (!mouseButtonDown(button) && m_buttons[button]);
}
