#pragma once

#include "../../maths/maths.h"

#include "../shader.h"
#include "../render.h"

namespace engine {

	class GUIObject {

	protected:
		Matrix4f m_transformation;
		Vector2f m_position;
		Vector2f m_scale;
		GLuint m_texture;
		float m_rotation;
		bool m_visible;

		void updateTransformationMatrix();

	public:
		GUIObject(float x, float y, float width, float height, float rotation = 0.0f);
		GUIObject(Vector2f position, Vector2f scale, float rotation = 0.0f);
		GUIObject(GLuint texture, float x, float y, float width, float height, float rotation = 0.0f);
		GUIObject(GLuint texture, Vector2f position, Vector2f scale, float rotation = 0.0f);

		virtual void render(int transformationLocation, Shader& shader);

		Vector2f getPosition() const;
		void setPosition(Vector2f position);
		void setPosition(float x, float y);

		Vector2f getScale() const;
		void setScale(Vector2f scale);
		void setScale(float x, float y);

		float getRotation() const;
		void setRotation(float rotation);

		bool isVisible() const;
		void setVisible(bool visible);

	};
}
