#version 330 core
out vec4 FragColor;  

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D ourTexture;

void main()
{
	vec3 normal = normalize(Normal);

	vec3 lightDir = normalize(normalize(lightPos - FragPos));
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir); 

	vec3 color = vec3(0.5f,0.7f,0.2f);

	vec3 ambient = 0.1 * color;

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * color;

	float spec = pow(max(dot(normal, halfwayDir), 0.0), 64);
	vec3 specular = vec3(0.5) * spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}