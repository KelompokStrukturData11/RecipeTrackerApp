#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QTextStream>
#include <QDirIterator>
#include <QTreeWidgetItem>


#include "detaildialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Deklarasi public variable
    QStringList currentItemRecipe;
    QString currentItemDescription;
    QString currentItemName;
    QString getCurrentItemDescription();
    QString getCurrentItemName();
    QMap<QString,QStringList> resepMakanan;
    QMap<QString,QString> kategoriMakanan;
    QMap<QString,QString> kategoriBahanProto;
    QMap<QString,QStringList> kategoriBahan;
    QMap<QString,QString> deskripsiMakanan;
    QMap<QString,QString> gambarMakanan;
    QMap<QString,QString> jumlahBahan;
    QMap<QString,QMap<QString,QString>> makananDetailResep;
    void readRecipeDb(QMap<QString,QStringList> &recipe,
                      QStringList &recipeList,
                      QMap<QString,QString> &kategoriBahan,
                      QMap<QString,QString> &deskripsiMakanan,
                      QMap<QString,QMap<QString,QString>> &detailRecipe
);

private slots:

    void on_searchBtn_clicked();

    void on_foodTree_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    detailDialog *detaildialog;
    //Prototype fungsi private
    QString toFormalCase(QString text);
    void setupFoodTree(QMap<QString,QStringList> &recipe);
    void ingredientsFormater(QMap<QString,QString> &katgoriBahanProto, QMap<QString,QStringList> &kategoriBahan);
    void setupIngredientsFilter(QMap<QString,QStringList> &kategoriBahan);
    QStringList filterFoodList();
    void updateListFood(QTreeWidgetItem *item, int column);
    void filterFoodListWidget(QStringList filteredFood);
    QStringList getCurrentList();
    void setDataDetail(
            QMap<QString,QString> &deskripsiMakanan,
            QMap<QString,QString> &gambarMakanan);
    void searchFoodList();

};
#endif // MAINWINDOW_H
