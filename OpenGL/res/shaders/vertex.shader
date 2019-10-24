#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

out vec3 fragColor;

uniform mat4 MVP;

void main()
{
	fragColor = vertexColor;
	gl_Position = MVP *  vec4(position, 1.0);
};