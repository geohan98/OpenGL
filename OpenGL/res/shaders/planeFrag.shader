#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 Color;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform sampler2D normalMap;

void main()
{
	vec3 normal = texture(normalMap, TexCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * Color;
	FragColor = vec4(result, 1.0);
}