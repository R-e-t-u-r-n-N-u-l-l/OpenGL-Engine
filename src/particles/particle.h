#pragma once

#include "../maths/maths.h"

namespace engine {

	class Particle {
	
	private:
		Vector3f m_position;
		Vector3f m_rotation;
		Vector3f m_scale;
		Vector3f m_velocity;
		float m_gravity;
		float m_life;
		int m_current;

	public:
		Particle(Vector3f position, Vector3f rotation, Vector3f scale, Vector3f velocity, float gravity, float life);

		virtual bool update();

		virtual void translate(const Vector3f& translation);
		virtual void rotate(const Vector3f& rotation);
		virtual void scale(const Vector3f& scale);
		virtual void accelerate(const Vector3f& velocity);

		virtual void scale(float scale);

		virtual void translate(float x, float y, float z);
		virtual void rotate(float x, float y, float z);
		virtual void scale(float x, float y, float z);
		virtual void accelerate(float x, float y, float z);

		virtual Vector3f getPosition() const;
		virtual Vector3f getRotation() const;
		virtual Vector3f getScale() const;
		virtual Vector3f getVelocity() const;

		virtual float getLife() const;
		virtual float getGravity() const;

		virtual Matrix4f createTransformationMatrix(const Matrix4f& viewMatrix) const;

		virtual void setPosition(Vector3f position);
		virtual void setRotation(Vector3f rotation);
		virtual void setVelocity(Vector3f velocity);
		virtual void setScale(Vector3f scale);
		virtual void setPosition(float x, float y, float z);
		virtual void setRotation(float x, float y, float z);
		virtual void setVelocity(float x, float y, float z);
		virtual void setScale(float x, float y, float z);
		virtual void setScale(float scale);

	};
}
