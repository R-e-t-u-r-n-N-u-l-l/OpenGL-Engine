#pragma once

#include "../utilities/fileio.h"
#include "../maths/maths.h"

#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>

namespace engine {

	class Shader {

	private:
		GLuint m_shader;

		GLuint load(const char* vSource, const char* fSource);
		bool checkShader(GLuint& shader, std::string type = "");

	public:
		Shader(const char* vertex, const char* fragment, bool raw = false);
		~Shader();

		void enable() const;
		void disable() const;

		GLuint getUniformLocation(const char* uniformName);
		GLuint getAttribLocation(const char* attribName);

		void setUniform1i(GLuint location, int value);
		void setUniform1f(GLuint location, float value);
		void setUniform2f(GLuint location, const engine::Vector2f& vector);
		void setUniform3f(GLuint location, const engine::Vector3f& vector);
		void setUniform4f(GLuint location, const engine::Vector4f& vector);
		void setUniform2f(GLuint location, float x, float y);
		void setUniform3f(GLuint location, float x, float y, float z);
		void setUniform4f(GLuint location, float x, float y, float z, float w);

		void setUniformMatrix4f(GLuint location, const engine::Matrix4f& value);

	};
}
