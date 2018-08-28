#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine {

	class Timer {

	private:
		float m_millis, m_lastTime;

	public:
		Timer(float millis) : m_millis(millis), m_lastTime(glfwGetTime()) {}

		bool ready() {
			float now = glfwGetTime();
			if ((now - m_lastTime) * 1000.0f >= m_millis) {
				m_lastTime = now;
				return true;
			}

			return false;
		}

		void reset() {
			m_lastTime = glfwGetTime();
		}

		float getMillis() const {
			return m_millis;
		}

		void setMillis(float millis) {
			m_millis = millis;
		}

	};
}
