#include <future>

#include "PhongLightingWidget.h"
#include "ShaderCollection.h"


void PhongLightingWidget::show_render_dialog()
{
    render_dialog_.show();
}

void PhongLightingWidget::set_render_mode(const int state)
{
	auto* obj = sender();

	if(obj->objectName() == "fill_checkBox") {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_fill);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_fill);
        }
	} else if (obj->objectName() == "line_checkBox") {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_line);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_line);
        }
	} else if (obj->objectName() == "front_checkBox") {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_cull_face_front);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_cull_face_front);
        }
    } else {
        if (state == Qt::Checked) {
            renderer_.set_mode(gl_cull_face_back);
        }
        else if (state == Qt::Unchecked) {
            renderer_.reset_mode(gl_cull_face_back);
        }
    }
}

void PhongLightingWidget::catch_fps(const QString& fps)
{
	emit send_fps(fps);
}

void PhongLightingWidget::set_constant(const int constant)
{
    last_constant = constant;
}

void PhongLightingWidget::generate_terrain()
{
    makeCurrent();
    example.change_map(current_scene_, last_constant, last_order);
    // doneCurrent();
}

void PhongLightingWidget::apply_erosion()
{
    makeCurrent();
    example.apply_thermal_erosion(current_scene_, erosion_times_);
    // doneCurrent();
}

void PhongLightingWidget::delete_erosion()
{
    makeCurrent();
    example.delete_thermal_erosion(current_scene_);
    // doneCurrent();
}


void PhongLightingWidget::set_order(const int order)
{
    last_order = static_cast<float>(order) / 100.f;
}

void PhongLightingWidget::set_erosion(int erosion_times)
{
    erosion_times_ = erosion_times;
}


PhongLightingWidget::PhongLightingWidget(QWidget* parent)
	:   QOpenGLWidget{ parent },
		render_dialog_{*this },
		lighting_dialog_{*this}
{
	setFocusPolicy(Qt::ClickFocus);
	connect(&fps_counter_, &FPSCounter::emit_fps, this, &PhongLightingWidget::catch_fps);
}


void PhongLightingWidget::keyPressEvent(QKeyEvent* event)
{
	if(CameraMover::keys.count(event->key())) {
		CameraMover::keys[event->key()] = true;
	}
}

void PhongLightingWidget::keyReleaseEvent(QKeyEvent* event)
{
    if (CameraMover::keys.count(event->key())) {
        CameraMover::keys[event->key()] = false;
    }
}

void PhongLightingWidget::wheelEvent(QWheelEvent* event)
{
    QPoint num_degrees = event->angleDelta() / 8;

    if (!num_degrees.isNull()) {
        QPoint num_steps = num_degrees / 15;
        current_scene_.camera_mover.update_camera_zoom(num_steps.y());
    }

    event->accept();
}

void PhongLightingWidget::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->screenPos().x() - current_scene_.camera_mover.mouse_pos_x;
    int dy = event->screenPos().y() - current_scene_.camera_mover.mouse_pos_y;
    current_scene_.camera_mover.camera.rotate(float(dy) / 5, 1 * float(dx) / 5);
}

void PhongLightingWidget::keyEvent()
{
    current_scene_.camera_mover.set_camera_speed(fps_counter_.delta_time());
    current_scene_.camera_mover.move();
}

void PhongLightingWidget::mouseEvent()
{
    current_scene_.camera_mover.mouse_pos_x = QCursor::pos().x();
    current_scene_.camera_mover.mouse_pos_y = QCursor::pos().y();
}

void PhongLightingWidget::show_shininess_dialog()
{
    lighting_dialog_.show();
}

void PhongLightingWidget::initializeGL()
{

    const auto retina_scale = static_cast<GLsizei>(devicePixelRatio());    

    renderer_.init(width(), height(), retina_scale);
    example.fill_scene(current_scene_, true);
}

void PhongLightingWidget::paintGL()
{
    fps_counter_.calculate_fps();

    auto max_h = example.max_h;
    auto min_h = example.min_h;
    current_scene_.objects.front()->renderer->shader_program_->setUniformValue("hMin", static_cast<float>(min_h));
    current_scene_.objects.front()->renderer->shader_program_->setUniformValue("hMax", static_cast<float>(max_h));
	
    keyEvent();
    mouseEvent();

    renderer_.render(current_scene_);
    update();
}

