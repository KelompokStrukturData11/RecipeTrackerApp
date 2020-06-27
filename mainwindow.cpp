#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>



//Ketika aplikasi pertama kali dibuka kode dalam Mainwindow dieksekusi
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Deklarasi variabel
    QStringList resep;
    QStringList filteredItems;

    //Pemanggilan Fungsi
    readRecipeDb(resepMakanan,
                 resep,
                 kategoriBahanProto,
                 deskripsiMakanan,
                 makananDetailResep);
    ingredientsFormater(kategoriBahanProto,kategoriBahan);
    setupFoodTree(resepMakanan);
    setupIngredientsFilter(kategoriBahan);
    QMapIterator<QString,QStringList> i(kategoriBahan);

    //Setting Ui esensial
    ui->ingredientsTree->sortItems(0,Qt::AscendingOrder);
    ui->foodTree->sortItems(0,Qt::AscendingOrder);
    ui->searchBar->setPlaceholderText("Cari makanan...");
}

//Fungsi untuk memformat kapital dari text
QString MainWindow::toFormalCase(QString text){
    for(int i = 0; i < text.size(); i++){
        if(text[i] == " "){
            i += 1;
            text[i] = text[i].toUpper();
        }else if(i == 0){
            text[i] = text[i].toUpper();
        }else{
            text[i] = text[i].toLower();
        }
        }
        return text;
}

// Fungsi untuk membaca database dan memasukan ke variabel
void MainWindow::readRecipeDb(QMap<QString,QStringList> &recipe, QStringList &recipeList, QMap<QString,QString> &kategoriBahan
, QMap<QString,QString> &deskripsiMakanan, QMap<QString, QMap<QString, QString> > &detailRecipe){
    QFile file(":/res/db/dbText/Hello.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
          //qDebug() << "Cannot Open File";
    }
    QTextStream in(&file);
    QString state;
    QString foodHolder;
    QStringList recipeBuffer;
    QString stateHolder;
    QMap <QString,QString> itemValue;
    while(!in.atEnd()){
        QString buffer = in.readLine();
        if(buffer == "END"){
            state = "END";
            QDirIterator descriptionPath(":/res/db/desciptions/", QDirIterator::Subdirectories);
             QDirIterator imagePath(":/img/img/", QDirIterator::Subdirectories);
            while(descriptionPath.hasNext()){
            QString pathDes = descriptionPath.next();
            QString imgPathHolder = imagePath.next();
            if(":/res/db/desciptions/"+foodHolder+".txt" == pathDes){
            QFile descriptions(pathDes);
            if (!descriptions.open(QIODevice::ReadOnly | QIODevice::Text)){
                return;
//                  qDebug() << "Cannot Open File";
            }
            QTextStream inDescriptions(&descriptions);
            deskripsiMakanan[foodHolder] = inDescriptions.readAll();
                if(":/img/img/"+foodHolder+".jpg" == imgPathHolder){
                    gambarMakanan[foodHolder] = imgPathHolder;
                }
            }}
            recipe[foodHolder] = recipeBuffer;
            detailRecipe[foodHolder] = itemValue;
            itemValue.clear();
        }

        if(buffer == "Nama:"){
            recipeBuffer.clear();
            state = "Makanan";
        }
        else if(buffer == "Resep:"){
            state = "Resep";
        }

        if(state == "Makanan"){
            foodHolder = toFormalCase(buffer);
        }else if(state == "Resep"){
            if(buffer != "Resep:"){
                recipeBuffer << toFormalCase(buffer);
                in.readLine();
                QString categoryHolder = in.readLine();
                kategoriBahan[toFormalCase(buffer)] = toFormalCase(categoryHolder);
                in.readLine();
                QString valueHolder = in.readLine();
                itemValue[toFormalCase(buffer)] = toFormalCase(valueHolder);
                if(!(recipeList.contains(toFormalCase(buffer)))){
                    recipeList << toFormalCase(buffer);
                }
            }

        }

    }
    file.close();
}

//Merapikan variabel list bahan
void MainWindow::ingredientsFormater(QMap<QString, QString> &katgoriBahanProto,QMap<QString,QStringList> &kategoriBahan){
    QMapIterator<QString,QString> i(katgoriBahanProto);
    QStringList listBahan;
    QStringList listKategori;
    while (i.hasNext()) {
        i.next();
        if(!(listKategori.contains(toFormalCase(i.value())))){
        listKategori << toFormalCase(i.value());
        kategoriBahan[toFormalCase(i.value())] = listBahan;
        QMapIterator<QString,QString> it(katgoriBahanProto);
        while (it.hasNext()) {
            it.next();
            if(toFormalCase(it.value())==toFormalCase(i.value())){
                kategoriBahan[toFormalCase(i.value())] << toFormalCase(it.key());

            }
        }
        }
    }
}

//Membuat UI untuk menu list makanan
void MainWindow::setupFoodTree(QMap<QString,QStringList> &recipe)
{
    int counter = 0;
    ui->foodTree->setColumnCount(1);
    ui->foodTree->setHeaderLabels(QStringList() << tr("Makanan"));
    ui->foodTree->setIconSize(QSize(50,100));
    QMapIterator<QString, QStringList> i(recipe);
    while (i.hasNext()) {
        i.next();
        QTreeWidgetItem *foodItem = new QTreeWidgetItem(ui->foodTree);
        foodItem->setText(0, i.key());
        foodItem->setSizeHint(0,QSize(foodItem->sizeHint(0).width(),100));
        QDirIterator it(":/img/img/", QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QString imgPath = it.next();
            if(":/img/img/"+i.key()+".jpg" == imgPath){
                foodItem->setIcon(0,QIcon(imgPath));
           }
        }
        counter += 1;

    }
}

//Membuat UI untuk menu filter dengan bahan
void MainWindow::setupIngredientsFilter(QMap<QString, QStringList> &kategoriBahan){
    ui->ingredientsTree->setColumnCount(1);
    ui->ingredientsTree->setHeaderLabels(QStringList() << tr("Bahan"));
////    ui->ingredientsTree->setIconSize(QSize(50,100));
    QMapIterator<QString,QStringList> i(kategoriBahan);

    while (i.hasNext()) {
        i.next();

        QTreeWidgetItem *categoryItem = new QTreeWidgetItem(ui->ingredientsTree);
        categoryItem->setText(0,i.key());
        categoryItem->setCheckState(0, Qt::Unchecked);
        categoryItem->setFlags(categoryItem->flags() | Qt::ItemIsAutoTristate);
        foreach(QString bahan,kategoriBahan[i.key()]){
            QTreeWidgetItem *ingredientItem = new QTreeWidgetItem(categoryItem);
                           ingredientItem->setText(0, bahan);
                           ingredientItem->setCheckState(0, Qt::Unchecked);

        }

    }
}

//Fungsi untuk melakukan filter pada food
QStringList MainWindow::filterFoodList(){
    QStringList filteredItems;
    for(int i = 0;i < ui->ingredientsTree->topLevelItemCount(); i++){
        QTreeWidgetItem *categoryItem = ui->ingredientsTree->topLevelItem(i);
        for(int j = 0; j < ui->ingredientsTree->topLevelItem(i)->childCount();j++){
            QTreeWidgetItem *ingredientItem = categoryItem->child(j);
            bool checked = ingredientItem->checkState(0);
            if(checked){
                filteredItems << ingredientItem->text(0);
            }
        }
    }
    return filteredItems;}

//Melakukan update UI setelah di transfer
void MainWindow::filterFoodListWidget(QStringList filteredFood){
    QTreeWidget *foodList = ui->foodTree;
    int counter = 0;
    int containCounter = 0;
    QMapIterator<QString,QStringList> i(resepMakanan);
    while(i.hasNext()){
        i.next();
        foreach(QString bahan,filteredFood){
            if((!(i.value().contains(bahan))&&(containCounter < 1))){
                if(filteredFood.last() == bahan){
                foodList->takeTopLevelItem(counter);
                counter -= 1;}
            }else{
            containCounter += 1;}
        }
        counter += 1;
        containCounter = 0;
    }
}

//Fungsi untuk mendapatkan list makanan saat ini
QStringList MainWindow::getCurrentList(){
    int currentListCount = ui->foodTree->topLevelItemCount();
    QStringList currentList;
    for(int i =0;i<currentListCount;i++){
        currentList << ui->foodTree->topLevelItem(i)->text(0);
    }
    return currentList;
}

// Fungsi untuk mencari makanan
void MainWindow::searchFoodList(){
    QString searchText = toFormalCase(ui->searchBar->text());
    QStringList currentList = getCurrentList();
    int itemCounter = 0;

    foreach(QString item, currentList){
        int M = searchText.size();
        int N = item.size();
        int matchCount = 0;

        for (int i = 0; i <= N - M; i++) {
            int j;

            /* For current index i, check for pattern match */
            for (j = 0; j < M; j++)
                if (item[i + j] != searchText[j])
                    break;

            if (j == M)
                matchCount += 1;// if pat[0...M-1] = txt[i, i+1, ...i+M-1]


    }
        if(matchCount == 0){
            ui->foodTree->takeTopLevelItem(itemCounter);
            itemCounter -= 1;
        }
        itemCounter += 1;

}
}

//Fungsi bila window tertutup
MainWindow::~MainWindow()
{
    delete ui;
}

//Button event untuk tombol cari makanan
void MainWindow::on_searchBtn_clicked()
{
    ui->foodTree->clear();
    setupFoodTree(resepMakanan);
    filterFoodListWidget(filterFoodList());
    searchFoodList();
}

// Event ketika salah satu list makanan di klik
void MainWindow::on_foodTree_itemClicked(QTreeWidgetItem *item, int column)
{
    hide();
    MainWindow::setWindowTitle(item->text(column));
    detaildialog = new detailDialog(this);
    detaildialog->show();
    detaildialog->setWindowTitle(item->text(column));
}





