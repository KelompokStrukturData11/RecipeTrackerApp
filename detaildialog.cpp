#include "detaildialog.h"
#include "ui_detaildialog.h"
#include "mainwindow.h"

MainWindow *listWindow;

detailDialog::detailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detailDialog)
{
    ui->setupUi(this);

    //Declare variabel widht & Height
    int w = ui->foodImageLabel->width();
    int h = ui->foodImageLabel->height();
    QString currentFood = parent->windowTitle();

    detailDialog::setGeometry(parent->geometry());

    listWindow = new MainWindow();

    //Setup Ui
    ui->foodNameLabel->setText(currentFood);
    ui->foodDescription->setText(listWindow->deskripsiMakanan[currentFood]);
    QPixmap pixmap(listWindow->gambarMakanan[currentFood]);
    setupRecipeTree(listWindow->makananDetailResep[currentFood]);
    ui->foodImageLabel->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
}

//Ketika detail dialog ditutup
detailDialog::~detailDialog()
{
    delete ui;
}

//Membuat UI resep bahan list
void detailDialog::setupRecipeTree(QMap<QString, QString> recipe){
    ui->foodRecipe->setColumnCount(1);
    ui->foodRecipe->setHeaderLabels(QStringList() << tr("Bahan"));
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

//Event ketika tombol kembali di klik
void detailDialog::on_pushButton_2_clicked()
{
    hide();
    listWindow->show();
}
