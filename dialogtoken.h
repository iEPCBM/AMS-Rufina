#ifndef DIALOGTOKEN_H
#define DIALOGTOKEN_H

#include <QDialog>

namespace Ui {
class DialogToken;
}

class DialogToken : public QDialog
{
    Q_OBJECT

public:
    explicit DialogToken(QWidget *parent = nullptr);
    ~DialogToken();

    void setToken(const QString &strToken);

private:
    inline void displayToken();
    QString m_strToken;
    Ui::DialogToken *ui;
};

#endif // DIALOGTOKEN_H
