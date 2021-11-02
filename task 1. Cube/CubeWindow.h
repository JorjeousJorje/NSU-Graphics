#pragma once
#include <QColorDialog>
#include <QSlider>
#include "CubeEdges.h"
#include "CubeGeometry.h"
#include "CubePainter.h"
#include "OpenGLWindow.h"

class CubeWindow : public OpenGLWindow
{
public:
    using OpenGLWindow::OpenGLWindow;

    explicit CubeWindow(ShaderParser& parser, QWindow* parent = nullptr)
        : OpenGLWindow{ parser , parent }
    {
        cube_geometry_.InitGeometry();
        edges_geometry_.InitGeometry();
    }

    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
	
    void Initialize() override;
	void Render(QPainter* painter) override {}
    void Render() override;

private:
    QColorDialog color_dialog_;
    QMatrix4x4 projection_{};

    QSlider slider_x_;
    QSlider slider_y_;
    QSlider slider_z_;
	
    CubeGeometry cube_geometry_{ 1.0f };
    CubeEdges edges_geometry_{ 1.0f };
	
    CubePainter painter_{ cube_geometry_ };


    QVector2D mouse_press_position_;
    QVector3D rotation_axis_;
    qreal angular_speed_ = 0;
    QQuaternion rotation_;

	
    void setRotation();
    void initColorDialog();
    void initSlidersDialog();
	void resizeGL() override;
};