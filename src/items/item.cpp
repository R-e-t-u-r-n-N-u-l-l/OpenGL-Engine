#include "item.h"

using namespace engine;

Item::Item(int ID, int texture, int maxAmount) : m_ID(ID), m_texture(texture), m_maxAmount(maxAmount) {}

GLuint Item::getID() const {
	return m_ID;
}

GLuint Item::getTexture() const {
	return m_texture;
}

GLuint Item::getMaxAmount() const {
	return m_maxAmount;
}
