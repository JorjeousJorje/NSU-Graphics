#pragma once
#include <QMatrix4x4>


class GLTransformation
{

public:

	void translate(const QVector3D& translation)
	{
		position_ += translation;
		transform_.translate(translation);
	}
	void rotate(const float angle, const QVector3D& axis)
	{
		transform_.rotate(QQuaternion::fromAxisAndAngle(axis, angle));
	}

	void reset()
	{
		position_ = {};
		transform_.setToIdentity();
	}

private:
	QMatrix4x4 transform_{};
	QVector3D position_{};
	
};