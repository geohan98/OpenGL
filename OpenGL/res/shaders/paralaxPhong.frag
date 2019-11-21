#version 330 core
out vec4 FragColor;  

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D ourTexture;
uniform sampler2D normalMap;
uniform sampler2D heightMap;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{
	//Parallax Mapping
	vec3 viewDir = normalize(viewPos - FragPos);
	vec2 texCoords = ParallaxMapping(TexCoords,  viewDir);
	//Normal Map
	vec3 normal = texture(normalMap,texCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);
	//Ambient
	vec3 color = texture(ourTexture,texCoords).rgb;
	vec3 ambient = 0.1 * color;
	//Diffuse
	vec3 lightDir = normalize(normalize(lightPos - FragPos));
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * color;
	//Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = spec * vec3(0.2f); 

    FragColor = vec4(ambient + diffuse + specular,1.0f);
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
	float height =  texture(heightMap, texCoords).r;    
    vec2 p = viewDir.xy / viewDir.z * (height * 5);
    return texCoords - p;
}