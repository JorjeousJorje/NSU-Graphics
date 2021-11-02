#pragma once
#include "GLTransformation.h"
#include "GLMesh.h"
#include "GLMeshRenderer.h"

//using renderer_sptr = std::shared_ptr<GLMeshRenderer>;
//
//class GLObject
//{
//public:
//
//	
//	GLObject(GLMesh mesh, GLTransformation transform, renderer_sptr renderer);
//	void init_renderer(const std::string& vertex, const std::string& fragment) const;
//
//	GLTransformation& transform();
//
//	const GLTransformation& transform() const;
//
//	GLMeshRenderer& renderer();
//	
//	const GLMeshRenderer& renderer() const;
//	
//private:
//	GLMesh mesh_;
//	GLTransformation transform_;
//	renderer_sptr renderer_;
//	
//};