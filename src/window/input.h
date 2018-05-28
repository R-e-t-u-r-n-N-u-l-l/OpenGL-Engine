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
		static double scrollX, scrollY;
		static double mouse_dx, mouse_dy;
		static double scroll_dx, scroll_dy;

		Input(GLFWwindow* window);
		~Input();

		static void update();
		
		static void mouse_move_callback(GLFWwindow* window, double xPos, double yPos);
		static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

		static bool keyDown(unsigned key);
		static bool keyPressed(unsigned key);
		static bool keyReleased(unsigned key);

		static bool mouseButtonDown(unsigned button);
		static bool mouseButtonPressed(unsigned button);
		static bool mouseButtonReleased(unsigned button);
	};
}