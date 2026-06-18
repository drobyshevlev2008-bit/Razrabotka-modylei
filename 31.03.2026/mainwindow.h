#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLinkedList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Create_clicked();
    void on_pushButton_Delete_clicked();
    void on_pushButton_CreateLink_clicked();
    void on_pushButton_Sort_clicked();

private:
    Ui::MainWindow *ui;
    QList<int> list;
    QLinkedList<int> linkedList;
};

#endif // MAINWINDOW_H