#include "guiObject.h"

using namespace engine;

GUIObject::GUIObject(GLuint texture, float x, float y, float width, float height) :
	m_transformation(Maths::createTransformationMatrix(Vector3f(x * 2.0f - 1.0f, y * -2.0f + 1.0f, 0.0f), Vector3f(), Vector3f(width, height, 1.0f))), 
	m_model(Shape2D::plane().createModel(false, false, texture)) {}

GUIObject::GUIObject(GLuint texture, float x, float y, Vector2f scale) : GUIObject(texture, x, y, scale.x, scale.y) {}
GUIObject::GUIObject(GLuint texture, Vector2f position, float width, float height) : GUIObject(texture, position.x, position.y, width, height) {}
GUIObject::GUIObject(GLuint texture, Vector2f position, Vector2f scale) : GUIObject(texture, position.x, position.y, scale.x, scale.y) {}

void GUIObject::render(int transformationLocation, Shader& shader) {
	shader.setUniformMatrix4f(transformationLocation, m_transformation);
	glBindTexture(GL_TEXTURE_2D, m_model.getTexture());
	Render::render(m_model);
}
