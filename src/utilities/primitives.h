#pragma once

#include "../maths/maths.h"
#include "../models/rawModel.h"
#include <iostream>

namespace engine {
	namespace Shape2D {
		static RawModel plane(float width = 1.0f, float height = 1.0f, bool flipHorizontalTexCoords = false) {
			engine::RawModel rModel;
			rModel.pushVertex(Vector3f(-width, -height, 0.0f));
			rModel.pushVertex(Vector3f(width, -height, 0.0f));
			rModel.pushVertex(Vector3f(width, height, 0.0f));
			rModel.pushVertex(Vector3f(-width, height, 0.0f));
							  
			rModel.pushNormal(Vector3f(0.0f, 1.0f, 0.0f));
			rModel.pushNormal(Vector3f(0.0f, 1.0f, 0.0f));
			rModel.pushNormal(Vector3f(0.0f, 1.0f, 0.0f));
			rModel.pushNormal(Vector3f(0.0f, 1.0f, 0.0f));

			float a = flipHorizontalTexCoords ? 1.0f : 0.0f;

			rModel.pushTexCoord(Vector2f(a, 0.0f));
			rModel.pushTexCoord(Vector2f(1.0f - a, 0.0f));
			rModel.pushTexCoord(Vector2f(1.0f - a, 1.0f));
			rModel.pushTexCoord(Vector2f(a, 1.0f));

			rModel.pushIndex(0);
			rModel.pushIndex(1);
			rModel.pushIndex(2);
			rModel.pushIndex(2);
			rModel.pushIndex(3);
			rModel.pushIndex(0);

			return rModel;
		}

		static RawModel regularPolygon(unsigned int n, float rotation = 0.0f) {
			RawModel rModel;
			rModel.pushVertex(engine::Vector3f(0.0f, 0.0f, 0.0f));

			for(unsigned int i = 0; i <= n; i++) {
				float angle = Maths::map((float) i, 0.0f, n, 0.0f, (float) (2.0f * M_PI)) + rotation;
				float x = cos(angle);
				float y = sin(angle);
				rModel.pushVertex(engine::Vector3f(x, y, 0.0f));
				rModel.pushIndex(0);
				rModel.pushIndex(i);
				rModel.pushIndex(i == n ? 1 : i + 1);
			}

			return rModel;
		}
	}

	namespace Shape3D {
		static RawModel cube(float size = 1.0f) {
			engine::RawModel rModel;

			rModel.pushVertex(engine::Vector3f(-size, -size, size));
			rModel.pushVertex(engine::Vector3f(size, -size, size));
			rModel.pushVertex(engine::Vector3f(size, size, size));
			rModel.pushVertex(engine::Vector3f(-size, size, size));
			rModel.pushVertex(engine::Vector3f(-size, -size, -size));
			rModel.pushVertex(engine::Vector3f(-size, size, -size));
			rModel.pushVertex(engine::Vector3f(size, size, -size));
			rModel.pushVertex(engine::Vector3f(size, -size, -size));
			rModel.pushVertex(engine::Vector3f(-size, size, -size));
			rModel.pushVertex(engine::Vector3f(-size, size, size));
			rModel.pushVertex(engine::Vector3f(size, size, size));
			rModel.pushVertex(engine::Vector3f(size, size, -size));
			rModel.pushVertex(engine::Vector3f(-size, -size, -size));
			rModel.pushVertex(engine::Vector3f(size, -size, -size));
			rModel.pushVertex(engine::Vector3f(size, -size, size));
			rModel.pushVertex(engine::Vector3f(-size, -size, size));
			rModel.pushVertex(engine::Vector3f(size, -size, -size));
			rModel.pushVertex(engine::Vector3f(size, size, -size));
			rModel.pushVertex(engine::Vector3f(size, size, size));
			rModel.pushVertex(engine::Vector3f(size, -size, size));
			rModel.pushVertex(engine::Vector3f(-size, -size, -size));
			rModel.pushVertex(engine::Vector3f(-size, -size, size));
			rModel.pushVertex(engine::Vector3f(-size, size, size));
			rModel.pushVertex(engine::Vector3f(-size, size, -size));

			rModel.pushTexCoord(engine::Vector2f(0.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 1.0f));
			rModel.pushTexCoord(engine::Vector2f(1.0f, 0.0f));
			rModel.pushTexCoord(engine::Vector2f(0.0f, 0.0f));

			rModel.pushNormal(engine::Vector3f(0.0f, 0.0f, 1.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 0.0f, 1.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 0.0f, 1.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 0.0f, 1.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 0.0f, -1.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 0.0f, -1.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 0.0f, -1.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 0.0f, -1.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 1.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 1.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 1.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, 1.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, -1.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, -1.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, -1.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(0.0f, -1.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(1.0f, 0.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(1.0f, 0.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(1.0f, 0.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(1.0f, 0.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(-1.0f, 0.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(-1.0f, 0.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(-1.0f, 0.0f, 0.0f));
			rModel.pushNormal(engine::Vector3f(-1.0f, 0.0f, 0.0f));

			rModel.pushIndex(0); 
			rModel.pushIndex(1);
			rModel.pushIndex(2);
			rModel.pushIndex(0);
			rModel.pushIndex(2);
			rModel.pushIndex(3);
			rModel.pushIndex(4);
			rModel.pushIndex(5);
			rModel.pushIndex(6);
			rModel.pushIndex(4);
			rModel.pushIndex(6);
			rModel.pushIndex(7);
			rModel.pushIndex(8);
			rModel.pushIndex(9);
			rModel.pushIndex(10);
			rModel.pushIndex(8);
			rModel.pushIndex(10);
			rModel.pushIndex(11);
			rModel.pushIndex(12);
			rModel.pushIndex(13);
			rModel.pushIndex(14);
			rModel.pushIndex(12);
			rModel.pushIndex(14);
			rModel.pushIndex(15);
			rModel.pushIndex(16);
			rModel.pushIndex(17);
			rModel.pushIndex(18);
			rModel.pushIndex(16);
			rModel.pushIndex(18);
			rModel.pushIndex(19);
			rModel.pushIndex(20);
			rModel.pushIndex(21);
			rModel.pushIndex(22);
			rModel.pushIndex(20);
			rModel.pushIndex(22);
			rModel.pushIndex(23);

			return rModel;
		}

		static RawModel uvSphere(unsigned int n, float rotation = 0.0f) {
			RawModel rModel;

			for (unsigned int i = 0; i <= n; i++) {
				float lat = Maths::map(float(i), 0.0f, float(n), float(M_PI / -2.0f), float(M_PI / 2.0f)) + rotation;
				for (unsigned int j = 0; j <= n; j++) {
					float lon = Maths::map(float(j), 0.0f, float(n), float(-M_PI), float(M_PI)) + rotation;
					float x = sin(lon) * cos(lat);
					float y = sin(lon) * sin(lat);
					float z = cos(lon);
					rModel.pushVertex(Vector3f(x, y, z));
					rModel.pushNormal(Vector3f(x, y, z));
				}
			}

			for (unsigned int i = 0; i <= n; i++) {
				for (unsigned int j = 0; j <= n; j++) {
					rModel.pushIndex(j + n * i);
					rModel.pushIndex(j + n * (i + 1));
					rModel.pushIndex(j + 1 + n * (i + 1));
					rModel.pushIndex(j + 1 + n * i);
					rModel.pushIndex(j + n * i);
					rModel.pushIndex(j + 1 + n * (i + 1));
				}
			}

			return rModel;
		}
	}
}