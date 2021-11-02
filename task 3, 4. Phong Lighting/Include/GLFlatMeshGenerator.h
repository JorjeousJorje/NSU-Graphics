#pragma once
#include "GLMeshGenerator.h"



class GLFlatMeshGenerator : public GLMeshGenerator
{
public:
	explicit GLFlatMeshGenerator(float edge_len);


	GLMesh generate(unsigned mesh_steps, const QColor& color) const override;

private:
	float edge_len_;
	
	void init_vertices(std::vector<GLVertex>& vertices, unsigned mesh_steps, const QColor& color) const;
	void init_indices(std::vector<unsigned>& indices, unsigned mesh_steps, const QColor& color) const;

	GLMesh generate() const override;
};