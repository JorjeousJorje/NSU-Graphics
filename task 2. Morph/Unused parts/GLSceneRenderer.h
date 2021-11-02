#pragma once
#include "QOpenGLFunctions"
class GLScene;

class GLSceneRenderer : protected QOpenGLFunctions
{
public:

	void render(GLScene& scene);
};
