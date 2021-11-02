#pragma once
#include <vector>
#include "TaskDispatcher/task_dispather.hpp"
#include "TaskDispatcher/thread_pool.hpp"


inline float getNewHeight(float h, float d, float dMax, float dTotal, float T) {
	const float c = 0.5f;
	if (d > T) {
		return h + c * (dMax - T) * d / dTotal;
	}
	return h;
}

template<typename T1>
void iteration(std::vector<T1>& v, int i, int j, int N) {
	float h = v.at((i)*N + j);
	//get 4 neighbors
	float h1 = v.at((i - 1) * N + j - 1);
	float h2 = v.at((i - 1) * N + j + 1);
	float h3 = v.at((i + 1) * N + j - 1);
	float h4 = v.at((i + 1) * N + j + 1);
	//difference
	float d1 = h - h1;
	float d2 = h - h2;
	float d3 = h - h3;
	float d4 = h - h4;

	const float T = 1 / 128.f;
	float dTotal = 0.f;
	float dMax = std::max(d1, std::max(d2, std::max(d3, d4)));
	if (d1 > T) dTotal += d1;
	if (d2 > T) dTotal += d2;
	if (d3 > T) dTotal += d3;
	if (d4 > T) dTotal += d4;
	//deposit soil to lower neighbors according to ratio d/dTotal
	v.at((i - 1) * N + j - 1) = getNewHeight(h1, d1, dMax, dTotal, T);
	v.at((i - 1) * N + j + 1) = getNewHeight(h2, d2, dMax, dTotal, T);
	v.at((i + 1) * N + j - 1) = getNewHeight(h3, d3, dMax, dTotal, T);
	v.at((i + 1) * N + j + 1) = getNewHeight(h4, d4, dMax, dTotal, T);
	v.at((i)*N + j) -= v.at((i - 1) * N + j - 1) + v.at((i - 1) * N + j + 1) +
		v.at((i + 1) * N + j - 1) + v.at((i + 1) * N + j + 1) - h1 - h2 - h3 - h4;

}

template<typename T>
void ThermalErosion(task_dispatcher& pool, std::vector<T>& v, int N, float h_max)
{
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < N - 1; j++) {
			iteration(v, i, j, N);
		}
	}
}