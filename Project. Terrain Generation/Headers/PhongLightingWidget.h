#pragma once
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColorDialog>
#include <QBasicTimer>

#include "RenderDialog.h"
#include "FPSCounter.h"
#include "GLSceneRenderer.h"
#include "LightingDialog.h"
#include "GLScene.h"
#include "TerrainGenerationExample.h"


constexpr int map_size = 1025;

class PhongLightingWidget final : public QOpenGLWidget
{
	Q_OBJECT
public:
	explicit PhongLightingWidget(QWidget* parent = nullptr);
	
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;


public slots:
	void show_render_dialog();
	void show_shininess_dialog();

	void set_render_mode(int state);
	void catch_fps(const QString&);

	void set_constant(int constant);
	void set_order(int order);
	void set_erosion(int erosion);
	void generate_terrain();
	void apply_erosion();
	void delete_erosion();

signals:
	void send_fps(const QString&);
	
protected:
	void initializeGL() override;
	void paintGL() override;
	void keyEvent();
	void mouseEvent();

	
public:
	TerrainGenerationExample<double> example{ map_size };

	bool wrap{ true };
	int last_constant { 140 };
	int erosion_times_{ 0 };
	float last_order { 50.f };
	
	GLScene current_scene_;
	GLSceneRenderer renderer_;
	RenderDialog render_dialog_;
	LightingDialog lighting_dialog_;

	FPSCounter fps_counter_;
};
