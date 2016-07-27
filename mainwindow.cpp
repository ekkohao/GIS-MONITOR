#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QString>
#include <QStringList>
#include <QMetaType>
#include <QDateTime>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "include/dbcon.h"
#include "portselect.h"
//#include <QWidget>
//#include <QStatusBar>
//#include <QLabel>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*注册信号传递类型*/
    qRegisterMetaType<QVector<int>>("QVector<int>");
	this->initWindow();


	this->connect(ui->openPortAction,SIGNAL(triggered()),this,SLOT(openPortSelectUISlot()));
    this->connect(ui->closePortAction,SIGNAL(triggered()),this,SLOT(closeThePortSlot()));
    this->connect(this,SIGNAL(AppendText(QString)),this,SLOT(SlotAppendText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
	ThePort.MainForm=this;
    if(!mydb.isopen)
        ui->statusBar->showMessage(QString::fromLocal8Bit("数据库连接失败，请检查连接"), 30000);
    else
        ui->statusBar->showMessage(QString::fromLocal8Bit("数据库连接成功"), 3000);
	/**************************/
}

void MainWindow::openPortSelectUISlot()
{
    portSelectForm.mainform=this;
    portSelectForm.show();
}


void MainWindow::openThePort(unsigned int portNumber)
{
    QString msg=QString::fromLocal8Bit("串口COM%1").arg(portNumber);
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
    QString QStrreceived=recievd;//2016.07.27
    CSerialPort::portRestore.append(recievd);
//    qDebug()<<QStrreceived;
    while(CSerialPort::portRestore.size()>=77){
        if(QStrreceived.startsWith("Flag=")&&QStrreceived.contains("Series=")&&QStrreceived.contains("Action=")){
            char prevW[]="ate0\r\n";
            int flag=QStrreceived.section(",",0,0).remove("Flag=").toInt();
    //        qDebug()<<"yy"<<QStrreceived.section(",",0,0).remove("Flag=");
    //        qDebug()<<"yy"<<flag;
            QString devNum=QStrreceived.section(",",1,1).remove("Series=");
            QString actionCount=QStrreceived.section(",",2,2).remove("Action=");
            QString actionTime=QStrreceived.section(",",3,3).remove("Time=");
            QString iNum=QStrreceived.section(",",4,4).remove("I=");
            QString tem=QStrreceived.section(",",5,5).remove("Tem=");
            QString hum=QStrreceived.section(",",6,6).remove("Hum=").remove("\r\n");
            QString alarmTime(actionTime);
            alarmTime.insert(10,":").insert(8,":").insert(6," ").insert(4,"-").insert(2,"-").insert(0,"20");
            if(flag==1){
                Append("-----"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"-----");
                Append(QString::fromLocal8Bit("收到设备%1报警，正在处理数据...").arg(devNum));

                if(!mydb.isopen)
                    mydb.open();
                if(mydb.isopen){
                    unsigned int devId=0;
                    devId=mydb.get_dev_id(devNum);
                    if(devId==0)
                        Append(QString::fromLocal8Bit("由于数据库未添加%1设备，添加报警信息到数据库失败").arg(devNum));
                    else{
                        AlarmInfo alarm{devId,alarmTime,actionCount.toUInt(),iNum.toUInt(),tem,hum};
                        mydb.insert_alarm(alarm,flag);
                    }
                }
                else{
                    Append(QString::fromLocal8Bit("数据库连接失败,请检查网络"));
                }

                tableAddNewRow(alarmTime,devNum,actionCount,iNum,tem,hum);

                actionTime.insert(12,QString::fromLocal8Bit("秒")).insert(10,QString::fromLocal8Bit("分")).insert(8,QString::fromLocal8Bit("时")).insert(6,QString::fromLocal8Bit("日")).insert(4,QString::fromLocal8Bit("月")).insert(2,QString::fromLocal8Bit("年"));

                QString preW1="AT^SMS=";
                QString preW2=QString::fromLocal8Bit(" \"设备%1于20%2发生报警动作，动作次数%3次，泄漏电流%4uA,温度%5℃，湿度%6%\"\r\n").arg(devNum,actionTime,actionCount,iNum,tem,hum);
                QString preW;

                QStringList phoneNumberList;
                if(mydb.isopen)
                    mydb.get_phonenumbers(phoneNumberList);
                Append(QString::fromLocal8Bit("数据处理完毕"));
                if(phoneNumberList.size()<1){
                    Append(QString::fromLocal8Bit("无发送手机列表"));
                }
                else{
                    for(int i=0;i<phoneNumberList.size();i++){
                        if(phoneNumberList.at(i)=="0")
                            continue;
                        ThePort.WriteData(prevW,strlen(prevW));
                        Sleep(800);
                        preW.clear();
                        preW=preW1+phoneNumberList.at(i)+preW2;
                        char readyW[1024];
                        strcpy(readyW,preW.toLocal8Bit().toStdString().data());
                        ThePort.WriteData(readyW,strlen(readyW));
                        Append(QString::fromLocal8Bit("已发送短信至%1").arg(phoneNumberList.at(i)));
                        Sleep(800);
                    }
                }
            }
            else{
                if(mydb.isopen){
                    unsigned int devId=0;
                    devId=mydb.get_dev_id(devNum);
                    if(devId==0)
                        Append(QString::fromLocal8Bit("由于数据库未添加%1设备，添加历史信息到数据库失败").arg(devNum));
                    else{
                        AlarmInfo alarm{devId,alarmTime,actionCount.toUInt(),iNum.toUInt(),tem,hum};
                        mydb.insert_alarm(alarm,flag);
                    }
                }
                else{
                    Append(QString::fromLocal8Bit("数据库连接失败,请检查网络和数据库服务"));
                }
            }
        }
    }

}
void MainWindow::Append(const QString &text)
{
    emit AppendText(text);
}
void MainWindow::SlotAppendText(const QString &text)
{
    ui->iologText->append(text);
}
void MainWindow::tableAddNewRow(QString &Time,QString &devNum,QString &actionCount,QString &iNum,QString &tem,QString &hum)
{
    int rowCount=ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rowCount+1);
    ui->tableWidget->setItem(rowCount,5,new QTableWidgetItem(Time));
    ui->tableWidget->setItem(rowCount,0,new QTableWidgetItem(devNum));
    ui->tableWidget->setItem(rowCount,1,new QTableWidgetItem(actionCount));
    ui->tableWidget->setItem(rowCount,2,new QTableWidgetItem(iNum));
    ui->tableWidget->setItem(rowCount,3,new QTableWidgetItem(tem));
    ui->tableWidget->setItem(rowCount,4,new QTableWidgetItem(hum));
    //ui->tableWidget->resizeColumnsToContents();
}
