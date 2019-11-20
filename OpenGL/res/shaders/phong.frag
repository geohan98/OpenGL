#version 330 core
out vec4 FragColor;  

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	float ambient = 0.05f;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(normalize(lightPos - FragPos));
	float diff = max(dot(normal, lightDir), 0.0);

	float specularStrength = 0.5;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);  
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	vec3 specular = specularStrength * spec * vec3(1.0f); 
	
	vec3 result = vec3(spec) + vec3(diff) + vec3(ambient);
    FragColor = vec4(result,1.0f);
}