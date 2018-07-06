#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>

#include "../graphics/texture.h"
#include "../maths/vector/vector4f.h"
#include "../stb/stb_image.h"

namespace engine {
	namespace File {

		static GLuint dataToTextureID(unsigned char* data, int width, int height, GLuint type = GL_RGB) {
			GLuint textureID;
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			return textureID;
		}

		static GLuint colorToTexture(float r, float g, float b, float a) {
			unsigned char* color = new unsigned char[4];
			color[0] = (int)(r * 255);
			color[1] = (int)(g * 255);
			color[2] = (int)(b * 255);
			color[3] = (int)(a * 255);

			return dataToTextureID(color, 1, 1, GL_RGBA);
		}

		static GLuint colorToTexture(Vector4f color) {
			return colorToTexture(color.x, color.y, color.z, color.w);
		}

		static GLuint loadTextureID(const char* path) {
			int w, h, n;
			unsigned char* data = stbi_load(path, &w, &h, &n, 0);

			if (!data)
				fprintf(stderr, "Cant load image: %s\n", path);

			GLuint type = GL_RGBA;

			switch (n) {
				case 1:
					type = GL_RED;
					break;
				case 2:
					type = GL_RG;
					break;
				case 3:
					type = GL_RGB;
					break;
			}

			return dataToTextureID(data, w, h, type);
		}

		static Texture loadTexture(const char* path) {
			int w, h, n;
			unsigned char* data = stbi_load(path, &w, &h, &n, 0);

			if (!data)
				fprintf(stderr, "Cant load image: %s\n", path);

			return Texture(data, w, h, n);
		}

		static GLFWimage loadGLFWimage(const char* path) {
			int w, h, n;
			unsigned char* data = stbi_load(path, &w, &h, &n, 0);

			if (!data)
				fprintf(stderr, "Cant load image: %s\n", path);

			GLFWimage image;

			image.width = w;
			image.height = h;
			image.pixels = data;

			return image;
		}

		// Right, Left, Top, Bottom, Back, Front
		static GLuint loadCubeMap(const char* paths[6]) {
			GLuint textureID;
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

			for (int i = 0; i < 6; i++) {
				Texture texture = loadTexture(paths[i]);

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, texture.getType(), texture.getWidth(), texture.getHeight(), 0, texture.getType(), GL_UNSIGNED_BYTE, texture.getData());
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			return textureID;
		}

		static std::string loadFileToString(const char* path) {
			std::string line, content = "";
			std::ifstream file(path);

			if (file.is_open()) {
				while (std::getline(file, line))
					content += line + "\n";
			}
			else
				fprintf(stderr, "Cant find file: %s\n", path);

			file.close();

			return content;
		}

		static void appendToFile(const char* path, const char* str) {
			std::ofstream file(path, std::ios_base::app);

			if (file.is_open())
				file << str;

			file.close();
		}

		static void clearFile(const char* path) {
			std::ofstream file(path, std::ofstream::out | std::ofstream::trunc);
			file.close();
		}

	}
}
