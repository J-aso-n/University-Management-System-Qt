#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <algorithm>
#include "addwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct unit;//提前声明一下unit
struct top;
struct person;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_table_customContextMenuRequested(const QPoint &pos);
    void showTable(const top theTop,QTableWidget *Table);//显示top下的所有unit
    void showUnit(unit *theUnit,QTableWidget *Table);//显示unit下的所有person
    void showPerson(const person *thePerson,QTableWidget *Table);//显示该人员具体信息
    void add_unit(top& check_top,int now_check,QTableWidget *Table);//添加unit
    void add_person(unit *check_unit,QTableWidget *Table);//添加person
    void add_3(person *check_person,QTableWidget *Table);//person添加unit

    void on_table_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
};



//人员结构体
typedef struct person{
    QString name;//人员名称
    QVector<QString> job;//职位（与部门一一对应）
    QVector<unit*> list;//所属部门
}person;

//部门结构体
typedef struct unit{
    QString name;//部门名称
    QVector<person*> list;//人员列表(指针)
}unit;

//顶层结构体
typedef struct top{
    QString name;//顶层名称
    QVector<unit*> list;//部门列表(指针)
}top;

//注册结构体
Q_DECLARE_METATYPE(person);
Q_DECLARE_METATYPE(unit);
Q_DECLARE_METATYPE(top);

void initial(QVariant *varValue);//初始化顶层
void check_(int n);
void my_sort(unit *theUnit);//给unit中的人员进行排序，默认主管，副主管，员工

#endif // MAINWINDOW_H
