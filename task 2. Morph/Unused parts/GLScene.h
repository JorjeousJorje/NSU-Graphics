#pragma once
#include <vector>
#include "GLObject.h"
#include "GLMeshGenerator.h"
#include "ShaderData.h"


// class GLSceneRenderer;
using renderer_sptr = std::shared_ptr<GLMeshRenderer>;

class GLScene final
{
	friend class GLSceneRenderer;
public:
	GLScene(const GLMeshGenerator& generator, renderer_sptr renderer, const ShaderData& data);



private:
	//std::vector<GLObject> objects_;
	QVector2D angular_velocity_ = { 0,0 };

	void add_object(const GLMeshGenerator& generator, 
					renderer_sptr renderer, 
					const QVector3D& pos, 
					const ShaderData& data);
};
