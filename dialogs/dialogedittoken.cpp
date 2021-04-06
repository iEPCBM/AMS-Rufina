#include "dialogedittoken.h"
#include "ui_dialogedittoken.h"

DialogEditToken::DialogEditToken(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditToken)
{
    ui->setupUi(this);
}

DialogEditToken::~DialogEditToken()
{
    delete ui;
}
