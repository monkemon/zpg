#version 330

#define MAX_LIGHTS 10

struct pointLight
{
	vec4 position;
	vec3 attenuation;
};
struct dirLight
{
	vec3 direction;
	vec3 ads;
};
struct spotLight
{
	vec4 position;
	vec3 attenuation;
	vec3 direction;
	float cutoff;
	float outerCutoff;
};

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 camera;
uniform vec3 modelColor;

uniform int pointLightCount;
uniform int dirLightCount;
uniform int spotLightCount;

uniform pointLight Plights[MAX_LIGHTS];
uniform dirLight Dlights[MAX_LIGHTS];
uniform spotLight Slights[MAX_LIGHTS];

out vec4 outColor;

float attenuation(float c, float l, float q, float dist);

vec3 calculateDirLight(dirLight d, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(pointLight p, vec3 normal, vec3 viewDir, vec3 pixelPos);
vec3 calculateSpotLight(spotLight s, vec3 normal, vec3 viewDir, vec3 pixelPos);


void main () 
{
	vec3 totalLight;

	vec3 lookDir = normalize(camera - vec3(ex_worldPosition));

	vec3 norm_normal = normalize(ex_worldNormal);

	// phong shader for direction lights
	for(int i = 0; i < dirLightCount; i++)
	{
		totalLight += calculateDirLight(Dlights[i], norm_normal, lookDir);
	}

	// phong shader for point lights
	for(int i = 0; i < pointLightCount; i++)
	{
		totalLight += calculatePointLight(Plights[i], norm_normal, lookDir, ex_worldPosition.xyz);
	}

	// phong shader for spot lights
	for (int i = 0; i < spotLightCount; i++)
	{
		totalLight += calculateSpotLight(Slights[i], norm_normal, lookDir, ex_worldPosition.xyz);
	}

	totalLight += vec3(0.03, 0.03, 0.03) * modelColor;

	outColor = vec4(totalLight, 1.0);
};

float attenuation(float c, float l, float q, float dist)
{
	float att = 1 / ( c + ( l * dist ) + ( q * dist * dist ));
	return max(att, 0.0);
}

vec3 calculateDirLight(dirLight d, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-(d.direction.xyz));

	// diffuse
	float diff = max(dot(lightDir, normal), 0.0);

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 40);

    vec3 diffuse  = diff * vec3(1.0, 1.0, 1.0) * modelColor * d.ads.y;
    vec3 specular = spec * vec3(1.0, 1.0, 1.0) * d.ads.z;

	if (dot(normal, lightDir) < 0.0)
	{
		specular *= 0;
	}

    return (diffuse + specular);
}

vec3 calculatePointLight(pointLight p, vec3 normal, vec3 viewDir, vec3 pixelPos)
{
	vec3 lightDir = normalize(p.position.xyz - pixelPos);
	
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 40);
	float attenuation = attenuation(p.attenuation.x,
		p.attenuation.y,
		p.attenuation.z,
		length(p.position.xyz - pixelPos));

	vec3 diffuse = diff * vec3(1.0, 1.0, 1.0) * modelColor;
	vec3 specular = spec * vec3(1.0, 1.0, 1.0);
	diffuse *= attenuation;
	specular *= attenuation;


	if (dot(normal, lightDir) < 0.0)
	{
		specular *= 0;
	}

	return (diffuse + specular);
}

vec3 calculateSpotLight(spotLight s, vec3 normal, vec3 viewDir, vec3 pixelPos)
{
	vec3 lightDir = normalize(s.position.xyz - pixelPos);

	float theta = dot(lightDir, normalize(-s.direction));
	float epsilon = s.cutoff - s.outerCutoff;
	float intensity = clamp((theta - s.outerCutoff) / epsilon, 0.0, 1.0);

	if (theta > s.outerCutoff)
	{
		// lambert
		float diff = max(dot(normal, lightDir), 0.0);

		// phong
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 40);
		float attenuation = attenuation(s.attenuation.x,
			s.attenuation.y,
			s.attenuation.z,
			length(s.position.xyz - pixelPos));

		vec3 diffuse = diff * vec3(1.0, 1.0, 1.0) * modelColor;
		vec3 specular = spec * vec3(1.0, 1.0, 1.0);

		diffuse *= attenuation;
		specular *= attenuation;

		diffuse *= intensity;
		specular *= intensity;

		if (dot(normal, lightDir) < 0.0)
		{
			specular *= 0;
		}

		return (diffuse + specular);
	}
	else
	{
		return vec3(0, 0, 0);
	}
}
