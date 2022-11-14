#version 330

#define MAX_LIGHTS 10
struct light
{
	vec4 position;
	vec4 diffuse;
};

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 camera;
uniform vec3 modelColor;

uniform light lights[MAX_LIGHTS];

out vec4 outColor;

void main () {

	//I = Ia + Id + Is

    vec4 lightColor = vec4(1, 1, 1, 1.0);

    vec3 lightPosition = vec3 (0.0 ,0.0 ,0.0);

	vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));

	// diffuse
	float d = dot(lightVector , normalize (ex_worldNormal));
	float dotLN = max (d ,0.0);

	// specular
	vec3 lookDirection = normalize(camera - vec3(ex_worldPosition));
	vec3 lightToPixel = normalize(vec3(ex_worldPosition) - lightPosition);
    vec3 reflection = reflect(lightToPixel, normalize(ex_worldNormal));
	float s = dot(reflection, lookDirection);

	// here im setting the h
    float spec = pow(max(s, 0.0), 30);

	vec4 Ia = vec4 (0.1 ,0.1 ,0.1 ,1.0);
	vec4 Id = dotLN * vec4(1.0, 1.0, 1.0, 1.0);
	vec4 Is = spec  * lightColor;

	if (dot(normalize (ex_worldNormal), lightVector) < 0.0)
	{
		Is = vec4(0.0, 0.0, 0.0, 0.0);
	}

	outColor = Ia * vec4(modelColor,1.0) + Id * vec4(modelColor, 1.0) + Is;
};