#pragma once
#include "GLMesh.h"
#include "TaskDispatcher/task_dispather.hpp"
#include "TaskDispatcher/thread_pool.hpp"
#include <QColor>
#include <cassert>


class SimpleTerrainGenerator
{
public:
	explicit SimpleTerrainGenerator(float terrain_size, unsigned vertex_count);

	template<typename T>
	GLMesh generate(const std::vector<T>& h_map, const QColor& color = {})
	{
		assert(h_map.size() == vertex_count_ * vertex_count_ && "Wrong height map size!");


		GLMesh mesh{};
		mesh.vertices.resize(vertex_count_ * vertex_count_);
		mesh.indices.resize(6 * (vertex_count_ - 1) * vertex_count_);
		
		init_vertices(mesh.vertices, h_map, color);
		init_indices(mesh.indices);

		pool.wait_finished();

		return mesh;
	}

	template<typename T>
	void replace_map(GLMesh& terrain_mesh, const std::vector<T>& h_map)
	{
		auto& terrain_vertices = terrain_mesh.vertices;
		
		const auto part = vertex_count_ / num_of_workers;
		auto remain = vertex_count_ % num_of_workers;
		auto part_end = 0u;

		
		for (auto k = 0u; k < vertex_count_; k += part_end) {
			part_end = remain > 0 ? part + !!remain-- : part;
			auto result_end = k + part_end;

			pool.insert_task([&, k, result_end]
				{
					for (auto i = k; i < result_end; ++i) {
						for (auto j = 0; j < vertex_count_; ++j) {
							const auto new_height = static_cast<float>(h_map[i * vertex_count_ + j]);
							terrain_vertices[i * vertex_count_ + j].coordinate.setY(new_height);
							terrain_vertices[i * vertex_count_ + j].normal = calculateNormal(j, i, h_map);
							terrain_vertices[i * vertex_count_ + j].mean_normal += terrain_vertices[i * vertex_count_ + j].normal / (result_end * vertex_count_);
						}
					}
				});
		}

		pool.wait_finished();
	}

	std::size_t num_of_workers = 8;
	thread_pool pool{ num_of_workers };
	float terrain_size_;
	unsigned vertex_count_;
	std::mutex main_lock_{};
private:
	
	template<typename T>
	void init_vertices(std::vector<GLVertex>& vertices, const std::vector<T>& h_map, const QColor& color = {})
	{
		auto part = vertex_count_ / num_of_workers;
		auto remain = vertex_count_ % num_of_workers;
		
		auto part_end = 0u;
		for (auto k = 0u; k < vertex_count_; k += part_end) {

			part_end = remain > 0 ? part + !!remain-- : part;
			auto result_end = k + part_end;
			pool.insert_task([&, k, result_end, part_end]
				{
					GLVertex vertex{};
					for (auto i = k; i < result_end; ++i) {
						for (auto j = 0; j < vertex_count_; ++j) {
							vertex.coordinate.setX(-static_cast<float>(j) / static_cast<float>(vertex_count_ - 1) * terrain_size_);

							
							const auto height = h_map[i * vertex_count_ + j];
							vertex.coordinate.setY(height);
							vertex.coordinate.setZ(-static_cast<float>(i) / static_cast<float>(vertex_count_ - 1) * terrain_size_);

							vertex.normal = calculateNormal(j, i, h_map);

							vertex.color.setX(static_cast<float>(color.redF()));
							vertex.color.setY(static_cast<float>(color.greenF()));
							vertex.color.setZ(static_cast<float>(color.blueF()));

							vertex.texture = { static_cast<float>(j) / static_cast<float>(vertex_count_ - 1) ,
											   static_cast<float>(i) / static_cast<float>(vertex_count_ - 1) };

							vertices[i * vertex_count_ + j] = vertex;
						}
					}
				});

			// доделать от крутизны.
		}
		
	}
	void init_indices(std::vector<unsigned>& indices);
	
	template<typename T>
	QVector3D calculateNormal(int x, int z, const std::vector<T>& h_map)
	{
		const auto hL = getHeight(x - 1, z, h_map);
		const auto hR = getHeight(x + 1, z, h_map);
		const auto hD = getHeight(x - 1, z - 1, h_map);
		const auto hU = getHeight(x - 1, z + 1, h_map);

		const auto normal = QVector3D{ hL - hR, 1.f, hD - hU }.normalized();
		return normal;
	}
	
	template<typename T>
	float getHeight(int x, int z, const std::vector<T>& h_map)
	{
		if (x < 0 || x * vertex_count_ >= h_map.size() || z < 0 || z * vertex_count_ >= h_map.size()) {
			return 0;
		}
		return h_map[z * vertex_count_ + x];
	}
};
