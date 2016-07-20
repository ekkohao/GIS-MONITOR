#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QString>
#include <QStringList>
#include "include/dbcon.h"
#include "portselect.h"
//#include <QWidget>
//#include <QStatusBar>
//#include <QLabel>



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->initWindow();

    this->connect(ui->openPortAction,SIGNAL(triggered()),this,SLOT(openPortSelectUIslot()));
    this->connect(ui->closePortAction,SIGNAL(triggered()),this,SLOT(closeThePortSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{

	/**************************/
	dbcon mydb;
	QStringList phoneNumberList;
	mydb.get_phonenumbers(phoneNumberList);
}

void MainWindow::openPortSelectUIslot()
{
    portSelectForm.mainform=this;
    portSelectForm.show();
}

void MainWindow::openThePort(unsigned int portNumber)
{
    if(ThePort.InitPort(portNumber,CBR_115200)){
        ui->openPortAction->setEnabled(false);
        ui->closePortAction->setEnabled(true);
        ThePort.OpenListenThread();
    }
    else{
        ui->openPortAction->setEnabled(true);
        ui->closePortAction->setEnabled(false);
    }
    portSelectForm.close();
}

void MainWindow::closeThePortSlot()
{
    ThePort.CloseListenTread();
    ThePort.ClosePort();
    ui->openPortAction->setEnabled(true);
    ui->closePortAction->setEnabled(false);
}


