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
                QFileDialog::getOpenFileName(this, "源文件"));
}

void Widget::on_toolButton_2_clicked()
{
    ui->outputEdit->setText(
                QFileDialog::getSaveFileName(this, "目标文件"));
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
        QMessageBox::information(this, "提示", "任务完成", QMessageBox::Ok);
    } else {
        QMessageBox::critical(this, "错误", QString::fromStdString(ret), QMessageBox::Ok);
    }
}
