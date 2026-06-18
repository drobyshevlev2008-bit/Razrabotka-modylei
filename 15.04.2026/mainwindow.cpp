#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <ctime>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit_FileF->setReadOnly(true);
    ui->textEdit_Result->setReadOnly(true);

    inputFilePath = "C:/file_f.txt";
    outputFilePath = "C:/file_g.txt";

    ui->lineEdit_InputFile->setText(inputFilePath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Create_clicked()
{
    inputFilePath = ui->lineEdit_InputFile->text();

    if (inputFilePath.isEmpty()) {
        QMessageBox::information(this, "Ошибка", "Укажите путь к файлу!");
        return;
    }

    QFile file(inputFilePath);

    if (file.exists()) {
        file.remove();
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Ошибка", "Не удалось создать файл!");
        return;
    }

    srand(time(0));

    QTextStream stream(&file);

    int count = rand() % 15 + 10;

    for (int i = 0; i < count; i++) {
        int num = rand() % 200 - 50;
        stream << num;
        if (i < count - 1) {
            stream << " ";
        }
    }

    file.close();

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Ошибка", "Не удалось прочитать файл!");
        return;
    }

    QTextStream readStream(&file);
    QString content = readStream.readAll();
    file.close();

    ui->textEdit_FileF->clear();
    QString output = "Файл f создан!\n";
    output += "Количество чисел: " + QString::number(count) + "\n";
    output += "Содержимое:\n";
    output += content;
    ui->textEdit_FileF->setText(output);

    ui->textEdit_Result->clear();
}

void MainWindow::on_pushButton_Process_clicked()
{
    inputFilePath = ui->lineEdit_InputFile->text();

    QFile inputFile(inputFilePath);

    if (!inputFile.exists()) {
        QMessageBox::information(this, "Ошибка", "Файл f не найден! Сначала создайте его.");
        return;
    }

    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Ошибка", "Не удалось открыть файл для чтения!");
        return;
    }

    QTextStream readStream(&inputFile);
    QString content = readStream.readAll();
    inputFile.close();

    QStringList numbers = content.split(" ", Qt::SkipEmptyParts);

    QList<int> evenNumbers;
    QList<int> divisibleBy3Not7;
    QList<int> perfectSquares;

    for (int i = 0; i < numbers.size(); i++) {
        bool ok;
        int num = numbers[i].toInt(&ok);

        if (!ok) continue;

        if (num % 2 == 0) {
            evenNumbers.append(num);
        }

        if (num % 3 == 0 && num % 7 != 0) {
            divisibleBy3Not7.append(num);
        }

        int sqrtNum = (int)sqrt(num);
        if (sqrtNum * sqrtNum == num && num >= 0) {
            perfectSquares.append(num);
        }
    }

    QFile outputFile(outputFilePath);

    if (outputFile.exists()) {
        outputFile.remove();
    }

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Ошибка", "Не удалось создать файл g!");
        return;
    }

    QTextStream writeStream(&outputFile);

    writeStream << "РЕЗУЛЬТАТЫ ОБРАБОТКИ ФАЙЛА f\n";
    writeStream << "========================================\n\n";

    writeStream << "а) Четные числа:\n";
    if (evenNumbers.isEmpty()) {
        writeStream << "  Нет четных чисел\n";
    } else {
        for (int i = 0; i < evenNumbers.size(); i++) {
            writeStream << evenNumbers[i] << " ";
        }
        writeStream << "\n";
    }
    writeStream << "\n";

    writeStream << "б) Числа, делящиеся на 3 и не делящиеся на 7:\n";
    if (divisibleBy3Not7.isEmpty()) {
        writeStream << "  Нет таких чисел\n";
    } else {
        for (int i = 0; i < divisibleBy3Not7.size(); i++) {
            writeStream << divisibleBy3Not7[i] << " ";
        }
        writeStream << "\n";
    }
    writeStream << "\n";

    writeStream << "в) Числа, являющиеся точными квадратами:\n";
    if (perfectSquares.isEmpty()) {
        writeStream << "  Нет чисел, являющихся точными квадратами\n";
    } else {
        for (int i = 0; i < perfectSquares.size(); i++) {
            writeStream << perfectSquares[i] << " ";
        }
        writeStream << "\n";
    }
    writeStream << "\n";

    writeStream << "Статистика:\n";
    writeStream << "Всего чисел в файле f: " << numbers.size() << "\n";
    writeStream << "Четных чисел: " << evenNumbers.size() << "\n";
    writeStream << "Чисел, делящихся на 3 и не на 7: " << divisibleBy3Not7.size() << "\n";
    writeStream << "Точных квадратов: " << perfectSquares.size() << "\n";

    outputFile.close();

    if (!outputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Ошибка", "Не удалось прочитать файл g!");
        return;
    }

    QTextStream resultStream(&outputFile);
    QString resultContent = resultStream.readAll();
    outputFile.close();

    ui->textEdit_Result->clear();
    ui->textEdit_Result->setText(resultContent);

    QMessageBox::information(this, "Готово",
                             "Файл g успешно создан!\n"
                             "Путь: " + outputFilePath + "\n\n" +
                                 "Найдено:\n" +
                                 "- Четных чисел: " + QString::number(evenNumbers.size()) + "\n" +
                                 "- Делящихся на 3 и не на 7: " + QString::number(divisibleBy3Not7.size()) + "\n" +
                                 "- Точных квадратов: " + QString::number(perfectSquares.size()));
}