#ifndef MAINDLG_H
#define MAINDLG_H

#include <QDialog>
#include "dataaccess.h"

namespace Ui {
class MainDlg;
}

class MainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MainDlg(QWidget *parent = 0);
    ~MainDlg();

private:
    Ui::MainDlg *ui;
    DataAccess *_dao;
};

#endif // MAINDLG_H
