#ifndef PORTSELECT_H
#define PORTSELECT_H

#include <QDialog>
#include <QStringList>
#include "include/haohelp.h"

namespace Ui {
class portselect;
}

class portselect : public QDialog
{
    Q_OBJECT

public:
    explicit portselect(QWidget *parent = 0);
    ~portselect();
    void updateCurrentPort();

private slots:
    void on_pushButton_clicked();

private:
     Ui::portselect *ui;
};

#endif // PORTSELECT_H
