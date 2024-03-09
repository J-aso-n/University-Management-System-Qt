#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class addWindow;
}

class addWindow : public QWidget
{
    Q_OBJECT

public:
    explicit addWindow(QWidget *parent = nullptr);
    ~addWindow();

private:
    Ui::addWindow *ui;
};

#endif // ADDWINDOW_H
