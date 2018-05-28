#pragma once

#define BOUND_AABB 0
#define BOUND_SPHERE 1

#include "../maths/maths.h"
#include "../physics/collision/AABB.h"
#include "../models/model.h"

namespace engine {
	class Entity {

	protected:
		Model m_model;
		Vector3f m_position;
		Vector3f m_rotation;
		Vector3f m_scale;
		AABB m_boundingBox;

		bool m_empty;

	public:
		Entity();
		Entity(Model model);
		Entity(Model model, Vector3f position, Vector3f rotation, Vector3f scale);
		Entity(Vector3f position, Vector3f rotation, Vector3f scale);

		void translate(Vector3f translation);
		void rotate(Vector3f rotation);
		void scale(Vector3f scale);
		void scale(float scale);

		void translate(float x, float y, float z);
		void rotate(float x, float y, float z);
		void scale(float x, float y, float z);

		void bind() const;
		void unbind() const;

		Model getModel() const;
		Vector3f getPosition() const;
		Vector3f getRotation() const;
		Vector3f getScale() const;
		AABB getBoundingBox() const;

		bool isEmpty() const;
		bool collsionWithEntity(const Entity& entity);

		Matrix4f createTransformationMatrix() const;

		void setPosition(Vector3f position);
		void setRotation(Vector3f rotation);
		void setScale(Vector3f scale);
		void setPosition(float x, float y, float z);
		void setRotation(float x, float y, float z);
		void setScale(float x, float y, float z);

		void setModel(Model model);
		void setScale(float scale);
		void setBoundingBox(AABB box);
	};
}
