#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProgressDialog>
#include "dialogsettings.h"
#include "vkApi/vkapi.h"
#include "messageassembler.h"
#include "vkApi/vkmessagedelivery.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QCheckBox* getFloorChk (int floor);
private slots:
    void on_actionSettings_triggered();

    void on_actionAboutQt_triggered();

    void on_actionExit_triggered();

    void on_actionAboutProgram_triggered();

    void on_btCheckAllFloors_clicked();

    void on_btSend_clicked();
    void on_ptxtedMessageText_textChanged();

    void on_chkAddAttentionStr_stateChanged(int arg1);

    void on_chkPingAll_stateChanged(int arg1);

    void on_chkAddSignature_stateChanged(int arg1);

public slots:
    void VkApiRequestFinished(QJsonDocument r);
    void onSettingsUpdated();

private:
    Ui::MainWindow *ui;
    void updateMsgPreview();
    Settings *m_settings;
    QHash<uint8_t, QCheckBox*> m_chBoxFloorMap;
};
#endif // MAINWINDOW_H
