#pragma once
#include <QMatrix4x4>
#include <QQuaternion>

class Camera
{
public:
    Camera(const QVector3D& pos_ = { 0, 60, 0 });

    QMatrix4x4 get_projection_matrix() const;
    QMatrix4x4 get_view_matrix() const;
    void rotate(float upDown, float leftRight);
    void step(float forwBack, float leftRight);
    void moveAround(QVector2D vec, float step);
    void fly(float upDown);

    float zoom = 45.f;
    QVector3D position;
    QVector3D eyeLaser;
    QVector3D headDir;
    QVector3D rightDir;

};

inline Camera::Camera(const QVector3D& pos_)
{
    position = pos_;
    eyeLaser = QVector3D(0, 0, -1);
    headDir = QVector3D(0, 1, 0);
    rightDir = QVector3D(1, 0, 0);
}

inline QMatrix4x4 Camera::get_projection_matrix() const
{
    QMatrix4x4 perspective;
    perspective.perspective(zoom, 16.0f / 9.0f, 0.1f, 1000.0f);
    return perspective;
}

inline QMatrix4x4 Camera::get_view_matrix() const
{
    QMatrix4x4 view;
    view.lookAt(position, position + eyeLaser, headDir);
    return view;
}

inline void Camera::rotate(float upDown, float leftRight)
{
    QQuaternion rotateLeftRight = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), leftRight);
    QQuaternion rotateUpDown = QQuaternion::fromAxisAndAngle(rightDir, upDown);
    QVector3D tmp = rotateLeftRight * rotateUpDown * headDir;
    if (tmp.y() > 0)
    {
        eyeLaser = rotateLeftRight * rotateUpDown * eyeLaser;
        headDir = rotateLeftRight * rotateUpDown * headDir;
        rightDir = rotateLeftRight * rotateUpDown * rightDir;
    }
    else
    {
        eyeLaser = rotateLeftRight * eyeLaser;
        headDir = rotateLeftRight * headDir;
        rightDir = rotateLeftRight * rightDir;
    }

}

inline void Camera::moveAround(QVector2D vec, float step)
{
    position -= QVector3D(vec.x(), 0, vec.y());
    const QQuaternion rotate = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), step);
    position = rotate * position;
    eyeLaser = rotate * eyeLaser;
    headDir = rotate * headDir;
    rightDir = rotate * rightDir;

    position += QVector3D(vec.x(), 0, vec.y());
}

inline void Camera::step(float forwBack, float leftRight)
{
    position = position + eyeLaser * forwBack;
    position = position + rightDir * leftRight;
}

inline void Camera::fly(float upDown)
{
    position = position + QVector3D(0, upDown, 0);
}