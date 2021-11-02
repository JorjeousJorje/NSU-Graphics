#pragma once
#include "ui_PhongLighting.h"

class PhongLighting : public QMainWindow
{
    Q_OBJECT

public:
    PhongLighting(QWidget *parent = Q_NULLPTR);

	void closeEvent(QCloseEvent* event) override
	{
		ui.PhongLightingWidget_->makeCurrent();
		ui.PhongLightingWidget_->current_scene_.objects.clear();
		ui.PhongLightingWidget_->current_scene_.lights_objects.clear();

		event->accept();
	}
	
private:
    Ui::PhongLightingClass ui;
};
