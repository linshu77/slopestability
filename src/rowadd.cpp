#include "rowadd.h"
#include "ui_rowadd.h"

RowAdd::RowAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RowAdd)
{
    ui->setupUi(this);
}

RowAdd::~RowAdd()
{
    delete ui;
}

void RowAdd::accept()
{
    depth = ui->lineEdit->text().toDouble();
    c = ui->lineEdit_2->text().toDouble();
    phi = ui->lineEdit_3->text().toDouble();
    gamma = ui->lineEdit_4->text().toDouble();

    QDialog::accept();
}
