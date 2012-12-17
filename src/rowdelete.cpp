#include "rowdelete.h"
#include "ui_rowdelete.h"

RowDelete::RowDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RowDelete)
{
    ui->setupUi(this);
}

RowDelete::~RowDelete()
{
    delete ui;
}

void RowDelete::setComboBox(QTableWidget *tableWidget)
{
    for(int i = 0; i < tableWidget->rowCount(); i++)
        ui->comboBox->addItem(QString('1'+i));
}

void RowDelete::accept()
{
    selection = ui->comboBox->currentIndex();
    QDialog::accept();
}
