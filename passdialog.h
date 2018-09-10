#ifndef PASSDIALOG_H
#define PASSDIALOG_H

#include <QDialog>

class Widget;

namespace Ui {
    class PassDialog;
}

class PassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PassDialog(QWidget *parent = 0);
    ~PassDialog();

private:
    Ui::PassDialog *ui;

    friend class Widget;
};

#endif // PASSDIALOG_H
