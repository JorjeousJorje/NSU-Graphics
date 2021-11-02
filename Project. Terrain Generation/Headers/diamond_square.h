#pragma once
#include "TaskDispatcher/task_dispather.hpp"
#include "TaskDispatcher/thread_pool.hpp"
#include <cassert>
#include <utility>
#include <numeric>
struct height_values
{
    float min_h;
    float max_h;
};


template <typename T, typename T2, typename T3>
height_values diamond_square_algorithm(task_dispatcher& pool, int size, T&& random, T2&& variance, T3&& at)
{
    assert(size >= 5 && ((size - 1) & (size - 2)) == 0 && "valid size");

    auto level = 0;
    auto stride = size - 1;
    auto end = size - 1;

    auto min_h = at(0, 0); // std::numeric_limits<T>::lowest();
    auto max_h = at(0, 0); //  std::numeric_limits<T>::max();

    while (stride > 1) {
        auto range = variance(level);
        auto half = stride / 2;

        // Diamond step:
        for (auto y = half; y < end; y += stride) {
            for (auto x = half; x < end; x += stride) {
                auto tl = at(x - half, y - half);
                auto bl = at(x - half, y + half);
                auto tr = at(x + half, y - half);
                auto br = at(x + half, y + half);

                auto average = (tl + tr + br + bl) / 4.0f;
                auto displacement = random(range * 2.0f) - range;
                at(x, y) = average + displacement;

            	if(at(x, y) < min_h) {
                    min_h = at(x, y);
            	} else if (at(x, y) > max_h) {
                    max_h = at(x, y);
            	}
            }
        }

        // Square step:
        // Firstly there are four special cases to handle the rows and columns
        // with only three neighbours.

        // Top row - no up
        for (auto x = half; x < end; x += stride) {
            auto down = at(x, half);
            auto left = at(x - half, 0);
            auto right = at(x + half, 0);

            auto average = (down + left + right) / 3.0f;
            auto displacement = random(range * 2.0f) - range;

            at(x, 0) = average + displacement;
        	
            if (at(x, 0) < min_h) {
                min_h = at(x, 0);
            } else if (at(x, 0) > max_h) {
                max_h = at(x, 0);
            }
        }

        // Bottom row - no down
        for (auto x = half; x < end; x += stride) {
            auto up = at(x, end - half);
            auto left = at(x - half, end);
            auto right = at(x + half, end);

            auto average = (up + left + right) / 3.0f;
            auto displacement = random(range * 2.0f) - range;

            at(x, end) = average + displacement;

            if (at(x, end) < min_h) {
                min_h = at(x, end);
            }

            if (at(x, end) > max_h) {
                max_h = at(x, end);
            }
        }

        // Left column - no left
        for (auto y = half; y < end; y += stride) {
            auto up = at(0, y - half);
            auto down = at(0, y + half);
            auto right = at(half, y);

            auto average = (up + down + right) / 3.0f;
            auto displacement = random(range * 2.0f) - range;

            at(0, y) = average + displacement;

            if (at(0, y) < min_h) {
                min_h = at(0, y);
            }

            if (at(0, y) > max_h) {
                max_h = at(0, y);
            }
        }

        // Right column - no right
        for (auto y = half; y < end; y += stride) {
            auto up = at(end, y - half);
            auto down = at(end, y + half);
            auto left = at(end - half, y);

            auto average = (up + down + left) / 3.0f;
            auto displacement = random(range * 2.0f) - range;

            at(end, y) = average + displacement;

            if (at(end, y) < min_h) {
                min_h = at(end, y);
            }

            if (at(end, y) > max_h) {
                max_h = at(end, y);
            }
        }

        // The remaining points -- the edges all processed as special cases
        // above -- that have four neighbours.
        auto offset = true;

        for (auto y = half; y < end; y += half) {
            for (auto x = offset ? stride : half; x < end; x += stride) {
                auto up = at(x, y - half);
                auto down = at(x, y + half);
                auto left = at(x - half, y);
                auto right = at(x + half, y);

                auto average = (up + down + left + right) / 4.0f;
                auto displacement = random(range * 2.0f) - range;

                at(x, y) = average + displacement;

                if (at(x, y) < min_h) {
                    min_h = at(x, y);
                }

                if (at(x, y) > max_h) {
                    max_h = at(x, y);
                }
            }

            offset = !offset;
        }

        stride /= 2;
        ++level;
    }

    return { float(min_h), float(max_h) };
}