/*
    resultswindow.h - (c) Michael Weber, Jr. (2012)

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
