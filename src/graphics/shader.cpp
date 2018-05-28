#include "shader.h"

using namespace engine;

Shader::Shader(const char* vertex, const char* fragment, bool raw) {
	if(raw)
		m_shader = load(vertex, fragment);
	else
		m_shader = load(File::loadFileToString(vertex).c_str(), File::loadFileToString(fragment).c_str());
}

Shader::~Shader() {
	glDeleteProgram(m_shader);
}

GLuint Shader::load(const char* vSource, const char* fSource) {
	GLuint program  = glCreateProgram();
	GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, &vSource, NULL);
	glCompileShader(vertex);

	if (!checkShader(vertex, "vertex"))
		return 0;

	glShaderSource(fragment, 1, &fSource, NULL);
	glCompileShader(fragment);

	if(!checkShader(fragment, "fragment"))
		return 0;

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

bool Shader::checkShader(GLuint& shader, std::string type) {
	GLint status = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		GLint len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		std::vector<char> error(len);
		glGetShaderInfoLog(shader, len, &len, &error[0]);
		std::cout << "Error whilst compiling " << type << " shader: " << std::endl << &error[0] << std::endl;
		glDeleteShader(shader);
		return false;
	}

	return true;
}

void Shader::enable() const {
	glUseProgram(m_shader);
}

void Shader::disable() const {
	glUseProgram(0);
}

GLuint Shader::getUniformLocation(const char* uniformName) {
	GLint location = glGetUniformLocation(m_shader, uniformName);
	if (location == -1)
		std::cout << "Error, can't find uniform: " << uniformName << std::endl;

	return location;
}

GLuint Shader::getAttribLocation(const char* attribName) {
	GLint location = glGetAttribLocation(m_shader, attribName);
	if (location == -1)
		std::cout << "Error, can't find attribute: " << attribName << std::endl;

	return location;
}

void Shader::setUniform1i(GLuint location, int value) {
	glUniform1i(location, value);
}

void Shader::setUniform1f(GLuint location, float value) {
	glUniform1f(location, value);
}

void Shader::setUniform2f(GLuint location, const Vector2f& value) {
	glUniform2f(location, value.x, value.y);
}

void Shader::setUniform3f(GLuint location, const Vector3f& value) {
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setUniform4f(GLuint location, const Vector4f& value) {
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setUniformMatrix4f(GLuint location, const Matrix4f& value) {
	glUniformMatrix4fv(location, 1, GL_FALSE, value.elements);
}
