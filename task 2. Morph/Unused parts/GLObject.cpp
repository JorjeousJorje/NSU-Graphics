//#include "GLObject.h"
//
//GLObject::GLObject(GLMesh mesh, GLTransformation transform, renderer_sptr renderer)
//	:	mesh_{std::move(mesh)},
//		transform_{ std::move(transform) },
//		renderer_{ std::move(renderer) }
//{
//}
//
//void GLObject::init_renderer(const std::string& vertex, const std::string& fragment) const
//{
//	renderer_->init_renderer(&mesh_, vertex, fragment);
//}
//
//GLTransformation& GLObject::transform()
//{
//	return transform_;
//}
//
//const GLTransformation& GLObject::transform() const
//{
//	return transform_;
//}
//
//GLMeshRenderer& GLObject::renderer()
//{
//	return *renderer_;
//}
//
//const GLMeshRenderer& GLObject::renderer() const
//{
//	return *renderer_;
//}
