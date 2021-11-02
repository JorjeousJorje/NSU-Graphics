#pragma once

#include "GLMeshRenderer.h"

class GLCubeMeshRenderer : public GLMeshRenderer
{

public:
	
	void render() override;

private:

	void draw_edges();
	void draw_faces();
};
