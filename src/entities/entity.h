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
		Vector3f m_size;
		AABB m_boundingBox;

		bool m_empty;

	public:
		Entity();
		Entity(Model model);
		Entity(Model model, Vector3f position, Vector3f rotation, Vector3f scale);
		Entity(Vector3f position, Vector3f rotation, Vector3f scale);

		virtual void translate(Vector3f translation);
		virtual void rotate(Vector3f rotation);
		virtual void scale(Vector3f scale);
		virtual void scale(float scale);

		virtual void translate(float x, float y, float z);
		virtual void rotate(float x, float y, float z);
		virtual void scale(float x, float y, float z);

		virtual void bind() const;
		virtual void unbind() const;

		virtual Model getModel() const;
		virtual Vector3f getPosition() const;
		virtual Vector3f getRotation() const;
		virtual Vector3f getScale() const;
		virtual Vector3f getSize() const;
		virtual AABB getBoundingBox() const;
		 
		virtual bool isEmpty() const;
		virtual bool collsionWithEntity(const Entity& entity);

		virtual void updateBoundingBox();

		virtual Matrix4f createTransformationMatrix() const;

		virtual void setPosition(Vector3f position);
		virtual void setRotation(Vector3f rotation);
		virtual void setScale(Vector3f scale);
		virtual void setSize(Vector3f size);
		virtual void setPosition(float x, float y, float z);
		virtual void setRotation(float x, float y, float z);
		virtual void setScale(float x, float y, float z);
		virtual void setSize(float x, float y, float z);
		
		virtual void setModel(Model model);
		virtual void setScale(float scale);
		virtual void setBoundingBox(AABB box);
	};
}
