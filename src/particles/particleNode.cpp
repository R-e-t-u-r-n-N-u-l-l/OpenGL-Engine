#include "particleNode.h"

using namespace engine;

engine::ParticleNode::ParticleNode() : m_particleModel(Shape2D::plane().createModel(true, true)) {}

ParticleNode::ParticleNode(Vector3f position, Vector3f area, Vector3f rotation, Vector3f particleRotation, Vector3f rotationSpread, Vector3f scale, Vector2f scaleMargin,
		Vector3f velocity, Vector3f velocitySpread, float gravity, int life, int pps, GLuint texture) : m_position(position), m_area(area), m_rotation(rotation), 
		m_particleRotation(particleRotation), m_rotationSpread(rotationSpread), m_scale(scale), m_scaleMargin(scaleMargin), m_velocity(velocity), 
		m_velocitySpread(velocitySpread), m_gravity(gravity), m_life(life), m_pps(pps), m_particleModel(Shape2D::plane().createModel(true, true, texture)), m_random(Random()) {}

void ParticleNode::update(float elapsedTime, Vector3f offset) {
	for (size_t i = 0; i < m_particles.size(); i++) {
		if (!m_particles[i]->update()) {
			delete m_particles[i];
			m_particles.erase(m_particles.begin() + i);
		}
	}

	float length = m_pps * elapsedTime;
	m_particalRemainder += fmod(length, 1.0f);

	for (int i = 0; i < length; i++)
		addParticle(offset);

	while (m_particalRemainder >= 1) {
		m_particalRemainder--;
		addParticle(offset);
	}
}

void ParticleNode::render(Shader& shader, const Matrix4f& viewMatrix, int transformationLocation) {
	m_particleModel.bind();
	glBindTexture(GL_TEXTURE_2D, m_particleModel.getTexture());
	for (Particle* p : m_particles) {
		shader.setUniformMatrix4f(transformationLocation, p->createTransformationMatrix(viewMatrix));
		Render::renderNoBind(m_particleModel.getIndexLength());
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	m_particleModel.unbind();
}

void ParticleNode::addParticle(Vector3f offset) {
	Vector3f position = m_position + offset;
	position.x += m_random.next() * m_area.x * 2.0f - m_area.x;
	position.y += m_random.next() * m_area.y * 2.0f - m_area.y;
	position.z += m_random.next() * m_area.z * 2.0f - m_area.z;

	Vector3f rotation = m_particleRotation;
	rotation.x += m_random.next() * m_rotationSpread.x * 2.0f - m_rotationSpread.x;
	rotation.y += m_random.next() * m_rotationSpread.y * 2.0f - m_rotationSpread.y;
	rotation.z += m_random.next() * m_rotationSpread.z * 2.0f - m_rotationSpread.z;

	Vector3f scale = m_scale;
	scale.x += m_random.next() * m_scaleMargin.x * 2.0f - m_scaleMargin.x;
	scale.z += m_random.next() * m_scaleMargin.y * 2.0f - m_scaleMargin.y;
	
	Vector3f velocity = Vector3f(m_velocity.x, m_velocity.y, m_velocity.z);
	velocity.x += m_random.next() * m_velocitySpread.x * 2.0f - m_velocitySpread.x;
	velocity.y += m_random.next() * m_velocitySpread.y * 2.0f - m_velocitySpread.y;
	velocity.z += m_random.next() * m_velocitySpread.z * 2.0f - m_velocitySpread.z;

	Particle* particle = new Particle(position, rotation, scale, velocity, m_gravity, m_life);
	m_particles.push_back(particle);
}
