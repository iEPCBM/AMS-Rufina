#ifndef DIALOGPASSWORDENTER_H
#define DIALOGPASSWORDENTER_H

#include <QDialog>

namespace Ui {
class DialogPasswordEnter;
}

class DialogPasswordEnter : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPasswordEnter(QWidget *parent = nullptr);
    ~DialogPasswordEnter();

private:
    Ui::DialogPasswordEnter *ui;
};

#endif // DIALOGPASSWORDENTER_H
