#pragma once

#include <GL/glew.h>
#include <vector>

#include "model.h"
#include "../maths/vector/vector3f.h"

namespace engine {

	class RawModel {

	private:
		std::vector<Vector3f> m_vertices;
		std::vector<Vector3f> m_normals;
		std::vector<Vector2f> m_texCoords;
		std::vector<GLuint> m_indices;

	public:
		void pushVertex(Vector3f vertex);
		void popVertex();
		void setVertex(unsigned int index, Vector3f vertex);
		void removeVertex(unsigned int index);

		void pushNormal(Vector3f normal);
		void popNormal();
		void setNormal(unsigned int index, Vector3f normal);
		void removeNormal(unsigned int index);

		void pushTexCoord(Vector2f texCoord);
		void popTexCoord();
		void setTexCoord(unsigned int index, Vector2f texCoord);
		void removeTexCoord(unsigned int index);

		void pushIndex(int index);
		void popIndex();
		void setIndex(unsigned int i, int index);
		void removeIndex(unsigned int i);

		Vector3f getVertex(int index);
		Vector3f getNormal(int index);
		Vector2f getTexCoord(int index);
		GLuint getIndex(int index);

		Model createModel(bool texCoords = true, bool normals = true, GLuint texture = 0);

		int vertexLength() const;
		int normalLength() const;
		int texCoordLength() const;
		int indexLength() const;

		GLfloat* vertices() const;
		GLfloat* normals() const;
		GLfloat* texCoords() const;
		GLuint* indices() const;
	};
}
