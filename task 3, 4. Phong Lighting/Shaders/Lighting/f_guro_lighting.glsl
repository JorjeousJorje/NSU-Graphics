#version 450
in vec3 FragPos;
in vec3 Normal;
in vec3 PhongColor;

uniform bool wireframe_enabled;

void main()
{
    if(wireframe_enabled) {
        gl_FragColor = vec4(1, 0.682, 0, 1.0f);
    } else {
        gl_FragColor = vec4(PhongColor, 1.0f);
    } 
}