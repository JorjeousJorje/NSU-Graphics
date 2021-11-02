#version 450

in vec3 posAttr;
in vec4 colAttr;
in vec3 normalAttr;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 normal_matrix;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(posAttr, 1.0));
    Normal = mat3(normal_matrix) * normalAttr;
    gl_Position = projection * view * model * vec4(posAttr, 1.0);
}