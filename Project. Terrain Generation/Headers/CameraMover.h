#pragma once
#include "Camera.h"



class CameraMover final
{
public:
	void move()
	{
		if(keys[Qt::Key_A]) {
			camera.step(0, -current_camera_speed_);
		}
		if (keys[Qt::Key_D]) {
			camera.step(0, current_camera_speed_);
		}
		if (keys[Qt::Key_W]) {
			camera.step(current_camera_speed_, 0);
		}
		if (keys[Qt::Key_S]) {
			camera.step(-current_camera_speed_, 0);
		}
		if (keys[Qt::Key_Space]) {
			camera.fly(current_camera_speed_);
		}
		if (keys[Qt::Key_Control]) {
			camera.fly(-current_camera_speed_);
		}
		if (keys[Qt::Key_Q]) {
			camera.moveAround({ -100, -100 }, current_camera_speed_);
		}
		if (keys[Qt::Key_E]) {
			camera.moveAround({ -100, -100 }, -current_camera_speed_);
		}
		
	}
	Camera camera{};

	void set_camera_speed(float delta_time)
	{
		current_camera_speed_ = initial_camera_speed_ * delta_time;
	};
	void update_camera_zoom(float dy)
	{
		if (camera.zoom >= 1.f && camera.zoom <= 45.f) {
			camera.zoom -= dy;
		}
		else if (camera.zoom < 1.f) {
			camera.zoom = 1.f;
		}
		else {
			camera.zoom = 45.f;
		}
	};

	static inline std::map<int, bool> keys =
	{
			{Qt::Key_A,	false},
			{Qt::Key_D,	false},
			{Qt::Key_S,	false},
			{Qt::Key_W,	false},
			{Qt::Key_Space,	false},
			{Qt::Key_Control,false},
			{Qt::Key_Q,false},
			{Qt::Key_E,false},
	};
	
	int mouse_pos_x;
	int mouse_pos_y;
	
private:

	float initial_camera_speed_{ 10.5f };
	float current_camera_speed_{ initial_camera_speed_ };
};