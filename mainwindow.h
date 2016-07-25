#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "portselect.h"
#include "include/serialport.h"
#include "include/dbcon.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void initWindow();
    dbcon mydb;
    void openThePort(unsigned int portNumber);
	void dataRecievd(char *recievd);
    void Append(const QString &text);
    void tableAddNewRow(QString &Time,QString &devNum,QString &actionCount,QString &iNum,QString &tem,QString &hum);
signals:
    void AppendText(const QString &text);
private:
    Ui::MainWindow *ui;
    portselect portSelectForm;
	CSerialPort ThePort;
private slots:
    /*打开选择端口界面*/
	void openPortSelectUISlot();
    void closeThePortSlot();
    void SlotAppendText(const QString &text);
};

#endif // MAINWINDOW_H
