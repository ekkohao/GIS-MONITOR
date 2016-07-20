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

	this->connect(ui->openPortAction,SIGNAL(triggered()),this,SLOT(openPortSelectUISlot()));
    this->connect(ui->closePortAction,SIGNAL(triggered()),this,SLOT(closeThePortSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
	ThePort.MainForm=this;
	/**************************/
}

void MainWindow::openPortSelectUISlot()
{
	portSelectForm.mainform=this;
    portSelectForm.show();
}

void MainWindow::openThePort(unsigned int portNumber)
{
	QString msg=QString::fromLocal8Bit("端口COM%1").arg(portNumber);
	if(ThePort.InitPort(portNumber,CBR_115200)){
        ui->openPortAction->setEnabled(false);
        ui->closePortAction->setEnabled(true);
		ThePort.OpenListenThread();
		msg+=QString::fromLocal8Bit("打开成功");
		ui->statusBar->showMessage( msg, 3000);
    }
	else{
		msg+=QString::fromLocal8Bit("打开失败");
		ui->statusBar->showMessage(msg, 3000);
    }
    portSelectForm.close();
}

void MainWindow::closeThePortSlot()
{
	ThePort.CloseListenTread();
	ThePort.ClosePort();
    ui->openPortAction->setEnabled(true);
    ui->closePortAction->setEnabled(false);
	ui->statusBar->showMessage(QString::fromLocal8Bit("串口关闭成功"), 3000);
}

void MainWindow::dataRecievd(char *recievd)
{
	QString QStrreceived=recievd;
	if(QStrreceived.startsWith("Flag=")&&QStrreceived.contains("Series=")&&QStrreceived.contains("Action=")){
		char *prevW="ate0";
		ThePort.WriteData(prevW,strlen(prevW));
		QString devNum=QStrreceived.section(",",1,1).remove("Series=");
		QString actionCount=QStrreceived.section(",",2,2).remove("Action=");
		QString actionTime=QStrreceived.section(",",3,3).remove("Time=");
		QString iNum=QStrreceived.section(",",4,4).remove("I=");
		QString tem=QStrreceived.section(",",5,5).remove("Tem=");
		QString hum=QStrreceived.section(",",5,5).remove("Hum=").remove("\r\n");
		actionTime.insert(12,"秒").insert(10,"分").insert(8,"时").insert(6,"日").insert(4,"月").insert(2,"年");
		QString preW1="AT^SMS=";
		QString preW2=QString::fromLocal8Bit(" \"设备%1于%2发生报警动作，动作次数%3次，泄漏电流%4uA,温度%5℃，湿度%6%%\r\n\"").arg(devNum,actionTime,actionCount,iNum,tem,hum);
		QString preW;
		dbcon mydb;
		QStringList phoneNumberList;
		mydb.get_phonenumbers(phoneNumberList);
		for(int i=0;i<phoneNumberList.size();i++){
			preW.clear();
			preW=preW1+phoneNumberList.at(i)+preW2;
			char readyW[1024];
			strcpy(readyW,preW.toStdString().data());
			ThePort.WriteData(readyW,strlen(readyW));
		}
	}
}

