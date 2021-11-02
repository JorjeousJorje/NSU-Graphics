#version 430
struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform Material material;

struct DirectedLightSource
{
    vec3 direction;
    vec4 color;   
    float intensity;
};

struct PointLightSource
{
    vec3 position;
    vec4 color;   
    float intensity;
};

uniform PointLightSource point_lights[10];
uniform int point_lightsCount;
uniform DirectedLightSource directed_lights[10];
uniform int directed_lightsCount;

uniform highp mat4 model;
uniform highp mat4 normal_matrix;
uniform highp mat4 view;
uniform highp mat4 projection;
uniform vec3 cameraPos;

uniform sampler2D t0; // grass
uniform sampler2D t1; // rock
uniform sampler2D t2; // rock 2
uniform sampler2D t3; // snow
uniform sampler2D t4; // mud

uniform float hMin;
uniform float hMax;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in vec3 MeanNormal;

float attenuation(float dist)
{
   return 1.0f / (1.0f + 0.01f * dist + 0.01f * dist * dist);
}

vec3 process_directed_lights(vec3 norm, vec3 viewDir)
{
    vec3 result = vec3(0);
    for (int i = 0; i < directed_lightsCount; ++i) {
        vec3 lightDir = normalize(-directed_lights[i].direction);

        float diff = max(dot(lightDir, norm), 0.0);
        vec3 diffuse =  diff * vec3(material.diffuse);

        result += vec3(directed_lights[i].color) * diffuse;
    }
    return result;
}

vec3 process_point_lights(vec3 norm, vec3 viewDir)
{
    vec3 result = vec3(0);
    for (int i = 0; i < point_lightsCount; ++i) {
        vec3 lightDir = normalize(point_lights[i].position - FragPos);

        float diff = max(dot(norm, lightDir), 0.f);
        vec3 diffuse =   diff * vec3(material.diffuse);

        float _distance = length(FragPos - point_lights[i].position);

        result += vec3(point_lights[i].color) * diffuse* attenuation(_distance);
    }
    return result;
}


vec3 calculate_lighting()
{
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 norm = normalize(Normal);
    
    // Фоновая составляющая
    vec3 result = 0.089f * vec3(material.ambient);
    result += process_directed_lights(norm, viewDir);
    result += process_point_lights(norm, viewDir);

    return result;
}

out vec4 FragColor;

void main()
{
    vec3 PhongColor = calculate_lighting();

    vec3 cGrass = texture(t0, TexCoords.xy).rgb;
	vec3 cRock = texture(t1, TexCoords.xy).rgb;
	vec3 cRock2 = texture(t2, TexCoords.xy).rgb;
	vec3 cSnow = texture(t3, TexCoords.xy).rgb;
	vec3 cMud = texture(t4, TexCoords.xy).rgb;

    float h = FragPos.y;

    vec3 color = vec3(0.0f);
    cGrass = mix(cGrass, cMud, 0.4).rgb;

    float grass_level = hMin + hMax / 2.5;

    float rock_level = hMax - hMax / 2;

    float cos_tetha = max(dot(MeanNormal, vec3(1, 1, 1)), 0.f) / length(MeanNormal);

    color = cRock;
    if(h < 0) {
        float a = smoothstep(hMin, 0, h);
        color = mix(cGrass, cRock, a).rgb;
    } else if(h < rock_level) {
        float a = smoothstep(0, rock_level, h);
        color = mix(cRock, cRock2, a).rgb;
    } else {
        float a = smoothstep(rock_level, hMax, h);
        color = mix(cRock2, cSnow, 3 * a).rgb;
    }
    FragColor = vec4(MeanNormal, 1.f) * vec4(PhongColor, 1.f);
}
