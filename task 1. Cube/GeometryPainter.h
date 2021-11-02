#pragma once
#include "Geometry.h"

// Имеет смысл,
class GeometryPainter
{
public:
	GeometryPainter(Geometry& geometry) : geometry_{ geometry } {}
	virtual ~GeometryPainter() = default;
	
	virtual void setUniformColor(const QColor& color) = 0;

protected:
	Geometry& geometry_;
};
