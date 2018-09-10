#include "passdialog.h"
#include "ui_passdialog.h"

PassDialog::PassDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PassDialog)
{
    ui->setupUi(this);
}

PassDialog::~PassDialog()
{
    delete ui;
}
