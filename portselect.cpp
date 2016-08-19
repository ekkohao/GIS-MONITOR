#include "portselect.h"
#include "ui_portselect.h"
#include <Windows.h>
#include <QString>
#include <QListWidget>

portselect::portselect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::portselect)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
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
    this->done(portNum);
    this->close();

}
