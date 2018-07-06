#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine {

	class Input {

	private:
		static GLFWwindow* m_window;
		static bool m_keys[GLFW_KEY_LAST];
		static bool m_buttons[GLFW_MOUSE_BUTTON_LAST];

		static void mouse_move_callback(GLFWwindow* window, double xPos, double yPos);
		static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

	public:
		static double mouseX, mouseY;
		static double scrollX, scrollY;
		static double mouse_dx, mouse_dy;
		static double scroll_dx, scroll_dy;
		static int width, height;

		Input(GLFWwindow* window);
		~Input();

		static void update();

		static bool mouseMoved();
		
		static bool keyDown(unsigned key);
		static bool keyPressed(unsigned key);
		static bool keyReleased(unsigned key);

		static bool mouseButtonDown(unsigned button);
		static bool mouseButtonPressed(unsigned button);
		static bool mouseButtonReleased(unsigned button);
	};
}