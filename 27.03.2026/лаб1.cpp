#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->pushButton_MinMax, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_MinMax_clicked);

    connect(ui->pushButton_Sort, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_Sort_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_MinMax_clicked()
{
// Получаем числа из полей ввода
    QString strX = ui->lineEdit_X->text();
    QString strY = ui->lineEdit_Y->text();
    QString strZ = ui->lineEdit_Z->text();

    bool ok1, ok2, ok3;

// Преобразуем строки в числа
    float x = strX.toFloat(&ok1);
    float y = strY.toFloat(&ok2);
    float z = strZ.toFloat(&ok3);

// Проверка на корректный ввод
    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::information(this, "Ошибка", "Введите корректные числа!");
        return;
    }

// Находим минимум и максимум
    float minVal = x;
    float maxVal = x;

    if (y < minVal) minVal = y;
    if (z < minVal) minVal = z;

    if (y > maxVal) maxVal = y;
    if (z > maxVal) maxVal = z;

// Находим "третье" число и заменяем его на разность
    float diff = maxVal - minVal;

// Определяем, какое число является "третьим"
    if (x != minVal && x != maxVal) {
        x = diff;
    } else if (y != minVal && y != maxVal) {
        y = diff;
    } else if (z != minVal && z != maxVal) {
        z = diff;
    }

// Выводим результат
    ui->lineEdit_X->setText(QString::number(x));
    ui->lineEdit_Y->setText(QString::number(y));
    ui->lineEdit_Z->setText(QString::number(z));

// Информационное сообщение
    QMessageBox::information(this, "Результат",
                             QString("Минимум: %1\nМаксимум: %2\nРазность: %3")
                                 .arg(minVal).arg(maxVal).arg(diff));
}

void MainWindow::on_pushButton_Sort_clicked()
{
// Получаем числа из полей ввода
    QString strX = ui->lineEdit_X->text();
    QString strY = ui->lineEdit_Y->text();
    QString strZ = ui->lineEdit_Z->text();

    bool ok1, ok2, ok3;

// Преобразуем строки в числа
    float x = strX.toFloat(&ok1);
    float y = strY.toFloat(&ok2);
    float z = strZ.toFloat(&ok3);

// Проверка на корректный ввод
    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::information(this, "Ошибка", "Введите корректные числа!");
        return;
    }

// Проверяем, упорядочены ли числа по убыванию
    if (x >= y && y >= z) {
        // Удваиваем
        x *= 2;
        y *= 2;
        z *= 2;
        QMessageBox::information(this, "Результат",
                                 "Числа упорядочены по убыванию!\nУдваиваем значения.");
    } else {
// Заменяем на противоположные
        x = -x;
        y = -y;
        z = -z;
        QMessageBox::information(this, "Результат",
                                 "Числа НЕ упорядочены по убыванию!\nЗаменяем на противоположные.");
    }

// Выводим результат
    ui->lineEdit_X->setText(QString::number(x));
    ui->lineEdit_Y->setText(QString::number(y));
    ui->lineEdit_Z->setText(QString::number(z));
}