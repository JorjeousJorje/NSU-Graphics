#pragma once
#include <map>
#include <string>
#include "GLScene.h"


class PreparedScenes
{
public:
	std::map<std::string, GLScene> scenes;

	void init();

private:
	GLScene default_scene();
	GLScene point_lights_scene();
	GLScene spot_lights_scene();
	GLScene directed_lights_scene();
	GLScene mega_scene();
};
