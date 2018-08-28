#pragma once

#include <vector>

#include "../graphics/render.h"
#include "../graphics/shader.h"
#include "../models/model.h"
#include "../maths/random/random.h"
#include "../utilities/primitives.h"
#include "particle.h"

namespace engine {

	class ParticleNode {

	private:
		std::vector<Particle*> m_particles;
		const Model m_particleModel;
		const Vector3f m_position;
		const Vector3f m_area;
		const Vector3f m_rotation;
		const Vector3f m_particleRotation;
		const Vector3f m_rotationSpread;
		const Vector3f m_scale;
		const Vector2f m_scaleMargin;
		const Vector3f m_velocity;
		const Vector3f m_velocitySpread;
		Random m_random;
		float m_particalRemainder;
		float m_gravity;
		int m_life;
		int m_pps;

		void addParticle(Vector3f offset);

	public:
		ParticleNode();
		ParticleNode(Vector3f position, Vector3f area, Vector3f rotation, Vector3f particleRotation, Vector3f rotationSpread, Vector3f scale, Vector2f scaleMargin, 
					 Vector3f velocity, Vector3f velocitySpread, float gravity, int life, int pps, GLuint texture);

		void update(float elapsedTime, Vector3f offset = 0.0f);

		void render(Shader& shader, const Matrix4f& viewMatrix, int transformationLocation);

	};
}
