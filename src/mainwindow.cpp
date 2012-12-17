/*
    mainwindow.cpp - (c) Michael Weber, Jr. (2012)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hTemp = new QHBoxLayout();
    QVBoxLayout *vTemp = new QVBoxLayout();
    modelBox = new QGroupBox("Calculation Parameters");
    hTemp->addWidget(new QLabel("Horizontal Loading, Kh:"));
    khLineEdit = new QLineEdit("0");
    hTemp->addWidget(khLineEdit);
    hTemp->addStretch();
    vTemp->addLayout(hTemp);
    hTemp = new QHBoxLayout();
    hTemp->addWidget(new QLabel("Vertical Loading, Kv:"));
    kvLineEdit = new QLineEdit("0");
    hTemp->addWidget(kvLineEdit);
    hTemp->addStretch();
    vTemp->addLayout(hTemp);
    modelBox->setLayout(vTemp);

    hTemp = new QHBoxLayout();
    vTemp = new QVBoxLayout();
    soilBox = new QGroupBox("Soil Properties");
    soilLayersTable = new QTableWidget();
    soilLayersTable->setColumnCount(4);
    QStringList *list = new QStringList();
    list->append("Depth to Layer (ft)");
    list->append("Unit Weight (lb/ft^3)");
    list->append("Cohesion (lb/ft^2)");
    list->append("Friction Angel (deg)");
    soilLayersTable->setHorizontalHeaderLabels(*list);
    soilLayersTable->adjustSize();
    addLayerButton = new QPushButton("Add Soil Layer");
    connect(addLayerButton, SIGNAL(clicked()), this, SLOT(addLayer()));
    vTemp->addWidget(addLayerButton);
    delLayerButton = new QPushButton("Delete Soil Layer");
    connect(delLayerButton, SIGNAL(clicked()), this, SLOT(delLayer()));
    vTemp->addWidget(delLayerButton);
    hTemp->addWidget(soilLayersTable);
    hTemp->addLayout(vTemp);
    soilBox->setLayout(hTemp);

    hTemp = new QHBoxLayout();
    vTemp = new QVBoxLayout();
    slopeBox = new QGroupBox("Slope Properties");
    hTemp->addWidget(new QLabel("Height of Slope (ft):"));
    heightLineEdit = new QLineEdit();
    heightLineEdit->setText("0");
    hTemp->addWidget(heightLineEdit);
    hTemp->addStretch();
    vTemp->addLayout(hTemp);
    hTemp = new QHBoxLayout();
    hTemp->addWidget(new QLabel("Horizontal Slope:"));
    slopeLineEdit = new QLineEdit("0");
    hTemp->addWidget(slopeLineEdit);
    hTemp->addStretch();
    vTemp->addLayout(hTemp);
    slopeBox->setLayout(vTemp);

    calculateButton = new QPushButton("Calculate");
    connect(calculateButton, SIGNAL(clicked()), this, SLOT(calculate()));
    hTemp = new QHBoxLayout();
    hTemp->addStretch();
    hTemp->addWidget(calculateButton);
    hTemp->addStretch();

    vTemp = new QVBoxLayout();
    vTemp->addWidget(slopeBox);
    vTemp->addWidget(soilBox);
    vTemp->addWidget(modelBox);
    vTemp->addLayout(hTemp);
    setLayout(vTemp);
}

void MainWindow::calculate()
{
    data = new Algorithm();

    data->height = heightLineEdit->text().toDouble();
    data->slope = slopeLineEdit->text().toDouble();
    data->kv = kvLineEdit->text().toDouble();
    data->kh = khLineEdit->text().toDouble();
    data->numOfLayers = soilLayersTable->rowCount();
    data->layers = new SoilLayer*[data->numOfLayers];
    for(int i = 0; i < data->numOfLayers; i++)
    {
        data->layers[i] = new SoilLayer;
        data->layers[i]->depth = soilLayersTable->item(i, 0)->text().toDouble();
        data->layers[i]->c = soilLayersTable->item(i, 2)->text().toDouble();
        data->layers[i]->friction = soilLayersTable->item(i, 3)->text().toDouble()*4.0*atan(1.0)/180;
        data->layers[i]->weight = soilLayersTable->item(i, 1)->text().toDouble();
    }

    data->calculate();

    ResultsWindow *rw = new ResultsWindow(this, data);
    rw->exec();

    delete data;
}

void MainWindow::addLayer()
{
    RowAdd *rowAdd = new RowAdd(this);
    if(rowAdd->exec())
    {
        int row = soilLayersTable->rowCount();
        soilLayersTable->setRowCount(row+1);
        soilLayersTable->setItem(row, 0, new QTableWidgetItem(QString::number(rowAdd->depth)));
        soilLayersTable->setItem(row, 1, new QTableWidgetItem(QString::number(rowAdd->gamma)));
        soilLayersTable->setItem(row, 2, new QTableWidgetItem(QString::number(rowAdd->c)));
        soilLayersTable->setItem(row, 3, new QTableWidgetItem(QString::number(rowAdd->phi)));
    }

    delete rowAdd;
}

void MainWindow::delLayer()
{
    RowDelete *rowDelete = new RowDelete(this);
    rowDelete->setComboBox(soilLayersTable);
    if(rowDelete->exec())
    {
        soilLayersTable->removeRow(rowDelete->selection);
    }

    delete rowDelete;
}
