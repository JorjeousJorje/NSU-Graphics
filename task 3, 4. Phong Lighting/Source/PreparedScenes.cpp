#include "PreparedScenes.h"


#include "GLDirectedLight.h"
#include "GLPointLight.h"
#include "GLSpotLight.h"
#include "MeshGeneratorCollecrion.h"
#include "ShaderCollection.h"


void init_grid(GLScene& scene, const size_t grid_size)
{
	auto& shader = ShaderCollection::shaders["guro_lighting"];
	const auto& generator = MeshGeneratorCollection::generators["cube"];
	QVector3D pos = {};
	
	GLMaterial material;
	material.shininess = 32.0f;
	
	for (std::size_t i = 0; i < grid_size; ++i) {

		for (std::size_t j = 0; j < grid_size; ++j) {
			pos.setX(static_cast<float>(i) * 1.5f);
			pos.setY(-5);
			pos.setZ(static_cast<float>(j) * 1.5f - 10);

			scene.add_object(shader, generator, pos, { 0, 0, 0 }, material);
		}
	}
}

void PreparedScenes::init()
{
	scenes.emplace("default", default_scene());
	scenes.emplace("point_light", point_lights_scene());
	scenes.emplace("spot_light", spot_lights_scene());
	scenes.emplace("directed_light", directed_lights_scene());
	scenes.emplace("mega", mega_scene());
}

GLScene PreparedScenes::default_scene()
{
	GLScene scene;
	const auto grid_size = 20u;
	
	init_grid(scene, grid_size);

	auto& light_object_shader = ShaderCollection::shaders["light"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["cube"];
	const auto light = std::make_shared<GLSpotLight>(QVector3D{ 5, 1, 10 }, QColor{ 255, 255, 255 });
	scene.add_light(light, light_object_shader, light_object_generator);


	return scene;
}

GLScene PreparedScenes::point_lights_scene()
{
	GLScene scene;
	const auto grid_size = 20u;

	init_grid(scene, grid_size);

	
	auto& light_object_shader = ShaderCollection::shaders["light"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["cube"];
	const auto light1 = std::make_shared<GLPointLight>(QVector3D{ 5, 1, 10 }, QColor{ 255, 255, 255 });
	scene.add_light(light1, light_object_shader, light_object_generator);
	const auto light2 = std::make_shared<GLPointLight>(QVector3D{ 10, 1, 11 }, QColor{ 255, 255, 255 });
	scene.add_light(light2, light_object_shader, light_object_generator);

	return scene;
}

GLScene PreparedScenes::spot_lights_scene()
{
	GLScene scene;
	const auto grid_size = 20u;

	init_grid(scene, grid_size);


	auto& light_object_shader = ShaderCollection::shaders["light"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["cube"];
	const auto light1 = std::make_shared<GLSpotLight>(QVector3D{ 5, 1, 10 }, QColor{ 255, 255, 255 });
	scene.add_light(light1, light_object_shader, light_object_generator);
	const auto light2 = std::make_shared<GLSpotLight>(QVector3D{ 10, 1, 11 }, QColor{ 255, 255, 255 });
	scene.add_light(light2, light_object_shader, light_object_generator);

	return scene;
}

GLScene PreparedScenes::directed_lights_scene()
{
	GLScene scene;
	const auto grid_size = 20u;
	
	init_grid(scene, grid_size);



	auto& light_object_shader = ShaderCollection::shaders["light"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["cube"];
	const auto light1 = std::make_shared<GLDirectedLight>(QVector3D{ 1000000, 0, 0 }, QColor{ 255, 255, 255 });
	scene.add_light(light1, light_object_shader, light_object_generator);

	return scene;
}

GLScene PreparedScenes::mega_scene()
{
	GLScene scene;
	const auto grid_size = 30;

	init_grid(scene, grid_size);


	auto& light_object_shader = ShaderCollection::shaders["light"];
	const auto& light_object_generator = MeshGeneratorCollection::generators["cube"];
	const auto light1 = std::make_shared<GLSpotLight>(QVector3D{ 5, 1, 10 }, QColor{ 255, 255, 255 });
	scene.add_light(light1, light_object_shader, light_object_generator);
	const auto light2 = std::make_shared<GLSpotLight>(QVector3D{ 15, 1, 11 }, QColor{ 255, 255, 255 });
	scene.add_light(light2, light_object_shader, light_object_generator);
	const auto light3 = std::make_shared<GLSpotLight>(QVector3D{ 35, 7, 10 }, QColor{ 255, 255, 255 });
	scene.add_light(light3, light_object_shader, light_object_generator);
	const auto light4 = std::make_shared<GLSpotLight>(QVector3D{ 98, 14, 10 }, QColor{ 255, 255, 255 });
	scene.add_light(light4, light_object_shader, light_object_generator);
	const auto light5 = std::make_shared<GLSpotLight>(QVector3D{ 34, 14, 19 }, QColor{ 255, 255, 255 });
	scene.add_light(light5, light_object_shader, light_object_generator);
	const auto light6 = std::make_shared<GLSpotLight>(QVector3D{ 45, 6, 16 }, QColor{ 255, 255, 255 });
	scene.add_light(light6, light_object_shader, light_object_generator);

	return scene;
}
