#version 330 core
out vec4 FragColor;  

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(normalize(lightPos - FragPos));
	float diff = max(dot(normal, lightDir), 0.0);

    FragColor = vec4(vec3(diff),1.0f);
}