#pragma once

#include <GL\glew.h>

namespace engine {
	class Shadow {

	private:
		GLuint m_shadowMap;
		GLuint m_shadowFBO;
		const int m_size;

	public:
		Shadow(int size);

		const int getSize() const;
		GLuint getShadowMap() const;
		GLuint getShadowFBO() const;

	};
}
