#include "CubeWindow.h"
#include <QMouseEvent>
#include <QScreen>

void CubeWindow::setRotation()
{
	angular_speed_ *= 0.99;

	if (angular_speed_ < 0.01) {
		angular_speed_ = 0.0;
	}
	else {
		rotation_ = QQuaternion::fromAxisAndAngle(rotation_axis_, angular_speed_) * rotation_;
	}
}

void CubeWindow::initColorDialog()
{
	color_dialog_.setGeometry(50, 50, 100, 100);
	color_dialog_.show();
	color_dialog_.setOption(QColorDialog::NoButtons);
}

void CubeWindow::initSlidersDialog()
{
	slider_x_.setOrientation(Qt::Orientation::Horizontal);
	slider_y_.setOrientation(Qt::Orientation::Horizontal);
	slider_z_.setOrientation(Qt::Orientation::Horizontal);
	slider_x_.setGeometry(50, 217, 230, 50);
	slider_y_.setGeometry(50, 234, 230, 50);
	slider_z_.setGeometry(50, 251, 230, 50);
}

void CubeWindow::mousePressEvent(QMouseEvent* e)
{
	mouse_press_position_ = QVector2D(e->screenPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent* e)
{
	QVector2D diff = QVector2D(e->screenPos()) - mouse_press_position_;
	QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized(); 

	qreal acc = diff.length() / 100.0f; 

	rotation_axis_ = (rotation_axis_ * angular_speed_ + n * acc).normalized();
	angular_speed_ += acc;
}

void CubeWindow::Initialize()
{
	context_ = new QOpenGLContext(this);
	context_->setFormat(requestedFormat());
	context_->create();
	context_->makeCurrent(this);

	initializeOpenGLFunctions();
	initColorDialog();
	initSlidersDialog();
	initShaders();

	const auto retina_scale = static_cast<GLsizei>(devicePixelRatio());
	glViewport(0, 0, width() * retina_scale, height() * retina_scale);

	glClearColor(0.1f, 0.3f, 0.3f, 1);

	// чтоб корректно отображать что грани и рёбра относительно друг друга
	glEnable(GL_DEPTH_TEST);
	// Now we will render only those elements whom normal vector directs us
	// Отрисовываем то, что видим.
	// Для поверхностей 
	glEnable(GL_CULL_FACE);
}

void CubeWindow::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(!program_.bind()) {
		close();
	}
		
	QMatrix4x4 matrix;
	resizeGL();
	setRotation();
	matrix.translate(0.0, 0.0, -3.0);
	//matrix.rotate(static_cast <GLfloat>(100 * frame_count_ / screen()->refreshRate()), 0.5f, 1.0f, 0.5f);
	
	matrix.rotate(rotation_);
	
	const auto matrix_location = program_.uniformLocation("matrix");
	Q_ASSERT(matrix_location != -1);
		
	program_.setUniformValue(matrix_location, projection_* matrix);

	// отрисовавыем те значения z, которые для нас "больше", то есть скрываем меньшие
	glDepthFunc(GL_LESS);
	// нормаль от нас не показывается
	glCullFace(GL_BACK);

	painter_.setUniformColor(color_dialog_.currentColor());
	
	cube_geometry_.DrawGeometry(&program_);
	edges_geometry_.DrawGeometry(&program_);
	
	program_.release();
		
	++frame_count_;
}

void CubeWindow::resizeGL()
{
	const auto ratio = static_cast<float>(width()) / static_cast<float>(height());
	const auto near_plane = 0.1f, far_plane = 100.0f, fov = 45.0f;
	
	projection_.setToIdentity();
	projection_.perspective(fov, ratio, near_plane, far_plane);
}
