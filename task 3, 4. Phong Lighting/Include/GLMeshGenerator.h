#pragma once
#include <QColor>

#include "GLMesh.h"


class GLMeshGenerator
{
public:
	GLMeshGenerator() = default;

	virtual GLMesh generate(unsigned mesh_steps, const QColor& color) const = 0;
	virtual GLMesh generate() const = 0;

	virtual ~GLMeshGenerator() = default;
};