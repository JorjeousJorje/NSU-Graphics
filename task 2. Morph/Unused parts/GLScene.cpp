#include "GLScene.h"

GLScene::GLScene(const GLMeshGenerator& generator, renderer_sptr renderer, const ShaderData& data)
{
	add_object(generator, std::move(renderer), {0, 0, -2}, data);
	
}

void GLScene::add_object(const GLMeshGenerator& generator, 
						 renderer_sptr renderer, 
						 const QVector3D& pos, 
						 const ShaderData& data)
{
	/*const auto mesh = generator.generate();
	GLTransformation transform{};
	transform.translate(pos);
	
	GLObject object{ mesh, transform, std::move(renderer) };
	object.init_renderer(data.vertex, data.fragment);
	
	objects_.emplace_back(object);*/
	
}
