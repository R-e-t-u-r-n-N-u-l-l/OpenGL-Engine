#pragma once

#include "../maths/vector/vector3f.h"
#include "../maths/matrix/matrix4f.h"
#include "../entities/entity.h"
#include "../window/input.h"

#include <GLFW/glfw3.h>

namespace engine {

	class Camera {

	protected:
		Vector3f m_position;
		Vector3f m_rotation;
		int m_width, m_height;

	public:
		Camera(Vector3f position, int width, int height);

		void focusOnEntity(const Entity& entity, const Vector3f& offset, float distance, float rotation);

		void basicMovement(float speed);

		void move(float x, float y, float z);
		void move(Vector3f translation);

		void setPosition(Vector3f position);
		void setRotation(Vector3f rotation);
		void setPitch(float pitch);
		void setYaw(float yaw);
		void setRoll(float roll);

		Vector3f getPosition() const;
		Vector3f getRotation() const;
		float getPitch() const;
		float getYaw() const;
		float getRoll() const;
	};
}
