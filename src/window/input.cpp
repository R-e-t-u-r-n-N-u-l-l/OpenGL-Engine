#include "input.h"

using namespace engine;

GLFWwindow* Input::m_window;
bool Input::m_keys[MAX_KEYS];
bool Input::m_buttons[MAX_BUTTONS];
double Input::mouseX, Input::mouseY;
double Input::dx, Input::dy;

Input::Input(GLFWwindow* window) {
	m_window = window;
	glfwSetCursorPosCallback(window, mouse_move_callback);
}

Input::~Input() {}

void Input::update() {
	for (int i = 0; i < MAX_KEYS; i++)
		m_keys[i] = keyDown(i);

	for (int i = 0; i < MAX_BUTTONS; i++)
		m_buttons[i] = mouseButtonDown(i);

	dx = 0;
	dy = 0;
}

void Input::mouse_move_callback(GLFWwindow * window, double xPos, double yPos) {
	dx = mouseX - xPos;
	dy = mouseY - yPos;
	mouseX = xPos;
	mouseY = yPos;
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
