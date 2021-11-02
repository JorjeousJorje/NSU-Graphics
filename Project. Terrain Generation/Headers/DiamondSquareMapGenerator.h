#pragma once
#include <vector>
#include <random>
#include <chrono>
#include "diamond_square.h"
#include "ThermalErosion.h"
#include "TaskDispatcher/task_dispather.hpp"
#include <utility>
#include "TaskDispatcher/thread_pool.hpp"



template<typename T>
class DiamondSquareMapGenerator
{
public:
	DiamondSquareMapGenerator(int _map_size);
	
	height_values perform_diamond_square_algorithm(task_dispatcher& pool, const T constant = T(140), const float power = 0.5)
	{
		init_corners();
		auto [min_h, max_h] = diamond_square_algorithm
		(
			pool,
			map_size,
			// random
			[this](T rng) { return distribution(engine) * rng; },
			// variance
			[constant, power](const int level) -> T { return constant * std::pow<T>(power, level); },
			// at
			[this](const int x, const int y) -> T& { return height_map[y * map_size + x]; }

		);

		return { min_h, max_h };
	}

	const std::vector<T>& get_height_map() const
	{
		return height_map;
	}

	std::vector<T>& get_height_map()
	{
		return height_map;
	}
	unsigned seed;
	int map_size;
	std::mt19937 engine;
	std::vector<T> height_map;
private:
	
	std::uniform_real_distribution<T> distribution;
	std::uniform_real_distribution<T> height_distribution;
	
	void init_corners()
	{
		auto edge = map_size - 1;
		height_map[0] = height_distribution(engine);

		height_map[edge] = height_distribution(engine);

		height_map[edge * edge - edge] = height_distribution(engine);

		height_map[edge * edge] = height_distribution(engine);
	}
};

template<typename T>
DiamondSquareMapGenerator<T>::DiamondSquareMapGenerator(const int _map_size)
	:	seed{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) },
		map_size{ _map_size },
		engine(seed),
		height_map(map_size * map_size, T(0)),
		distribution{ T(0), T(1) },
		height_distribution{ T(1), T(16) }
{
	
}
