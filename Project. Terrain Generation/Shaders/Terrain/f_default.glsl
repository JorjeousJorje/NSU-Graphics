#version 450
in vec4 Color;
in vec2 TexCoords;

uniform sampler2D t1;
uniform sampler2D t2;
uniform sampler2D t3;

out vec4 FragColor;
void main()
{
    FragColor = vec4(texture(t1, TexCoords).rgb, 1.f);
}


