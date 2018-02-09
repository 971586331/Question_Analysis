#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void slots_on_pushButton_open_clicked();

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_finished_2_clicked();

    void on_pushButton_finished_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW1_H
