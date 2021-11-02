#pragma once
#include "GLScene.h"

#include "TerrainGenerationExample.h"
#include "GLDirectedLight.h"
#include "GLTextureLoader.h"
#include "SimpleTerrainGenerator.h"
#include "ShaderCollection.h"
#include "MeshGeneratorCollecrion.h"

#include "TaskDispatcher/task_dispather.hpp"
#include "TaskDispatcher/thread_pool.hpp"

#include <random>
#include "DiamondSquareMapGenerator.h"


template<typename T>
class TerrainGenerationExample
{
public:

	TerrainGenerationExample(const int _vertex_cnt)
		:	vertex_cnt{ _vertex_cnt },
			map_generator_{ vertex_cnt }
	{
		auto [min__h, max__h] = map_generator_.perform_diamond_square_algorithm(pool);
		min_h = min__h;
		max_h = max__h;
		current_map = map_generator_.get_height_map();
	}
	
	void fill_scene(GLScene& scene, const bool add_lights)
	{
		auto& map = map_generator_.get_height_map();

		load_terrain(scene);

		if (add_lights) {
			get_lights(scene);
		}
	}

	void change_map(GLScene& scene, const T constant = T(140), const float power = 0.5)
	{
		auto [min__h, max__h] = map_generator_.perform_diamond_square_algorithm(pool, constant, power);

		min_h = min__h;
		max_h = max__h;

		current_map = map_generator_.get_height_map();

		auto& terrain_object = *scene.objects.front();
		// terrain_generator.replace_map(terrain_object.mesh, current_map);
		terrain_object.renderer->reload();

	}

	void delete_thermal_erosion(GLScene& scene)
	{
		current_map = current_map_wo_erosion;
		auto& terrain_object = *scene.objects.front();
		terrain_generator.replace_map(terrain_object.mesh, current_map);
		terrain_object.renderer->reload();

		first_time_erosion = true;
	}

	void apply_thermal_erosion(GLScene& scene, const int erosion_times)
	{
		if (first_time_erosion) {
			first_time_erosion = false;
			current_map_wo_erosion = current_map;
		}
		
		for (int i = 0; i < erosion_times; i++) {
			ThermalErosion(pool, current_map, vertex_cnt, max_h);
		}

		if(erosion_times > 0) {
			auto& terrain_object = *scene.objects.front();
			terrain_generator.replace_map(terrain_object.mesh, current_map);
			terrain_object.renderer->reload();
		}
	}




	int vertex_cnt;
	int last_erosion_times = 0;
	GLMesh terrain_mesh;
	GLMaterial material;
	ShaderData& shader_data = ShaderCollection::shaders["terrain_light"];
	SimpleTerrainGenerator terrain_generator{ 400, static_cast<unsigned>(vertex_cnt) };
	DiamondSquareMapGenerator<T> map_generator_;


	bool first_time_erosion = true;
	std::vector<T> current_map_wo_erosion;
	std::vector<T> current_map;
	T min_h = 0;
	T max_h = 0;

	
	std::size_t num_of_workers = 8;
	task_dispatcher pool{ num_of_workers };
private:

	void get_lights(GLScene& scene) const
	{
		auto& light_object_shader = ShaderCollection::shaders["light_source"];
		const auto& light_object_generator = MeshGeneratorCollection::generators["sphere"];

		const auto& light_sphere_gen = std::dynamic_pointer_cast<GLSphereMeshGenerator>(light_object_generator);
		light_sphere_gen->radius_ = 0.f;

		const auto light = std::make_shared<GLDirectedLight>(QVector3D{ 1, -1, 0 }, QColor{ 255, 255, 255 });
		scene.add_light(light, light_object_shader, light_sphere_gen);
	}

	void load_terrain(GLScene& scene, const bool load_texture = true)
	{
		const auto& map = map_generator_.get_height_map();

		if(load_texture) {
			
			GLTextureLoader::load_texture(material, "Textures\\T_Ground_Grass_1_BC_R.tga");
			GLTextureLoader::load_texture(material, "Textures\\T_Ground_Rock_2_BC_R.tga");
			GLTextureLoader::load_texture(material, "Textures\\T_Ground_Rock_5_BC_R.tga");
			GLTextureLoader::load_texture(material, "Textures\\T_Ground_Snow_1_BC_R.tga");
			GLTextureLoader::load_texture(material, "Textures\\T_Ground_Mud_1_BC_R.tga");
			
			material.shininess = 32.f;
			material.diffuse = { 255, 255, 255 };
			material.specular = { 255, 255, 255 };
			material.ambient = { 255, 255, 255 };
		}
		
		terrain_mesh = terrain_generator.generate(map);

		scene.add_object(shader_data, terrain_mesh, { 0, -2, 0 }, material);
	}

	
};
