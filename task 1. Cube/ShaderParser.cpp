#include "ShaderParser.h"
#include <iostream>
#include <ostream>
#include <sstream>

using ifs = std::ifstream;

ShaderParser::ShaderParser(const std::string& vertex_path, const std::string& fragment_path)
	: vertex_shader_file_{vertex_path}, frag_shader_file_{fragment_path}
{
}

shader_code ShaderParser::parse()
{
	
    vertex_shader_file_.exceptions(ifs::failbit | ifs::badbit | ifs::eofbit);
    frag_shader_file_.exceptions(ifs::failbit | ifs::badbit | ifs::eofbit);

	try {
        std::stringstream vertex_shader_stream, frag_shader_stream;

        vertex_shader_stream << vertex_shader_file_.rdbuf();
        frag_shader_stream << frag_shader_file_.rdbuf();

        vertex_code_ = vertex_shader_stream.str();
        fragment_code_ = frag_shader_stream.str();
	} catch (const std::ifstream::failure& ex) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << ex.what() << std::endl;
    }

    return { vertex_code_.c_str() , fragment_code_.c_str() };
}