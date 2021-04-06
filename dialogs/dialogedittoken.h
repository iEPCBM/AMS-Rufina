#ifndef DIALOGEDITTOKEN_H
#define DIALOGEDITTOKEN_H

#include <QDialog>

namespace Ui {
class DialogEditToken;
}

class DialogEditToken : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditToken(QWidget *parent = nullptr);
    ~DialogEditToken();

private:
    Ui::DialogEditToken *ui;
};

#endif // DIALOGEDITTOKEN_H
