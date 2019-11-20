#version 330 core
out vec4 FragColor;  

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	float ambient = 0.05f;
    FragColor = vec4(vec3(ambient),1.0f);
}