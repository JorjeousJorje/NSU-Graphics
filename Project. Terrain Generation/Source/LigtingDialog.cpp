#include "LightingDialog.h"
#include "PhongLightingWidget.h"


LightingDialog::LightingDialog(PhongLightingWidget& phong_widget, QWidget* parent)
	: QWidget{ parent }
{
	setupUi(this);
	connect(shiness, &QSlider::valueChanged, &phong_widget, &PhongLightingWidget::set_constant);
	connect(shiness_2, &QSlider::valueChanged, &phong_widget, &PhongLightingWidget::set_order);
	connect(shiness_3, &QSlider::valueChanged, &phong_widget, &PhongLightingWidget::set_erosion);
	connect(pushButton, &QPushButton::clicked, &phong_widget, &PhongLightingWidget::generate_terrain);
	connect(pushButton_2, &QPushButton::clicked, &phong_widget, &PhongLightingWidget::apply_erosion);
	connect(pushButton_3, &QPushButton::clicked, &phong_widget, &PhongLightingWidget::delete_erosion);
}
