#version 330 core

layout(location = 0) out vec4 color;

in vec3 fragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{
	color = vec4(fragColor,1.0f);
};