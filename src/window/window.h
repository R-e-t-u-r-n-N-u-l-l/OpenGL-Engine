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
		bool m_windowed;
		GLenum m_prevError;
		float m_tickSpeed, m_lastTime, m_delta, m_elapsed, m_updated;

		bool init(int monitorIndex, bool resizable = true);

		static void resize_callback(GLFWwindow* window, int width, int height);

	public:
		Window(int width, int height, const char* title, bool resizable = true, int monitorIndex = 0);
		Window(const char* title, bool windowed = true, int monitorIndex = 0);
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

		float getElapsedTime() const;
		float getTickSpeed() const;
		float getAspectRatio() const;

		GLFWwindow* getWindow() const;

		void setTitle(const char* title);
		void setTickSpeed(float tickSpeed);
		void setIcon(const char** paths, int count);
		void setCursor(const char* path, int xHot, int yHot);
		void setPosition(int x, int y);
		void setWindowSize(int width, int height);
		void setMinVersion(GLuint major, GLuint minor);

	};
}