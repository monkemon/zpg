#version 330
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 camera;
uniform vec3 modelColor;

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
	vec3 ic = lightVector + lookDirection;
	vec3 h = (ic) / length(ic);
	vec3 n = normalize(ex_worldNormal);
	float specular = pow(max(dot(n, h), 0.0), 40);

	vec4 Ia = vec4 (0.1 ,0.1 ,0.1 ,1.0);
	vec4 Id = dotLN * lightColor;
	vec4 Is = specular * lightColor;

	if (dot(normalize(ex_worldNormal), lightVector) < 0.0)
	{
		Is = vec4(0.0, 0.0, 0.0, 0.0);
	}

	outColor = ((Ia + Id) * vec4(modelColor, 1.0)) + Is;
};