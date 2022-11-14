#version 330
uniform vec3 camera;

in vec4 ex_worldPosition;
in vec4 ex_worldNormal;

out vec4 out_Color;

void main(void)
{
    vec3 lightPosition= vec3(0.0,0.0,0.0); 

    vec3 vp = vec3(ex_worldPosition.x,ex_worldPosition.y,ex_worldPosition.z);
    vec3 vn = vec3(ex_worldNormal.x, ex_worldNormal.y, ex_worldNormal.z);
    
    vec3 lightVector = lightPosition - vp;

    float dot_product = max(dot(reflect(lightVector, normalize(vn)), camera), 0.0);
    vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    out_Color = ambient;
    //out_Color = vec4(camera, 1.0);
}

//constant
//lambert = constant + diffuse
//blin =  weird phong
//phong = lambert + specular

//constant -> lambert -> phong -> blin