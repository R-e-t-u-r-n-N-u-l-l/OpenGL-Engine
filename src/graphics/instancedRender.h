#pragma once

#include <GL/glew.h>
#include <vector>

#include "../buffers/vertexArray.h"

namespace engine {

	class InstancedRender {

	private:
		std::vector<GLuint> m_attributes;
		std::vector<GLuint> m_vbos;
		VertexArray m_vao;

	public:
		InstancedRender(VertexArray vao);

		void addInstancedAttribute(GLuint attribute, int dimensions, int maxInstances, int divisor = 1, int stride = 0, int offset = 0);
		void updateAttribute(GLuint index, GLuint dimensions, GLuint instances, GLfloat* data);

		void bind() const;
		void unbind() const;
		
		int getVBOLength() const;

		VertexArray getVAO() const;

		static GLuint createEmptyVBO(GLuint length, GLuint dimensions);

	};
}
