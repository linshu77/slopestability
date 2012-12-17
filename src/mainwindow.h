#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <math.h>
#include "rowadd.h"
#include "rowdelete.h"
#include "resultswindow.h"
#include "algorithm.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void calculate();
    void addLayer();
    void delLayer();

private:
    QGroupBox *modelBox;
    QLineEdit *khLineEdit;
    QLineEdit *kvLineEdit;

    QGroupBox *soilBox;
    QTableWidget *soilLayersTable;
    QPushButton *addLayerButton;
    QPushButton *delLayerButton;

    QGroupBox *slopeBox;
    QLineEdit *heightLineEdit;
    QLineEdit *slopeLineEdit;

    QPushButton *calculateButton;

    Algorithm *data;
};

#endif // MAINWINDOW_H
