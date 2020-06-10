#ifndef DETAILDIALOG_H
#define DETAILDIALOG_H

#include <QDialog>

namespace Ui {
class detailDialog;
}

class detailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit detailDialog(QWidget *parent = nullptr);
    ~detailDialog();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::detailDialog *ui;
    void setupRecipeTree(QMap<QString,QString> recipe);
};

#endif // DETAILDIALOG_H
