#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    memory = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->lineEdit->insert("0");
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->lineEdit->insert("1");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->insert("2");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->insert("3");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->insert("4");
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->insert("5");
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->insert("6");
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->insert("7");
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->insert("8");
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->insert("9");
}

void MainWindow::on_pushButton_Dot_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.length() == 0 || text.at(text.length()-1) == '.' || text.indexOf('.') != -1) {
        return;
    }
    ui->lineEdit->setText(text + '.');
}

void MainWindow::on_pushButton_Sign_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.length() == 0 || text.at(0) != '-') {
        ui->lineEdit->setText("-" + text);
    } else {
        ui->lineEdit->setText(text.remove(0, 1));
    }
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    stack.clear();
}

void MainWindow::on_pushButton_Plus_clicked()
{
    calculate("+");
}

void MainWindow::on_pushButton_Minus_clicked()
{
    calculate("-");
}

void MainWindow::on_pushButton_Multiply_clicked()
{
    calculate("*");
}

void MainWindow::on_pushButton_Divide_clicked()
{
    calculate("/");
}

void MainWindow::calculate(QString sgn)
{
    if (ui->lineEdit->text().length() == 0) {
        return;
    }

    if (stack.length() >= 2) {
        double val2 = ui->lineEdit->text().toDouble();
        QString sign = stack.pop();
        double val1 = stack.pop().toDouble();

        if (sign == "+") {
            stack.push(QString::number(val1 + val2));
        } else if (sign == "-") {
            stack.push(QString::number(val1 - val2));
        } else if (sign == "*") {
            stack.push(QString::number(val1 * val2));
        } else if (sign == "/") {
            if (val2 == 0) {
                QMessageBox::warning(this, "Ошибка", "Деление на ноль!");
                stack.push(QString::number(val1));
            } else {
                stack.push(QString::number(val1 / val2));
            }
        }
        stack.push(sgn);
    } else {
        stack.push(ui->lineEdit->text());
        stack.push(sgn);
    }

    ui->lineEdit->clear();
    ui->lineEdit_2->setText(stack.toList().join(" "));
}

void MainWindow::on_pushButton_Equal_clicked()
{
    if (ui->lineEdit->text().length() != 0 && stack.length() == 2) {
        stack.push(ui->lineEdit->text());
    }

    if (stack.length() < 3) {
        return;
    }

    double val2 = stack.pop().toDouble();
    QString sign = stack.pop();
    double val1 = stack.pop().toDouble();

    if (sign == "+") {
        stack.push(QString::number(val1 + val2));
    } else if (sign == "-") {
        stack.push(QString::number(val1 - val2));
    } else if (sign == "*") {
        stack.push(QString::number(val1 * val2));
    } else if (sign == "/") {
        if (val2 == 0) {
            QMessageBox::warning(this, "Ошибка", "Деление на ноль!");
            stack.push(QString::number(val1));
        } else {
            stack.push(QString::number(val1 / val2));
        }
    }

    ui->lineEdit->setText(stack.pop());
    ui->lineEdit_2->clear();
}

void MainWindow::on_pushButton_Cos_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.length() == 0) {
        return;
    }
    double val = text.toDouble();
    double result = cos(val);
    ui->lineEdit->setText(QString::number(result));
    ui->lineEdit_2->setText("cos(" + text + ") = " + QString::number(result));
}

void MainWindow::on_pushButton_Lg_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.length() == 0) {
        return;
    }
    double val = text.toDouble();
    if (val <= 0) {
        QMessageBox::warning(this, "Ошибка", "Логарифм определен только для положительных чисел!");
        return;
    }
    double result = log10(val);
    ui->lineEdit->setText(QString::number(result));
    ui->lineEdit_2->setText("lg(" + text + ") = " + QString::number(result));
}

void MainWindow::on_pushButton_Square_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.length() == 0) {
        return;
    }
    double val = text.toDouble();
    double result = val * val;
    ui->lineEdit->setText(QString::number(result));
    ui->lineEdit_2->setText("(" + text + ")² = " + QString::number(result));
}

void MainWindow::on_pushButton_Factorial_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.length() == 0) {
        return;
    }
    int val = text.toInt();
    if (val < 0) {
        QMessageBox::warning(this, "Ошибка", "Факториал определен только для неотрицательных чисел!");
        return;
    }
    long long result = 1;
    for (int i = 2; i <= val; i++) {
        result *= i;
    }
    ui->lineEdit->setText(QString::number(result));
    ui->lineEdit_2->setText(text + "! = " + QString::number(result));
}

void MainWindow::on_pushButton_MS_clicked()
{
    memory = ui->lineEdit->text();
    ui->lineEdit_2->setText("M = " + memory);
}

void MainWindow::on_pushButton_MR_clicked()
{
    if (memory.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Память пуста!");
        return;
    }
    ui->lineEdit->setText(memory);
}

void MainWindow::on_pushButton_MC_clicked()
{
    memory = "";
    ui->lineEdit_2->clear();
}

void MainWindow::on_pushButton_MPlus_clicked()
{
    if (memory.isEmpty()) {
        memory = "0";
    }
    double memVal = memory.toDouble();
    double curVal = ui->lineEdit->text().toDouble();
    memory = QString::number(memVal + curVal);
    ui->lineEdit_2->setText("M = " + memory);
}

void MainWindow::on_pushButton_MMinus_clicked()
{
    if (memory.isEmpty()) {
        memory = "0";
    }
    double memVal = memory.toDouble();
    double curVal = ui->lineEdit->text().toDouble();
    memory = QString::number(memVal - curVal);
    ui->lineEdit_2->setText("M = " + memory);
}