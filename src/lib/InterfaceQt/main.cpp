#include <unistd.h>
#include <QApplication>

#include "mainwindowphotoshop.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	close(2);
	MainWindowPhotoShop w;
	w.show();
	return a.exec();
}
