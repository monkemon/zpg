#version 330
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 camera;
uniform vec3 modelColor;

out vec4 outColor;

void main () {

	//I
	outColor = vec4(modelColor, 1.0);
};

