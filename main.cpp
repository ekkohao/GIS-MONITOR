#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

#if _MSC_VER >= 1600

#pragma execution_character_set("utf-8")

#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//qt版本低于qt5

	#if QT_VERSION < QT_VERSION_CHECK(5,0,0)

	//VS版本低于VS2010

	#if defined(_MSC_VER) && (_MSC_VER < 1600)

		QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

	#else

		QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	#endif

	#endif


    MainWindow w;
    w.show();
    return a.exec();
}
