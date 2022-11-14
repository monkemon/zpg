#version 330

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 modelColor;

out vec4 outColor;

void main () 
{
	// I = Ia + Id

	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

	vec3 lightPosition= vec3(0,0,0);     

	vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));

	float d = dot(lightVector, normalize(ex_worldNormal));
	float dotLN = max(d, 0.0);

	vec4 diffuse = dotLN * lightColor;
	vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
	outColor = (ambient + diffuse) * vec4(modelColor, 1.0);
};