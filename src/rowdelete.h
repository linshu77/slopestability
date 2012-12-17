#ifndef ROWDELETE_H
#define ROWDELETE_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class RowDelete;
}

class RowDelete : public QDialog
{
    Q_OBJECT
    
public:
    explicit RowDelete(QWidget *parent = 0);
    void setComboBox(QTableWidget *);
    ~RowDelete();

    int selection;
    
private:
    Ui::RowDelete *ui;

    void accept();
};

#endif // ROWDELETE_H
