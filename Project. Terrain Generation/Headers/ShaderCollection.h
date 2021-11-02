#pragma once
#include <map>
#include "ShaderData.h"
#include "GLSimpleMeshRendererGenerator.h"

class ShaderCollection final
{
public:
	
	inline static std::map<std::string, ShaderData> shaders =
	{

		{	{"light_source"},
				{"Shaders\\Lighting\\v_light_source.glsl",
			   "Shaders\\Lighting\\f_light_source.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },

		{	{"phong_wo_normal_mapping"},
				{"Shaders\\Lighting\\v_phong_lighting_wo_normal_mapping.glsl",
			   "Shaders\\Lighting\\f_phong_lighting_wo_normal_mapping.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },

		{	{"phong_normal_mapping"},
				{"Shaders\\Lighting\\v_phong_lighting_normal_mapping.glsl",
			   "Shaders\\Lighting\\f_phong_lighting_normal_mapping.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },
		
		{	{"guro_wo_normal_mapping"},
				{"Shaders\\Lighting\\v_guro_lighting_wo_normal_mapping.glsl",
			   "Shaders\\Lighting\\f_guro_lighting_wo_normal_mapping.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },

		{ {"morphing"},
				{"Shaders\\v_morphing.glsl",
			   "Shaders\\f_morphing.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },
		
		{ {"many_textures"},
				{"Shaders\\Lighting\\v_texture_filters.glsl",
			   "Shaders\\Lighting\\f_texture_filters.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },
		{ {"terrain_default"},
				{"Shaders\\Terrain\\v_default.glsl",
			   "Shaders\\Terrain\\f_default.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },

		{ {"terrain_light"},
				{"Shaders\\Terrain\\v_phong_lighting.glsl",
			   "Shaders\\Terrain\\f_phong_lighting.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} }
	};
};
