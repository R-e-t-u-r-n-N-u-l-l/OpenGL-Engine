#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "input.h"

namespace engine {

	class Window {

	private:
		GLFWwindow* m_window;
		int m_width, m_height;
		const char* m_title;
		bool m_fullscreen;

		bool init();

	public:
		Window(int width, int height, const char* title);
		Window(const char* title);
		~Window();
		
		void sync();
		void update();

		void enableDepthTest() const;
		void disableDepthTest() const;
		void enableVSync() const;
		void disableVSync() const;
		void enableTransparancy() const;
		void disableTransparancy() const;
		void lockCursor() const;
		void unlockCursor() const;

		bool isOpen() const;

		int getWidth();
		int getHeight();

		float getAspectRatio();

		GLFWwindow* getWindow() const;

		void setMinVersion(GLuint major, GLuint minor);
	};
}