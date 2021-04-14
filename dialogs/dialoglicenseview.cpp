#include "dialoglicenseview.h"
#include "ui_dialoglicenseview.h"

DialogLicenseView::DialogLicenseView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLicenseView)
{
    ui->setupUi(this);
}

DialogLicenseView::~DialogLicenseView()
{
    delete ui;
}
