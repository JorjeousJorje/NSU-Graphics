#include "GLCameraMover.h"



void GLCameraMover::move()
{
	const auto& direction = controls_[last_pressed_key_];
	if(direction == QVector3D{0, 0, 0}) {
		return;
	}
	camera.translate(direction * current_camera_speed_);
}

void GLCameraMover::set_camera_speed(const float delta_time)
{
	current_camera_speed_ = initial_camera_speed_ * delta_time;
}

void GLCameraMover::set_key(const int key)
{
	last_pressed_key_ = key;
}

void GLCameraMover::reset_key(const int key)
{
	if(last_pressed_key_ == key) {
		last_pressed_key_ = std::numeric_limits<int>::max();
	}
}
