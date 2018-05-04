#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine {

#define MAX_KEYS    256
#define MAX_BUTTONS 16

	class Input {

	private:
		static GLFWwindow* m_window;
		static bool m_keys[MAX_KEYS];
		static bool m_buttons[MAX_BUTTONS];

	public:
		static double mouseX, mouseY;
		static double dx, dy;

		Input(GLFWwindow* window);
		~Input();

		static void update();
		
		static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);

		static bool keyDown(unsigned key);
		static bool keyPressed(unsigned key);
		static bool keyReleased(unsigned key);

		static bool mouseButtonDown(unsigned button);
		static bool mouseButtonPressed(unsigned button);
		static bool mouseButtonReleased(unsigned button);
	};
}