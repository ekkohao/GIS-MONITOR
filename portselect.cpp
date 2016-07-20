#include "portselect.h"
#include "ui_portselect.h"
#include <Windows.h>
#include <QString>
#include <QListWidget>
#include "mainwindow.h"

portselect::portselect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::portselect)
{
    ui->setupUi(this);
}

portselect::~portselect()
{
    delete ui;
}

void portselect::updateCurrentPort()
{

}

void portselect::on_pushButton_clicked()
{
    QString comQStr(ui->listWidget->currentItem()->text());
    int portNum=comQStr.remove(0,3).toInt();
    MainWindow *w=(MainWindow *)mainform;
    w->openThePort(portNum);
}
