#include "window/window.h"
#include "graphics/render.h"
#include "graphics/shader.h"
#include "entities/light.h"
#include "utilities/fileio.h"
#include "models/rawModel.h"
#include "utilities/primitives.h"
#include "terrain/terrainGenerator.h"
#include "entities/camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

int main() {
	engine::Window window(1280, 720, "Engine Demo");
	window.setMinVersion(3, 3);
	window.lockCursor();
	window.enableDepthTest();
	window.enableTransparancy();

	int size = 5;
	engine::Light light(engine::Vector3f(0.0f, 200.0f, 0.0f), engine::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));

	engine::Model model = engine::Shape3D::cube().createModel();

	engine::TerrainGenerator terrain(64, 64, 0, 20.0f, 0.006f, 3);
	for(int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			terrain.addTerrain(engine::File::colorToTexture(0.3f, 0.7f, 0.3f, 1.0f), i, j);

	engine::Shader shader("test.vs", "test.fs");
	shader.enable();

	GLuint transformationLocation = shader.getUniformLocation("transformation");
	
	engine::Entity cube(model);

	engine::Camera camera(engine::Vector3f(0.0f, 2.0f, 0.0f), window.getWidth(), window.getHeight());

	engine::Matrix4f transformation;
	engine::Matrix4f projection = engine::Matrix4f::perspective(70.0f, window.getAspectRatio(), 0.1f, 2000.0f);
	engine::Matrix4f viewMatrix = engine::Maths::createViewMatrix(camera.getPosition(), camera.getRotation());

	engine::Shader terrainShader("testterrain.vs", "testterrain.fs");
	terrainShader.enable();

	GLuint terrainTransformationLocation = terrainShader.getUniformLocation("transformation");
	
	engine::Render::disableFaceCulling();

	float timer = glfwGetTime();
	float lastTime = glfwGetTime();
	float tickAmt = 60.0f;
	float delta = 0;
	int frames = 0;

	while (window.isOpen()) {
		float now = glfwGetTime();
		delta += (now - lastTime) / (1.0f / tickAmt);
		lastTime = now;

		//update
		while (delta >= 1) {
			delta--;

			camera.basicMovement(1.0f);
			viewMatrix = engine::Maths::createViewMatrix(camera.getPosition(), camera.getRotation());

			cube.setPosition(camera.getPosition() + engine::Maths::createRay(camera.getRotation()) * 20.0f);

			window.sync();
		}

		//render
		engine::Render::clear();
		
		terrainShader.enable();
		terrainShader.setUniformMatrix4f(terrainShader.getUniformLocation("view"), viewMatrix);
		terrainShader.setUniformMatrix4f(terrainShader.getUniformLocation("projection"), projection);
		terrainShader.setUniform3f(terrainShader.getUniformLocation("lightPosition"), light.getPosition());
		terrainShader.setUniform4f(terrainShader.getUniformLocation("lightColor"), light.getColor());
		terrain.render(terrainShader, terrainTransformationLocation);
		terrainShader.disable();

		shader.enable();
		shader.setUniformMatrix4f(shader.getUniformLocation("view"), viewMatrix);
		shader.setUniformMatrix4f(shader.getUniformLocation("projection"), projection);
		shader.setUniform3f(shader.getUniformLocation("lightPosition"), light.getPosition());
		shader.setUniform4f(shader.getUniformLocation("lightColor"), light.getColor());
		shader.setUniformMatrix4f(transformationLocation, cube.createTransformationMatrix());
		engine::Render::render(cube);
		shader.disable();

		window.update();
	}

	return 0;
}
