#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMenu>
#include <QMainWindow>
#include <QSystemTrayIcon>
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
    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayIconMenu;
    Ui::MainWindow *ui;
    portselect portSelectForm;
	CSerialPort ThePort;
private slots:
    void iconActivatedSlot(QSystemTrayIcon::ActivationReason reason);
	void openPortSelectUISlot();
    void closeThePortSlot();
    void SlotAppendText(const QString &text);
    void on_closeAppAction_triggered();
};

#endif // MAINWINDOW_H
