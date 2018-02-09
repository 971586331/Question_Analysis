#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>
#include "main.h"
#include <QTextCodec>
#include <QSqlQuery>
#include "qtsql_operation.h"
#include <QSqlError>
#include <QMessageBox>

QString open_path;
QString save_path;

QSqlDatabase my_sql;                //数据库
QSqlQuery my_sql_tab;               //数据库中的表
Test_Questions_T Test_Questions;    //题库结构体

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//打开按钮
void MainWindow::on_pushButton_open_clicked()
{
//    QString desktop_path = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);    //获取桌面路径
    QString desktop_path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString Path = QFileDialog::getOpenFileName(this, tr("Open File"), desktop_path, tr("Text files (*.txt)"));
    if (!Path.isEmpty())
    {
        ui->lineEdit_open_path->setText(Path);
        open_path = Path;
    }
}

//保存文件
void MainWindow::on_pushButton_save_clicked()
{
//    QString desktop_path = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);    //获取桌面路径
    QString desktop_path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString Path = QFileDialog::getSaveFileName(this, tr("Save File"), desktop_path, tr("Text files (*.db)"));
    if (!Path.isEmpty())
    {
        ui->lineEdit_save_path->setText(Path);
        save_path = Path;
    }
}

//开始分析
void MainWindow::on_pushButton_finished_2_clicked()
{
    int Test_sum = 1;
    ui->label_3->setText(QString::fromLocal8Bit("正在分析!"));
    my_sql = Creat_database(save_path);   //连接数据库
    Open_database(my_sql);              //打开数据库
    my_sql_tab = Creat_sql_table(my_sql , card_create_sql); //创建一个名为AOPA1的表
    clear_sql_table(my_sql_tab, card_clear_sql);        //先清空表

    QFile f(open_path);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("---Open txt failed---\n");
        return;
    }

    QTextStream txtInput(&f);
    QString lineStr;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    while (!txtInput.atEnd())   //读文件直到把文件读完
    {
        QByteArray arr = f.readLine();
        arr.replace(0x0B,0x0D);
        lineStr = QString::fromLocal8Bit(arr, arr.length());    //Window下的QByteArray转QString
        qDebug()<<lineStr;
        qDebug()<<lineStr.length();

        if((lineStr.mid(0,1)>="0")&&(lineStr.mid(0,1)<="9"))
        {
            if((lineStr.mid(1,1)>="0")&&(lineStr.mid(1,1)<="9"))
            {
               if((lineStr.mid(2,1)>="0")&&(lineStr.mid(2,1)<="9"))
               {
                   Test_Questions.Subject = lineStr.mid(4);
               }
            }
        }
        else if(lineStr.mid(0,1)=="A")
        {
            Test_Questions.Option_A = lineStr.mid(2);
        }
        else if(lineStr.mid(0,1)=="B")
        {
            Test_Questions.Option_B = lineStr.mid(2);
        }
        else if(lineStr.mid(0,1)=="C")
        {
            Test_Questions.Option_C = lineStr.mid(2);
        }
        else if(lineStr.mid(0,1)=="D")
        {
            Test_Questions.Option_D = lineStr.mid(2);
        }
        else if(lineStr.mid(0,2)==QString::fromLocal8Bit("答案"))
        {
            Test_Questions.Answer = lineStr.mid(3,1);
        }
        else if(lineStr == "\n")
        {
            qDebug()<<"ssssyyyy";
            Test_Questions.Title_Number = Test_sum;
            Insert_sql_data(my_sql_tab, card_insert_sql, Test_Questions);
            Test_sum ++;
        }
    }
    Close_database(my_sql);
    ui->label_3->setText(QString::fromLocal8Bit("分析完成!"));
    QMessageBox::about(this,tr(""),QString::fromLocal8Bit("分析完成!"));
}

//完成分析
void MainWindow::on_pushButton_finished_clicked()
{
    this->close();
}

//写文件
void Write_In_File(QString file , QString str)
{
    QFile f(file);
    if(!(f.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)))
    {
        qDebug("---Open failed!---\n");
        return;
    }
    QTextStream txtInput(&f);
    txtInput << str <<"\n";
    f.close();
}

//新建文件
//fileName:路径和文件名
void New_File(QString fileName)
{
    QFileInfo fi(fileName);
    if(fi.isFile())
    {
        qDebug("file ecist!\n");
    }
    else
    {
        QFile f(fileName);
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        f.close();
    }
}
