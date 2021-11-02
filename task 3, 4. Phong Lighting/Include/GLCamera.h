#pragma once
#include <qmatrix4x4.h>
#include <qvector3d.h>
#include <QtMath>

class GLCamera final
{
public:
	QVector3D position = { 10,1, 20 };
	
	GLCamera();
	QMatrix4x4 get_projection_matrix() const;
	QMatrix4x4 get_view_matrix() const;
	
	void update_camera_vectors();
	void translate(const QVector3D& mult);
	
private:
	float FOV = 60;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float aspectRatio = 16.0f / 9.0f;

	QVector3D front = { 0, 0, -1 };
	QVector3D right = { 1, 0, 0 };
	QVector3D up = { 0, 1, 0 };
};