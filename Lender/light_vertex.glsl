#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

out vec4 ex_worldPosition;
out vec4 ex_worldNormal;

void main(void){
    
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(vp,1.0f);
    ex_worldPosition = modelMatrix * vec4(vp,1.0f);
    ex_worldNormal = normalMatrix * vec4(vn, 1.0);
}