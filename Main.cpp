#include <QApplication>

#include "XUeMainWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	XUeMainWindow window;
	window.show();
	app.exec();
}
