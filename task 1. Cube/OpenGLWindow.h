#pragma once
#include <QWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "ShaderParser.h"

#include "Geometry.h"

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	explicit OpenGLWindow(ShaderParser& parser, QWindow* parent = nullptr);
	~OpenGLWindow() override;

	virtual void Render(QPainter* painter) = 0;
	virtual void Render() = 0;
	virtual void Initialize() = 0;
	
	void setAnimating(bool animating);

public slots:
	void renderLater();
	void renderNow();

protected:
	bool event(QEvent* event) override;
	void exposeEvent(QExposeEvent* event) override;

	bool animating_{ false };
	bool need_initialization_{ true };
	int frame_count_ = 0;
	
	QOpenGLContext* context_{ nullptr };
	QOpenGLShaderProgram program_{ this };
	ShaderParser& shader_parser_;

	void initShaders();
	virtual void resizeGL() = 0;
};
