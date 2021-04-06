#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QTextCodec>
#include <QDebug>
#include "dialogchatslist.h"
#include "dialogpasswordenter.h"
#include "settings.h"
#include "dialogtoken.h"
#include "dialogcreatepassword.h"

#include "aesfacade.h"

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QWidget *parent = nullptr);
    ~DialogSettings();

signals:
    void saved();

private slots:

    void on_btEditChatsList_clicked();

    void on_btShowToken_clicked();

    void on_chbUseKeyCry_stateChanged(int arg1);

    void on_buttonBoxAct_accepted();

private:
    Ui::DialogSettings *ui;
    Settings *settingsHandler;

    void createPassword();
};

#endif // DIALOGSETTINGS_H
