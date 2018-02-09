#ifndef MAIN_H
#define MAIN_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>

//试题数据结构
typedef struct
{
    int Title_Number;   //题库题号
    QString Subject;    //题目
    QString Option_A;   //选项A
    QString Option_B;   //选项B
    QString Option_C;   //选项C
    QString Option_D;   //选项D
    QString Answer;     //答案
}Test_Questions_T;

void New_File(QString fileName);
void Write_In_File(QString file , QString str);

extern QSqlDatabase my_sql;                //数据库
extern QSqlQuery my_sql_tab;               //数据库中的表

#endif // MAIN_H
