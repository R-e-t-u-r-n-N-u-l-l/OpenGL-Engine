#pragma once

#include <GL/glew.h>
#include <vector>

#include "../buffers/buffer.h"

namespace engine {

	class InstancedRender {

	private:
		std::vector<GLuint> m_attributes;
		std::vector<GLuint> m_vbos;

		GLuint m_vao;

	public:
		InstancedRender(GLuint vao);

		void addInstancedAttribute(GLuint attribute, int dataSize, int maxInstances, int stride, int offset);
		void updateVBO(int index, int dataSize, int instances, GLfloat* data);

		void bind() const;
		void unbind() const;
		
		static GLuint createEmptyVBO(int length);

		int getVBOLength() const;
	};
}
