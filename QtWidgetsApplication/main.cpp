#include <QtWidgets/QApplication>
#include <QDebug>
#include "QtWidgetsApplication1.h"
#include "QtWidgetsClass.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//
	// QtWidgetsApplication1 w;

	QtWidgetsClass w2;
	w2.show();

   //w.show();
    return a.exec();
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j < i; j++) {
			int count = i * j;
			qDebug() << i << "*" << j << "=" << count;
		}
	}
}
