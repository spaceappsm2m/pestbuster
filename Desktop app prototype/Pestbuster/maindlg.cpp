#include "maindlg.h"
#include "ui_maindlg.h"


MainDlg::MainDlg(QWidget *parent) : QDialog(parent), ui(new Ui::MainDlg) {
    ui->setupUi(this);

    //prepare DB access
    _dao = DataAccess::getInstance();

    /*QImage img("/Users/deadbird/Desktop/pestbuster/Pestbuster/mais.png");
    _dao->pushImage(img);

    QImage img2(_dao->fetchImage(10));
    img2.save("/Users/deadbird/Desktop/pestbuster/Pestbuster/mais2.png");*/

}

MainDlg::~MainDlg()
{
    delete ui;
}
