/*
    mainwindow.h - (c) Michael Weber, Jr. (2012)

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
