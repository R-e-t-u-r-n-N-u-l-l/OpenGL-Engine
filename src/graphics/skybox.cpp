#include "skybox.h"

using namespace engine;

const char* VERTEX_SHADER =
"#version 330 core\n"

"layout(location = 0) in vec3 position;\n"

"out vec3 texCoords;\n"

"uniform mat4 projection;\n"
"uniform mat4 view;\n"

"void main() {\n"
"	gl_Position = projection * view * vec4(position, 1.0);\n"
"	texCoords = position;\n"
"}";

const char* FRAGMENT_SHADER =
"#version 330 core\n"

"layout(location = 0) out vec4 color;\n"
"in vec3 texCoords;\n"
"uniform samplerCube cubeMap;\n"

"void main() {\n"
	"color = texture(cubeMap, texCoords);\n"
"}";

Skybox::Skybox(float size, const char* paths[6]) : m_size(size), m_cubeModel(createCubeMapModel(size)), m_shader(Shader(VERTEX_SHADER, FRAGMENT_SHADER, true)) {
	m_cubeModel.setTexture(File::loadCubeMap(paths));
	m_projectionLocation = m_shader.getUniformLocation("projection");
	m_viewMatrixLocation = m_shader.getUniformLocation("view");
}

void Skybox::render(const Matrix4f& projection, const Vector3f& rotation) {
	m_shader.enable();
	Matrix4f viewMatrix = Maths::createViewMatrix(Vector3f(0.0f), rotation);
	m_shader.setUniformMatrix4f(m_projectionLocation, projection);
	m_shader.setUniformMatrix4f(m_viewMatrixLocation, viewMatrix);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeModel.getTexture());
	m_cubeModel.bind();
	Render::render(m_cubeModel);
	m_cubeModel.unbind();
	m_shader.disable();
}

Model Skybox::createCubeMapModel(float size) {
	GLfloat vertices[] = {
		 size,  size,  size, //0
		 size,  size, -size, //1
		 size, -size, -size, //2
		 size, -size,  size, //3
		-size,  size,  size, //4
		-size,  size, -size, //5
		-size, -size,  size, //6
		-size, -size, -size, //7
	};

	GLuint indices[] = {
		5, 7, 2, 2, 1, 5,
		6, 7, 5, 5, 4, 6,
		2, 3, 0, 0, 1, 2,
		6, 4, 0, 0, 3, 6,
		5, 1, 0, 0, 4, 5,
		7, 6, 2, 2, 6, 3,
	};

	Model model(vertices, indices, 8, 36);

	return engine::Shape3D::cube(size).createModel(false, false);
}
