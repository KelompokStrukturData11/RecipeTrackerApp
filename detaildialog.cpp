#include "detaildialog.h"
#include "ui_detaildialog.h"
#include <QtDebug>
#include "mainwindow.h"

MainWindow *listWindow;
detailDialog::detailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detailDialog)
{
    ui->setupUi(this);
    int w = ui->foodImageLabel->width();
    int h = ui->foodImageLabel->height();
    qDebug() << w << "  " << h;
    QString currentFood = parent->windowTitle();
    detailDialog::setGeometry(parent->geometry());
    listWindow = new MainWindow();
    ui->foodNameLabel->setText(currentFood);
    ui->foodDescription->setText(listWindow->deskripsiMakanan[currentFood]);
    QPixmap pixmap(listWindow->gambarMakanan[currentFood]);
    setupRecipeTree(listWindow->makananDetailResep[currentFood]);

    ui->foodImageLabel->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

}

detailDialog::~detailDialog()
{
    delete ui;
}

void detailDialog::setupRecipeTree(QMap<QString, QString> recipe){
//    int counter = 0;
    ui->foodRecipe->setColumnCount(1);
    ui->foodRecipe->setHeaderLabels(QStringList() << tr("Resep"));
    ui->foodRecipe->setIconSize(QSize(50,100));
    QMapIterator<QString,QString> i(recipe);
    while(i.hasNext()){
        i.next();
        QTreeWidgetItem *recipeItem = new QTreeWidgetItem(ui->foodRecipe);
        QTreeWidgetItem *recipeValue = new QTreeWidgetItem(recipeItem);
        recipeItem->setText(0,i.key());
        recipeItem->setFlags(recipeItem->flags() | Qt::ItemIsAutoTristate);
        recipeValue->setText(0,i.value());
    }
}

void detailDialog::on_pushButton_2_clicked()
{
    hide();
    listWindow->show();
}
