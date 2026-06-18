#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <cmath>

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
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_Dot_clicked();
    void on_pushButton_Sign_clicked();
    void on_pushButton_Clear_clicked();
    void on_pushButton_Plus_clicked();
    void on_pushButton_Minus_clicked();
    void on_pushButton_Multiply_clicked();
    void on_pushButton_Divide_clicked();
    void on_pushButton_Equal_clicked();
    void on_pushButton_Cos_clicked();
    void on_pushButton_Lg_clicked();
    void on_pushButton_Square_clicked();
    void on_pushButton_Factorial_clicked();
    void on_pushButton_MS_clicked();
    void on_pushButton_MR_clicked();
    void on_pushButton_MC_clicked();
    void on_pushButton_MPlus_clicked();
    void on_pushButton_MMinus_clicked();

private:
    Ui::MainWindow *ui;
    QStack<QString> stack;
    QString memory;
    void calculate(QString sgn);
};

#endif // MAINWINDOW_H