#pragma once
#include <limits>

#include "GLCamera.h"



class GLCameraMover final
{
public:
	void move();
	GLCamera camera;

	void set_camera_speed(float delta_time);
	void set_key(int key);
	void reset_key(int key);
private:

	int last_pressed_key_{ std::numeric_limits<int>::max() };
	float initial_camera_speed_{ 10.5f };
	float current_camera_speed_{ initial_camera_speed_ };
	
	std::map<int, QVector3D> controls_ = {
			{Qt::Key_W, {0,0,1}	},
			{Qt::Key_S, {0,0,-1}	},
			{Qt::Key_A, {-1,0,0}	},
			{Qt::Key_D, {1,0,0}	},
			{Qt::Key_E, {0,1,0}	},
			{Qt::Key_Q, {0,-1,0}	}
	};
};