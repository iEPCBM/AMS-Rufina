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
    explicit DialogEditToken(QString token, QWidget *parent = nullptr);
    ~DialogEditToken();

    QString token() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogEditToken *ui;
    QString m_token;
};

#endif // DIALOGEDITTOKEN_H
