#include <QOpenGLFunctions_3_0>

#include "GLSimpleMeshRenderer.h"
#include "GLPointLight.h"
#include "GLDirectedLight.h"
#include "GLSpotLight.h"

GLSimpleMeshRenderer::GLSimpleMeshRenderer(GLMesh& mesh, GLTransform& transform, GLMaterial& material)
	: GLMeshRenderer{ mesh, transform, material }
{
	
}



void GLSimpleMeshRenderer::render(QOpenGLFunctions_3_0& functions, const Camera& camera, const std::map<light_sptr, obj_sptr>& lights)
{
	functions.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader_program_->bind();
	shader_program_->setUniformValue("wireframe_enabled", false);
	upload_camera_details(camera);

	if (!material_.is_light_source) {
		upload_lights_details(lights);
		material_.upload_to_shader(shader_program_);
	}
	
	upload_texture_details(functions);
	
	vao_.bind();
	functions.glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh_.indices.size()), GL_UNSIGNED_INT, nullptr);
	// vao_.release();
	
	/*if(!material_.texture.empty()) {
		for(auto& texture : material_.texture) {
			texture.texture_data->release();
		}
	}
	if (!material_.normals.empty()) {
		for (auto& normals : material_.normals) {
			normals.texture_data->release();
		}
	}*/
	
}

void GLSimpleMeshRenderer::upload_lights_details(const std::map<light_sptr, obj_sptr>& lights) const
{
	auto point_lights = 0u;
	auto spot_lights = 0u;
	auto directed_lights = 0u;
	for (const auto& [light, light_object] : lights) {

		auto id = 0u;
		if (std::dynamic_pointer_cast<GLPointLight>(light) != nullptr)
		{
			id = point_lights++;
		}
		if (std::dynamic_pointer_cast<GLDirectedLight>(light) != nullptr)
		{
			id = directed_lights++;
		}
		if (std::dynamic_pointer_cast<GLSpotLight>(light) != nullptr)
		{
			id = spot_lights++;
		}
		light->upload_to_shader(shader_program_, id);

	}

	shader_program_->setUniformValue("directed_lightsCount", static_cast<int>(directed_lights));
	shader_program_->setUniformValue("point_lightsCount", static_cast<int>(point_lights));
	shader_program_->setUniformValue("spot_lightsCount", static_cast<int>(spot_lights));
}

void GLSimpleMeshRenderer::upload_texture_details(QOpenGLFunctions_3_0& functions)
{
	for (auto i = 0u; i < material_.texture.size(); ++i) {
		const auto texture_name = "t" +  std::to_string(i);
		shader_program_->setUniformValue(texture_name.c_str(), i);
		functions.glActiveTexture(GL_TEXTURE0 + i);
		material_.texture[i].texture_data->bind();
	}

	/*for (auto i = 0u; i < material_.normals.size(); ++i) {
		const auto texture_name = "n" + std::to_string(i);
		shader_program_->setUniformValue(texture_name.c_str(), i);
		functions.glActiveTexture(GL_TEXTURE0 + i);
		material_.normals[i].texture_data->bind();
	}*/
}
