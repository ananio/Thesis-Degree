#include "fress.h"
#include "about.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Fress w;

	w.show();

	return a.exec();
}
