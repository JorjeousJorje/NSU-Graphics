#pragma once
#include <map>
#include "GLCubeMeshGenerator.h"
constexpr std::size_t initial_grid_step = 1;


class MeshGeneratorCollection final
{
public:

	inline static std::map<std::string, std::shared_ptr<GLMeshGenerator>> generators =
	{
		{{"cube"}, std::make_shared<GLCubeMeshGenerator>(1.0f)}
	};
};
