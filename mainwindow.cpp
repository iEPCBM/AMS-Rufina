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
    DialogSettings dSettings(m_settings, this);
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
    QMessageBox::about(this,"О программе", AppInfo::buildAboutText());
}

void MainWindow::on_btCheckAllFloors_clicked()
{
    toggleFloorChechBoxes(true);
}

void MainWindow::on_btSend_clicked()
{
    QList<QCheckBox*> chBoxChats = m_chBoxFloorMap.values();
    bool isOneChBoxChecked = false;
    foreach (QCheckBox* chBoxChat, chBoxChats) {
        isOneChBoxChecked |= chBoxChat->isChecked();
    }
    if (!isOneChBoxChecked) {
        QMessageBox::critical(this, "Ошибка", "Ни одна из бесед не отмечена. Для отправки сообщения отметьте хотя бы одну беседу.");
        return;
    }
    MessageAssembler masm(m_settings, ui->ptxtedMessageText->toPlainText(), ui->chkAddAttentionStr->isChecked(), ui->chkPingAll->isChecked(), ui->chkAddSignature->isChecked());
    QString token = "";
    if (m_settings->isEncrypted()) {
        DialogPasswordEnter dlgPasswEnter(QByteArray::fromBase64(m_settings->getVkToken().toUtf8()), this);
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
    QProgressDialog dlgSending("Отправка сообщения", "Отмена", 0, checkedFloors.length(), this);
    dlgSending.setWindowModality(Qt::WindowModal);
    dlgSending.show();
    int progress = 0;
    foreach(uint8_t floor, checkedFloors) {
        msgDelivery.sendMessage(VK_API_MULTICHAT_BASE_ID+m_settings->getChats()[floor].getId(), masm.assembly());
        if(msgDelivery.hasError()) {
            VkError vkErr = msgDelivery.getVkError();
            if (vkErr.hasError()) {
                ErrorMessages::errorVkApi(this, vkErr.code(), vkErr.description()+
                                          "\nОшибка возникла при отправке сообщения в беседу: \""+
                                          m_settings->getChats()[floor].getTitle()+
                                          "\" (ID: "+QString::number(m_settings->getChats()[floor].getId())+").");
                dlgSending.cancel();
            }
        }
        if (dlgSending.wasCanceled())
            break;
        dlgSending.setValue(++progress);
    }
    dlgSending.setValue(checkedFloors.length());
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
    }
    updateMsgPreview();
}

void MainWindow::on_ptxtedMessageText_textChanged()
{
    updateMsgPreview();
}

void MainWindow::on_chkAddAttentionStr_stateChanged(int arg1)
{
    updateMsgPreview();
}

void MainWindow::on_chkPingAll_stateChanged(int arg1)
{
    updateMsgPreview();
}

void MainWindow::on_chkAddSignature_stateChanged(int arg1)
{
    updateMsgPreview();
}

void MainWindow::VkApiRequestFinished(QJsonDocument r)
{
    qDebug()<<"F!";
    qDebug()<<r.toJson();
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

void MainWindow::on_actionLicenseText_triggered()
{
    DialogLicenseView dlgLicenseView(this);
    dlgLicenseView.exec();
}
