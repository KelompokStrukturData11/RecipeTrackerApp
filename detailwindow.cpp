#include "detailwindow.h"
#include "ui_detailwindow.h"

#include "mainwindow.h"

//MainWindow *listWindow;

DetailWindow::DetailWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DetailWindow)
{
    ui->setupUi(this);

//    listWindow = new MainWindow();
//    listWindow->PrintLabel();
//    qDebug() << listWindow->deskripsiMakanan["Nasi Goreng"];
//    listWindow->setDetailView(ui);
//    QString sv;
    qDebug() << DetailWindow::windowTitle();

}

DetailWindow::~DetailWindow()
{
    delete ui;
}

void DetailWindow::on_pushButton_clicked()
{
//    hide();
//    listWindow = new MainWindow();
//    listWindow->show();
}

QString DetailWindow::getCurrentWindowTitle(){
    return DetailWindow::windowTitle();
}

void DetailWindow::on_pushButton_2_clicked()
{
    qDebug() << getCurrentWindowTitle();
}
