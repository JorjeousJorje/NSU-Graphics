#include "SimpleTerrainGenerator.h"

SimpleTerrainGenerator::SimpleTerrainGenerator(const float terrain_size, const unsigned vertex_count)
	:	terrain_size_{ terrain_size },
		vertex_count_{ vertex_count }
{
}

void SimpleTerrainGenerator::init_indices(std::vector<unsigned>& indices) 
{
	const auto part = (vertex_count_ - 1) / num_of_workers;
	auto remain = (vertex_count_ - 1) % num_of_workers;
	auto part_end = 0u;


	int pointer = 0;
	for (auto k = 0u; k < vertex_count_ - 1; k += part_end) {
		part_end = remain > 0 ? part + !!remain-- : part;
		auto result_end = k + part_end;

		pool.insert_task([&, k, result_end, pointer]
			{
				auto current_pointer = pointer;
				for (auto gz = k; gz < result_end; ++gz) {
					for (unsigned gx = 0; gx < vertex_count_ - 1; ++gx) {
						const auto topleft = gz * vertex_count_ + gx;
						const auto topright = topleft + 1;
						const auto bottomleft = (gz + 1) * vertex_count_ + gx;
						const auto bottomright = bottomleft + 1;
						indices[current_pointer++] = topleft;
						indices[current_pointer++] = bottomleft;
						indices[current_pointer++] = topright;
						indices[current_pointer++] = topright;
						indices[current_pointer++] = bottomleft;
						indices[current_pointer++] = bottomright;
					}
				}
			});
		pointer += 6u * (vertex_count_ - 1) * part_end;
	}
}