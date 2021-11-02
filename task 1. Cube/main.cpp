#include <QApplication>
#include "CubeWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QSurfaceFormat format;
	format.setSamples(32);

	ShaderParser parser{ "Resources/vshader.glsl", "Resources/fshader.glsl" };

	CubeWindow window{ parser };
	window.setFormat(format);
	window.resize(800, 600);
	window.show();

	window.setAnimating(true);
	
	return app.exec();
}
