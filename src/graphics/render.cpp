#include "render.h"

using namespace engine;

void Render::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::renderTerrain(const Terrain& terrain, int chunkSize) {
	terrain.bind();
	glDrawElements(GL_TRIANGLES, terrain.getModel().getIndexLength(), GL_UNSIGNED_INT, 0);
	terrain.unbind();
}

void Render::render(const Entity& entity) {
	glBindTexture(GL_TEXTURE_2D, entity.getModel().getTexture());
	entity.bind();
	glDrawElements(GL_TRIANGLES, entity.getModel().getIndexLength(), GL_UNSIGNED_INT, 0);
	entity.unbind();
}

void Render::render(const Model& model) {
	model.bind();
	glDrawElements(GL_TRIANGLES, model.getIndexLength(), GL_UNSIGNED_INT, 0);
	model.unbind();
}

void Render::renderNoBind(int indexLength) {
	glDrawElements(GL_TRIANGLES, indexLength, GL_UNSIGNED_INT, 0);
}

void Render::renderBatch(InstancedRender& ir, const std::vector<Entity>& entities) {
	entities[0].bind();
	ir.bind();
	glDrawElementsInstanced(GL_TRIANGLES, entities[0].getModel().getIndexLength(), GL_UNSIGNED_INT, 0, entities.size());
	ir.unbind();
	entities[0].unbind();
}

void Render::renderBatch(InstancedRender& ir, const Model& model, int amount) {
	model.bind();
	ir.bind();
	glDrawElementsInstanced(GL_TRIANGLES, model.getIndexLength(), GL_UNSIGNED_INT, 0, amount);
	ir.unbind();
	model.unbind();
}

void Render::renderBatchNoBind(int indexLength, int amount) {
	glDrawElementsInstanced(GL_TRIANGLES, indexLength, GL_UNSIGNED_INT, 0, amount);
}

void Render::enableWireFrame() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Render::disableWireFrame() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Render::enableFaceCulling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Render::disableFaceCulling() {
	glDisable(GL_CULL_FACE);
}
