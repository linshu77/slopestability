#include "resultswindow.h"
#include <stdio.h>

ResultsWindow::ResultsWindow(QWidget *parent, Algorithm *data) :
    QDialog(parent)
{
    this->data = data;

    resultsTable = new QTableWidget();
    resultsTable->setColumnCount(6);
    resultsTable->setRowCount(30);
    QStringList *list = new QStringList();
    list->append("Moment X (ft)");
    list->append("Moment Y (ft)");
    list->append("Moment Radius (ft)");
    list->append("Overturning Moment (kip-ft/ft)");
    list->append("Resisting Moment (kip-ft/ft)");
    list->append("Factor of Safety");
    resultsTable->setHorizontalHeaderLabels(*list);

    for(int i = 0; i < 30; i++)
    {
        resultsTable->setItem(i, 0, new QTableWidgetItem(QString::number(data->results[i][0])));
        resultsTable->setItem(i, 1, new QTableWidgetItem(QString::number(data->results[i][1])));
        resultsTable->setItem(i, 2, new QTableWidgetItem(QString::number(data->results[i][2])));
        resultsTable->setItem(i, 3, new QTableWidgetItem(QString::number(data->results[i][3]/1000)));
        resultsTable->setItem(i, 4, new QTableWidgetItem(QString::number(data->results[i][4]/1000)));
        resultsTable->setItem(i, 5, new QTableWidgetItem(QString::number(data->results[i][5])));
    }

    exportButton = new QPushButton("Export");
    connect(exportButton, SIGNAL(clicked()), this, SLOT(csv()));

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(resultsTable);
    QHBoxLayout *h = new QHBoxLayout();
    h->addStretch();
    h->addWidget(exportButton);
    h->addStretch();
    l->addLayout(h);
    setLayout(l);
}

void ResultsWindow::csv()
{
    QFileDialog *saveFileDialog = new QFileDialog(this,
                                      tr("Export Data"), "", tr("Excel Import (*.csv)"));
    saveFileDialog->setDefaultSuffix("csv");
    saveFileDialog->setViewMode(QFileDialog::Detail);
    if(saveFileDialog->exec())
    {
        QStringList fileName = saveFileDialog->selectedFiles();
        FILE* file = fopen(fileName[0].toAscii().data(), "w");
        fprintf(file, "Moment X (ft),Moment Y (ft),Moment Radius (ft),Overturning Moment (kip-ft/ft),Resisting Moment (kip-ft/ft),Factor of Safety\n");
        for(int i = 0; i < 30; i++)
        {
            fprintf(file, "%lf,%lf,%lf,%lf,%lf,%lf\n", data->results[i][0], data->results[i][1], data->results[i][2], data->results[i][3]/1000,
                    data->results[i][4]/1000, data->results[i][5]);
        }

        fclose(file);
    }
    delete saveFileDialog;
}
