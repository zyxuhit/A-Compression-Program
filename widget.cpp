#include "widget.h"
#include "ui_widget.h"
#include "passdialog.h"
#include "ui_passdialog.h"
#include <QtGui>
#include <string>

std::string process(std::string inputFile,
                    std::string outputFile,
                    int type,
                    bool zip,
                    std::string password);

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_toolButton_clicked()
{
    ui->inputEdit->setText(
                QFileDialog::getOpenFileName(this, "Դ�ļ�"));
}

void Widget::on_toolButton_2_clicked()
{
    ui->outputEdit->setText(
                QFileDialog::getSaveFileName(this, "Ŀ���ļ�"));
}

void Widget::on_runButton_clicked()
{
    QString password;
    if (ui->passBox->isChecked()) {
        PassDialog d;
        if (d.exec()) {
            password = d.ui->lineEdit->text();
        } else return;
    }

    std::string ret = process(ui->inputEdit->text().toStdString(),
                              ui->outputEdit->text().toStdString(),
                              ui->typeBox->currentIndex(),
                              ui->zipButton->isChecked(),
                              password.toStdString());
    if (ret.empty()) {
        QMessageBox::information(this, "��ʾ", "�������", QMessageBox::Ok);
    } else {
        QMessageBox::critical(this, "����", QString::fromStdString(ret), QMessageBox::Ok);
    }
}
