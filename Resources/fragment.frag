#version 330 core

in vec3 UV;

out vec3 color;

uniform sampler2DArray texSampler;

void main(){

	color = texture( texSampler, UV).rgb;
}