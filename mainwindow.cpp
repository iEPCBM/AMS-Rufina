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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_settings = Settings::getInstance();
    QList<QCheckBox*> lstFloorsChb = ui->frmFloorsContainer->findChildren<QCheckBox*>();
    foreach (QCheckBox* checkBoxFloor, lstFloorsChb) {
        m_chBoxFloorMap[checkBoxFloor->property("floorNumber").value<uint8_t>()] = checkBoxFloor;
    }
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_settings;
}

void MainWindow::on_actionSettings_triggered()
{
    DialogSettings dSettings(this);
    connect(&dSettings, SIGNAL(saved(Settings*)), this, SLOT(onSettingsUpdated(Settings*)));
    dSettings.exec();
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionAboutProgram_triggered()
{
    QMessageBox::about(this, "О САОС Руфина", AppInfo::buildAboutText());
}

void MainWindow::on_btCheckAllFloors_clicked()
{
    toggleFloorChechBoxes(true);
}

void MainWindow::on_btSend_clicked()
{
    if (!checkUsersData()) {
        return;
    }

    MessageAssembler masm(m_settings, ui->ptxtedMessageText->toPlainText(), ui->chkAddAttentionStr->isChecked(), ui->chkPingAll->isChecked(), ui->chkAddSignature->isChecked());
    QString token = "";
    if (m_settings->isEncrypted()) {
        DialogPasswordEnter dlgPasswEnter(QByteArray::fromBase64(m_settings->getVkToken().toUtf8()),
                                          QByteArray::fromHex(m_settings->getInitializeVector().toUtf8()), this);
        dlgPasswEnter.exec();
        if (dlgPasswEnter.isSuccessful()) {
            token = QString::fromUtf8(dlgPasswEnter.getDecryptedData());
        } else {
            return;
        }
    } else {
        token = m_settings->getVkToken();
    }

    QList<uint8_t> floors = m_chBoxFloorMap.keys();
    QList<uint8_t> checkedFloors;
    foreach (uint8_t floor, floors) {
        if (m_chBoxFloorMap[floor]->isChecked()) {
            checkedFloors.append(floor);
        }
    }

    VkMessageDelivery msgDelivery(token, this);
    QHash<uint8_t, bool> isSentMsgList;
    QProgressDialog dlgSending("Отправка сообщения", "Отмена", 0, checkedFloors.length(), this);
    dlgSending.setWindowModality(Qt::WindowModal);
    dlgSending.show();
    bool hasCriticalError = false;
    int progress = 0;
    foreach(uint8_t floor, checkedFloors) {
        dlgSending.setLabelText("Отправка сообщения в \"" + m_settings->getChats()[floor].getTitle() + "\"");
        msgDelivery.sendMessage(VK_API_MULTICHAT_BASE_ID+m_settings->getChats()[floor].getId(), masm.assembly());
        if(msgDelivery.hasError()) {
            VkError vkErr = msgDelivery.getVkError();
            if (vkErr.hasError()) {
                QMessageBox::StandardButton resultMsgBox = ErrorMessages::errorVkApi(this, vkErr.code(), vkErr.description()+
                                          "\nОшибка возникла при отправке сообщения в беседу: \""+
                                          m_settings->getChats()[floor].getTitle()+
                                          "\" (ID: "+QString::number(m_settings->getChats()[floor].getId())+").", QMessageBox::Ok|QMessageBox::Abort);
                if (resultMsgBox == QMessageBox::Abort) {
                    dlgSending.cancel();
                }
            } else {
                hasCriticalError = true;
                dlgSending.cancel();
            }
            isSentMsgList[floor]=false;
        }
        else {
            isSentMsgList[floor]=true;
        }
        if (dlgSending.wasCanceled())
            break;
        dlgSending.setValue(++progress);
    }
    dlgSending.setValue(checkedFloors.length());
    if (!hasCriticalError) {
        afterSentMessage(isSentMsgList);
    }
}

void MainWindow::updateMsgPreview()
{
    MessageAssembler masm(m_settings, ui->ptxtedMessageText->toPlainText(), ui->chkAddAttentionStr->isChecked(), ui->chkPingAll->isChecked(), ui->chkAddSignature->isChecked());
    ui->txtedPreview->setPlainText(masm.assembly());
}

void MainWindow::update()
{
    QList<uint8_t> floors = m_chBoxFloorMap.keys();
    foreach (uint8_t floor, floors) {
        bool isContains = m_settings->getChats().contains(floor);
        m_chBoxFloorMap[floor]->setEnabled(isContains);
        m_chBoxFloorMap[floor]->setChecked(m_chBoxFloorMap[floor]->isChecked()&isContains);
        if (isContains) {
            m_chBoxFloorMap[floor]->setToolTip(m_settings->getChats()[floor].getTitle());
        } else {
            m_chBoxFloorMap[floor]->setToolTip("");
        }
    }
    updateMsgPreview();
}

void MainWindow::on_ptxtedMessageText_textChanged()
{
    updateMsgPreview();
}

void MainWindow::on_chkAddAttentionStr_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
    updateMsgPreview();
}

void MainWindow::on_chkPingAll_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
    updateMsgPreview();
}

void MainWindow::on_chkAddSignature_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
    updateMsgPreview();
}

void MainWindow::onSettingsUpdated(Settings *settings)
{
    m_settings = settings;
    update();
}

void MainWindow::on_btUncheckAllFloors_clicked()
{
    toggleFloorChechBoxes(false);
}

void MainWindow::toggleFloorChechBoxes(bool state)
{
    QList<uint8_t> floors = m_chBoxFloorMap.keys();
    foreach (uint8_t floor, floors) {
        m_chBoxFloorMap[floor]->setChecked(state&m_chBoxFloorMap[floor]->isEnabled());
    }
}

void MainWindow::afterSentMessage(QHash<uint8_t, bool> data)
{
    QList<uint8_t> floors = data.keys();
    QString successfulSend = "";
    QString failedSend = "";
    foreach (uint8_t floor, floors) {
        QString chatData = QString("\"") + m_settings->getChats()[floor].getTitle() + "\" (" + QString::number(floor) + " этаж)\n";
        if (data[floor]) {
            successfulSend += chatData;
        }
        else {
            failedSend += chatData;
        }
    }
    QString msgText = (successfulSend.isEmpty()?QString():(QString("Сообщение было отправлено в беседу(ы):\n") + successfulSend)) +
                      (failedSend.isEmpty()?"":("\nВозникла ошибка при отправке сообщения в беседу(ы):\n" + failedSend));
    QMessageBox::information(this, "Отчет об отправке", msgText.trimmed());
}

bool MainWindow::checkUsersData()
{
    QList<QCheckBox*> chBoxChats = m_chBoxFloorMap.values();
    bool isOneChBoxChecked = false;
    foreach (QCheckBox* chBoxChat, chBoxChats) {
        isOneChBoxChecked |= chBoxChat->isChecked();
    }
    if (!isOneChBoxChecked) {
        QMessageBox::warning(this, "Ошибка", "Ни одна из бесед не отмечена. Для отправки сообщения отметьте хотя бы одну беседу.");
        return false;
    }

    MessageAssembler masm(m_settings, ui->ptxtedMessageText->toPlainText(), ui->chkAddAttentionStr->isChecked(), ui->chkPingAll->isChecked(), ui->chkAddSignature->isChecked());
    if (masm.assembly().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сообщение пустое!");
        return false;
    }
    return true;
}

void MainWindow::on_actionLicenseText_triggered()
{
    DialogLicenseView dlgLicenseView(this);
    dlgLicenseView.exec();
}
