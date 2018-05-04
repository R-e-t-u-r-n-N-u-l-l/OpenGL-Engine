#pragma once

#include <vector>
#include <string>

#include "../maths/maths.h"
#include "../models/rawModel.h"
#include "stringUtils.h"
#include "fileio.h"

namespace engine {
	class OBJ {

	private:
		static void processIndices(const std::vector<std::string>& vertex, int index, RawModel& rawModel, std::vector<Vector3f>& verticesVector, std::vector<Vector2f>& texCoordsVector, std::vector<Vector3f>& normalsVector) {
			rawModel.pushVertex(verticesVector[std::stoi(vertex[0]) - 1]);
			rawModel.pushTexCoord(texCoordsVector[std::stoi(vertex[1]) - 1]);
			rawModel.pushNormal(normalsVector[std::stoi(vertex[2]) - 1]);
			rawModel.pushIndex(index);
		}

	public:
		static RawModel loadOBJ(const char* path) {
			RawModel rModel;

			std::string file = File::loadFileToString(path);
			std::vector<std::string> lines = String::split(file, '\n');

			std::vector<Vector3f> verticesVector;
			std::vector<Vector2f> texCoordsVector;
			std::vector<Vector3f> normalsVector;
			int index = 0;

			for (std::string line : lines) {
				if (String::startsWith(line, "v ")) {
					std::vector<std::string> elements = String::split(line, ' ');
					Vector3f position(std::stof(elements[1]), std::stof(elements[2]), std::stof(elements[3]));
					verticesVector.push_back(position);
				}
				else if (String::startsWith(line, "vt ")) {
					std::vector<std::string> elements = String::split(line, ' ');
					Vector2f position(std::stof(elements[1]), std::stof(elements[2]));
					texCoordsVector.push_back(position);
				}
				else if (String::startsWith(line, "vn ")) {
					std::vector<std::string> elements = String::split(line, ' ');
					Vector3f position(Vector3f(std::stof(elements[1]), std::stof(elements[2]), std::stof(elements[3])));
					normalsVector.push_back(position);
				} 
				else if (String::startsWith(line, "f ")) {
					std::vector<std::string> elements = String::split(line, ' ');
					for (int i = 1; i < 4; i++)
						processIndices(String::split(elements[i], '/'), index++, rModel, verticesVector, texCoordsVector, normalsVector);
				}
			}

			return rModel;
		}
	};
}