#pragma once
#include <memory>
#include <QVector3D>
#include <numbers>


constexpr auto PI = std::numbers::pi_v<float>;



class TreeBranch
{
public:
	TreeBranch(const float r, const float s, const float ss)
		:	ratio_{ r },
			spread_{ s },
			split_size_{ ss }
	{}

	TreeBranch(std::unique_ptr<TreeBranch> branch, const bool root)
		:	ratio_{ branch->ratio_ },
			spread_{ branch->spread_ },
			split_size_{ branch->split_size_ }
	{
		if (root) {
			return;
		}
		depth_ = branch->depth_ + 1;
		parent_ = std::move(branch);
	}

	void grow(float feed_count)
	{
		radius_ = std::sqrt(area_ / PI);

		if(leaf_) {
			length_ = std::cbrt(feed_count);
			feed_count -= std::cbrt(feed_count) * area_;
			area_ += feed_count / length_;

			if(length_ > split_size_ * std::exp(split_size_ * depth_)) {
				split();
			}

			return;
		}
	}

	
	void split()
	{
		
	}
	 
	QVector3D leaf_density(int search_depth)
	{
		
	}

private:
	std::size_t id_ = 0; //For Leaf Hashing
	std::unique_ptr<TreeBranch> left_children_;
	std::unique_ptr<TreeBranch> right_children_;
	std::unique_ptr<TreeBranch> parent_;


	std::size_t depth_ = 0u;
	float ratio_, spread_, split_size_;
	bool leaf_ = true;

	QVector3D growth_dir_{ 0.0f, 1.0f, 0.0f };
	float length_ = 0.0f, radius_ = 0.0f, area_ = 0.1f;
	
	
};


