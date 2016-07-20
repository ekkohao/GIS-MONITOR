#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "portselect.h"
#include "include/serialport.h"

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
    void openThePort(unsigned int portNumber);


private:
    Ui::MainWindow *ui;
    portselect portSelectForm;
    CSerialPort ThePort;
private slots:
    /*打开选择端口界面*/
    void openPortSelectUIslot();
    void closeThePortSlot();
};

#endif // MAINWINDOW_H
