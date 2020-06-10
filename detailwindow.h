#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H

#include <QMainWindow>

namespace Ui {
class DetailWindow;
}

class DetailWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DetailWindow(QWidget *parent = nullptr);
    ~DetailWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DetailWindow *ui;
    QString getCurrentWindowTitle();
};

#endif // DETAILWINDOW_H
