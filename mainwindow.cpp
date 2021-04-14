#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateMsgPreview();
    m_settings = Settings::getInstance();
    QList<QCheckBox*> lstFloorsChb = ui->frmFloorsContainer->findChildren<QCheckBox*>();
    foreach (QCheckBox* checkBoxFloor, lstFloorsChb) {
        m_chBoxFloorMap[checkBoxFloor->property("floorNumber").value<uint8_t>()] = checkBoxFloor;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QCheckBox* MainWindow::getFloorChk(int floor)
{
    switch (floor) {
    case 2:
        return this->ui->chkSecondFloor;
        break;
    case 3:
        return this->ui->chkThirdFloor;
        break;
    case 4:
        return this->ui->chkFourthFloor;
        break;
    case 5:
        return this->ui->chkFifthFloor;
        break;
    }
    return nullptr;
}


void MainWindow::on_actionSettings_triggered()
{
    DialogSettings dSettings(this);
    connect(&dSettings, SIGNAL(saved()), this, SLOT(onSettingsUpdated()));
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
    QMessageBox::about(this,"О программе", "Система автоматизированной отправки сообщений Руфина");
}

void MainWindow::on_btCheckAllFloors_clicked()
{
    for (auto i=2; i<=5; i++) {
        getFloorChk(i)->setChecked(true);
    }
}

void MainWindow::on_btSend_clicked()
{

    MessageAssembler masm(ui->ptxtedMessageText->toPlainText(), ui->chkAddAttentionStr->isChecked(), ui->chkPingAll->isChecked(), ui->chkAddSignature->isChecked());
    QString token = "";
    if(m_settings->isEncrypted()) {
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
        if (dlgSending.wasCanceled())
            break;
        dlgSending.setValue(++progress);
    }
    dlgSending.setValue(checkedFloors.length());

    //connect(&api, SIGNAL(requestFinished(QJsonDocument)), this, SLOT(VkApiRequestFinished(QJsonDocument)));
}

void MainWindow::updateMsgPreview()
{
    MessageAssembler masm(ui->ptxtedMessageText->toPlainText(), ui->chkAddAttentionStr->isChecked(), ui->chkPingAll->isChecked(), ui->chkAddSignature->isChecked());
    ui->txtedPreview->setText(masm.assembly());
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

void MainWindow::onSettingsUpdated()
{
    updateMsgPreview();
}
