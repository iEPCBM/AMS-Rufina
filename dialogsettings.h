#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QTextCodec>
#include <QDebug>
#include <QFileDialog>
#include "dialogchatslist.h"
#include "dialogpasswordenter.h"
#include "settings.h"
#include "dialogtoken.h"
#include "dialogcreatepassword.h"
#include "dialogs/dialogedittoken.h"
#include "aesfacade.h"

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(Settings *settings, QWidget *parent = nullptr);
    ~DialogSettings();

    void update();

signals:
    void saved(Settings*);

public slots:
    void onApplied();

private slots:

    void on_btEditChatsList_clicked();

    void on_btShowToken_clicked();

    void on_buttonBoxAct_accepted();

    void on_chbUseKeyCry_clicked(bool checked);

    void on_btEditKey_clicked();

    void on_btEditToken_clicked();

    void on_btExportSettings_clicked();

    void on_btImportSettings_clicked();

    void on_buttonBoxAct_rejected();

private:
    Ui::DialogSettings *ui;
    Settings *settingsHandler;

    bool createPassword();
    void saveSettings();

    inline void setEncryptedFlag(bool checked);
};

#endif // DIALOGSETTINGS_H
