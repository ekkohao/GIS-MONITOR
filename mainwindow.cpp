#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QString>
#include <QStringList>
#include "include/dbcon.h"
//#include <QWidget>
//#include <QStatusBar>
//#include <QLabel>



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->initWindow();
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


