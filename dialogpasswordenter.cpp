#include "dialogpasswordenter.h"
#include "ui_dialogpasswordenter.h"

DialogPasswordEnter::DialogPasswordEnter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPasswordEnter)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

DialogPasswordEnter::~DialogPasswordEnter()
{
    delete ui;
}
