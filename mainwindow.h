/*
 *  AMS Rufina - automated message delivery program
 *  Copyright (C) 2021 Rishat D. Kagirov (iEPCBM)
 *
 *     This file is part of AMS Rufina.
 *
 *  AMS Rufina is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProgressDialog>
#include "dialogs/dialogsettings.h"
#include "vkApi/vkapi.h"
#include "messageassembler.h"
#include "vkApi/vkmessagedelivery.h"
#include "settings.h"
#include "AppInfo.h"
#include "dialogs/dialoglicenseview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
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

    void on_btUncheckAllFloors_clicked();

    void on_actionLicenseText_triggered();

public slots:    void onSettingsUpdated(Settings *settings);

private:
    Ui::MainWindow *ui;
    void updateMsgPreview();
    void update();
    void toggleFloorChechBoxes(bool state);
    void afterSentMessage(QHash<uint8_t, bool> data);
    bool checkUsersData();
    Settings *m_settings;
    QHash<uint8_t, QCheckBox*> m_chBoxFloorMap;
};
#endif // MAINWINDOW_H
