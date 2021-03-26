#ifndef DIALOGCREATEPASSWORD_H
#define DIALOGCREATEPASSWORD_H

#include <QDialog>
#include <QPushButton>
namespace Ui {
class DialogCreatePassword;
}

class DialogCreatePassword : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreatePassword(QWidget *parent = nullptr);
    ~DialogCreatePassword();

    QString getPassword() const;

private slots:
    void on_lePasswordConfirm_textEdited(const QString &arg1);

    void on_lePassword_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::DialogCreatePassword *ui;
    inline bool checkPassword();

    QString m_strPassword;
};

#endif // DIALOGCREATEPASSWORD_H
