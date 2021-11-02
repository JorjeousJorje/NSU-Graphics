#pragma once
#include <QColor>
#include "GLMesh.h"


class GLMeshGenerator
{
public:
	GLMeshGenerator() = default;

	virtual GLMesh generate(const QColor& color) = 0;
	virtual ~GLMeshGenerator() = default;
protected:
	void init_tangent_bitangent_vectors(std::vector<GLVertex>& vertices, std::vector<unsigned>& indices);
	
	virtual void init_vertices(std::vector<GLVertex>& vertices, const QColor& color) = 0;
	virtual void init_indices(std::vector<unsigned>& indices) = 0;
};