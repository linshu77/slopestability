#ifndef ROWADD_H
#define ROWADD_H

#include <QDialog>

namespace Ui {
class RowAdd;
}

class RowAdd : public QDialog
{
    Q_OBJECT
    
public:
    explicit RowAdd(QWidget *parent = 0);
    ~RowAdd();

    double depth;
    double c;
    double phi;
    double gamma;
    
private:
    Ui::RowAdd *ui;
    void accept();
};

#endif // ROWADD_H
