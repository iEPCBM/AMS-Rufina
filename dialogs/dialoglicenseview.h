#ifndef DIALOGLICENSEVIEW_H
#define DIALOGLICENSEVIEW_H

#include <QDialog>

namespace Ui {
class DialogLicenseView;
}

class DialogLicenseView : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLicenseView(QWidget *parent = nullptr);
    ~DialogLicenseView();

private:
    Ui::DialogLicenseView *ui;
};

#endif // DIALOGLICENSEVIEW_H
