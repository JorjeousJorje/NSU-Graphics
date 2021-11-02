#pragma once
#include <QOpenGLShaderProgram>
#include <string>
#include <fstream>

struct shader_code
{

    const char* vertex_code;
    const char* fragment_code;
};

class ShaderParser
{
public:
    ShaderParser(const std::string& vertex_path, const std::string& fragment_path);

    shader_code parse();

private:
    std::ifstream vertex_shader_file_, frag_shader_file_;
    std::string vertex_code_{}, fragment_code_{};
};
