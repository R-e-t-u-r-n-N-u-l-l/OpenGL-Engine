#version 330 core

layout (location = 0) out vec4 color;

in vec3 normal;
in vec2 coords;
in vec3 lightVector;
in vec3 cameraVector;

uniform vec4 lightColor;
uniform sampler2D image;

void main() {
	float damper = 10.0;
	float reflective = 1.0;

	vec3 unitNormal = normalize(normal);
	vec3 unitVector = normalize(lightVector);
	vec3 unitCamera = normalize(cameraVector);
	vec3 lightDirection = -unitVector;
	vec3 reflection = reflect(lightDirection, unitNormal);

	float specular = dot(reflection, unitCamera);
	specular = max(specular, 0.0);
	float dampening = pow(specular, damper);
	vec4 finalSpecular = dampening * lightColor;

	float dotProduct = dot(unitNormal, unitVector);
	float brightness = max(dotProduct, 0.2);
	vec4 diffuse = brightness * reflective * lightColor;

	vec4 raw = diffuse * texture(image, vec2(coords.x, 1.0 - coords.y));

	color = vec4(raw.xyz, 1.0);
}