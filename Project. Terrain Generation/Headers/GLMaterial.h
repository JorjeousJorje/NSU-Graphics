#pragma once
#include <QOpenGLShaderProgram>
#include "GLTexture.h"


struct GLMaterial
{
	std::vector<GLTexture> texture;
	std::vector<GLTexture> normals;
	
	QColor ambient;
	QColor diffuse;
	QColor specular;
	float  shininess;
	bool is_light_source;
	
	bool many_textures = false;

	GLMaterial(QColor _ambient = {}, QColor _diffuse = {}, QColor _specular = {}, float _shininess = 0, bool _is_light_source = false);
	
	void upload_to_shader(std::shared_ptr<QOpenGLShaderProgram>& shader) const;
};
