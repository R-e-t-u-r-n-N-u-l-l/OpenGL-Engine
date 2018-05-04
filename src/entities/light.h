#pragma once

#include "../maths/vector/vector3f.h"
#include "entity.h"

namespace engine {

	class Light : public Entity {

	private:
		Vector4f m_color;

	public:
		Light(Vector3f position, Vector4f color);

		void setColor(Vector4f color);

		Vector4f getColor() const;
	};
}
