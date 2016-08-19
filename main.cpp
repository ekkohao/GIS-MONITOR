#include "mainwindow.h"
#include "include/haohelp.h"
#include <QApplication>
#include <QTextCodec>
#include <QString>
#include <QSharedMemory>
#include <QMessageBox>

int assumeSingleInstance(const char* program);
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


    if(assumeSingleInstance("topo-client.lock") < 0)
    {
        QMessageBox::information(NULL, "提示","GIS监测终端已打开");
        return -1;
    }
//    //qt版本低于qt5
//	#if QT_VERSION < QT_VERSION_CHECK(5,0,0)

//	//VS版本低于VS2010

//	#if defined(_MSC_VER) && (_MSC_VER < 1600)

//		QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

//	#else

//		QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

//	#endif

//	#endif


    MainWindow w;
    w.show();
    return a.exec();
}
int assumeSingleInstance(const char* program)
{
    static QSharedMemory shm(program);
    if(shm.create(100) == false)
    {
        return -1;
    }
    return 0;
}
