#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../utilities/fileio.h"
#include "input.h"

namespace engine {

	class Window {

	private:
		GLFWwindow* m_window;
		int m_width, m_height;
		const char* m_title;
		bool m_fullscreen;
		GLenum m_prevError;
		float m_tickSpeed, m_lastTime, m_delta;

		bool init(int monitorIndex);

		static void resize_callback(GLFWwindow* window, int width, int height);

	public:
		Window(int width, int height, const char* title, int monitorIndex = 0);
		Window(const char* title, int monitorIndex = 0);
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

		bool isOpen();
		bool canUpdate();

		int getWidth() const;
		int getHeight() const;

		float getTickSpeed() const;

		float getAspectRatio();

		GLFWwindow* getWindow() const;

		void setTickSpeed(float tickSpeed);
		void setIcon(const char** paths, int count);
		void setCursor(const char* path, int xHot, int yHot);
		void setWindowSize(int width, int height);
		void setMinVersion(GLuint major, GLuint minor);

	};
}