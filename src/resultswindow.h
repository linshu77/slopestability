#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QtGui>
#include "algorithm.h"

class ResultsWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ResultsWindow(QWidget *parent, Algorithm *data);
    
signals:
    
public slots:
    void csv();

private:
       QTableWidget *resultsTable;
       QPushButton *exportButton;
       Algorithm *data;
};

#endif // RESULTSWINDOW_H
