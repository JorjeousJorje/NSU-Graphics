#include "OpenGLWindow.h"


OpenGLWindow::OpenGLWindow(ShaderParser& parser, QWindow* parent)
	:  QWindow{parent}, shader_parser_{parser}
{
	setSurfaceType(OpenGLSurface);
}


void OpenGLWindow::renderLater()
{
	requestUpdate();
}


void OpenGLWindow::renderNow()
{
	if (!isExposed()) {
		return;
	}

	if(need_initialization_) {
		Initialize();
		need_initialization_ = false;
	}
	context_->makeCurrent(this);
	
	Render();

	context_->swapBuffers(this);

	if (animating_) {
		renderLater();
	}
}


void OpenGLWindow::initShaders()
{
	auto [vertex_code, fragment_code] = shader_parser_.parse();
	const auto vertex_bool = program_.addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_code);
	const auto fragment_bool = program_.addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_code);
	
	if(!vertex_bool || !fragment_bool) {
		close();
		return;
	}
	if(!program_.link()) {
		close();
	}
}


OpenGLWindow::~OpenGLWindow()
{
	delete context_;
}


void OpenGLWindow::setAnimating(const bool animating)
{
	animating_ = animating;

	if (animating) {
		renderLater();
	}
}


bool OpenGLWindow::event(QEvent* event)
{
	switch (event->type()) {
	case QEvent::UpdateRequest:
		renderNow();
		return true;
	default:
		return QWindow::event(event);
	}
}


void OpenGLWindow::exposeEvent(QExposeEvent* event)
{
	Q_UNUSED(event)

	if (isExposed()) {
		renderNow();
	}
}
