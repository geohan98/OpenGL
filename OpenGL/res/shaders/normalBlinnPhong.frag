#version 330 core
out vec4 FragColor;  

in vec3 FragPos;
in vec2 TexCoord;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

void main()
{
    vec3 normal = texture(normalMap, TexCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
   
    vec3 color = texture(diffuseMap, TexCoord).rgb;

    vec3 ambient = 0.1 * color;

    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = vec3(0.5) * spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}