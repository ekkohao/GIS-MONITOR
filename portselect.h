#ifndef PORTSELECT_H
#define PORTSELECT_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class portselect;
}

class portselect : public QWidget
{
    Q_OBJECT

public:
    explicit portselect(QWidget *parent = 0);
    ~portselect();
    void updateCurrentPort();
    void *mainform;

private slots:
    void on_pushButton_clicked();

private:
     Ui::portselect *ui;
};

#endif // PORTSELECT_H
