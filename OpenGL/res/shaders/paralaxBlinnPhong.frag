#version 330 core
out vec4 FragColor;  

in vec3 FragPos;
in vec2 TexCoord;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D heightMap;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{
	vec2 texCoord = TexCoord;
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  

	texCoord = ParallaxMapping(TexCoord,  viewDir);
	if(texCoord.x > 1.0 || texCoord.y > 1.0 || texCoord.x < 0.0 || texCoord.y < 0.0) discard;

    vec3 normal = texture(normalMap, texCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    vec3 color = texture(diffuseMap, texCoord).rgb;

    vec3 ambient = 0.1 * color;
   
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = vec3(0.5) * spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
	float height =  texture(heightMap, texCoords).r;    
    vec2 p = viewDir.xy / viewDir.z * (height * 0.03);
    return texCoords - p;
}