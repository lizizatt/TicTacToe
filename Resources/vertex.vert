#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in int texLayer;

out vec3 UV;
uniform mat4 MVP;

void main(){	

	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

	UV = vec3(vertexUV, texLayer);
}