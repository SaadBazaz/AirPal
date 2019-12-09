#include "AirPal.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AirPal w;
	w.show();
	return a.exec();
}
