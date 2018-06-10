#version 330 core

layout (location = 0) in vec3 vertices;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 instances;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transformation;
uniform vec3 lightPosition;

out vec3 normal;
out vec2 coords;
out vec3 lightVector;
out vec3 cameraVector;

void main() {
	vec4 worldPosition = transformation * vec4(vertices + instances, 1.0);
	gl_Position = projection * view * worldPosition;
	coords = texCoords;
	normal = (transformation * vec4(normals, 0.0)).xyz;
	lightVector = lightPosition - worldPosition.xyz;
	cameraVector = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}