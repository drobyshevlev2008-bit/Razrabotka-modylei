#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit_Array->setReadOnly(true);
    ui->textEdit_Result->setReadOnly(true);
    ui->textEdit_Matrix->setReadOnly(true);
    ui->textEdit_CountResult->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Create_clicked()
{
    QString sizeText = ui->lineEdit_Size->text();
    bool ok;
    int N = sizeText.toInt(&ok);

    if (!ok || N <= 0) {
        QMessageBox::information(this, "Ошибка",
                                 "Введите положительное целое число!");
        return;
    }

    arr.clear();
    for (int i = 0; i < N; i++) {
        arr.append(rand() % 100);
    }

    ui->textEdit_Array->clear();
    QString output = "Исходный массив (размер " + QString::number(N) + "):\n";
    output += "[ ";
    for (int i = 0; i < arr.size(); i++) {
        output += QString::number(arr[i]) + " ";
    }
    output += "]";
    ui->textEdit_Array->setText(output);
    ui->textEdit_Result->clear();
}

void MainWindow::on_pushButton_Transform_clicked()
{
    if (arr.isEmpty()) {
        QMessageBox::information(this, "Ошибка",
                                 "Сначала создайте массив!");
        return;
    }

    int firstElement = arr[0];
    QVector<int> transformedArr = arr;

    for (int i = 1; i < transformedArr.size() - 1; i++) {
        if (transformedArr[i] % 2 == 0) {
            transformedArr[i] += firstElement;
        }
    }

    ui->textEdit_Result->clear();
    QString result = "Преобразованный массив:\n";
    result += "[ ";
    for (int i = 0; i < transformedArr.size(); i++) {
        result += QString::number(transformedArr[i]) + " ";
    }
    result += "]";

    result += "\n\nПервый элемент: " + QString::number(firstElement);
    result += "\nК четным числам (кроме первого и последнего) прибавлен "
              + QString::number(firstElement);

    ui->textEdit_Result->setText(result);
}

void MainWindow::on_pushButton_CreateMatrix_clicked()
{
    QString rowsText = ui->lineEdit_Rows->text();
    QString colsText = ui->lineEdit_Cols->text();

    bool okRows, okCols;
    int m = rowsText.toInt(&okRows);
    int n = colsText.toInt(&okCols);

    if (!okRows || !okCols || m <= 0 || n <= 0) {
        QMessageBox::information(this, "Ошибка",
                                 "Введите положительные целые числа!");
        return;
    }

    matrix.clear();
    for (int i = 0; i < m; i++) {
        QVector<int> row;
        for (int j = 0; j < n; j++) {
            row.append(rand() % 100);
        }
        matrix.append(row);
    }

    ui->textEdit_Matrix->clear();
    QString output = "Матрица " + QString::number(m) + "x" + QString::number(n) + ":\n\n";
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            output += QString("%1").arg(matrix[i][j], 4);
        }
        output += "\n";
    }
    ui->textEdit_Matrix->setText(output);
    ui->textEdit_CountResult->clear();
}

void MainWindow::on_pushButton_Count_clicked()
{
    if (matrix.isEmpty()) {
        QMessageBox::information(this, "Ошибка",
                                 "Сначала создайте матрицу!");
        return;
    }

    ui->textEdit_CountResult->clear();
    QString result = "Количество элементов > среднего арифметического в каждой строке:\n\n";

    for (int i = 0; i < matrix.size(); i++) {
        QVector<int> row = matrix[i];

        int sum = 0;
        for (int j = 0; j < row.size(); j++) {
            sum += row[j];
        }
        double average = (double)sum / row.size();

        int count = 0;
        QString elements = "";
        for (int j = 0; j < row.size(); j++) {
            if (row[j] > average) {
                count++;
                elements += QString::number(row[j]) + " ";
            }
        }

        result += "Строка " + QString::number(i + 1) + ": ";
        result += "среднее = " + QString::number(average, 'f', 2);
        result += ", элементов > среднего = " + QString::number(count) + "\n";
        if (count > 0) {
            result += "  Элементы: " + elements + "\n";
        }
        result += "\n";
    }

    ui->textEdit_CountResult->setText(result);
}