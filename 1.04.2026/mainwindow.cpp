#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit_Stack->setReadOnly(true);
    ui->textEdit_StackResult->setReadOnly(true);
    ui->textEdit_Queue->setReadOnly(true);
    ui->textEdit_QueueResult->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_CreateStack_clicked()
{

    stack.clear();


    srand(time(0));

    for (int i = 0; i < 8; i++) {
        stack.push(rand() % 100);
    }


    ui->textEdit_Stack->clear();
    QString output = "Мой стек (8 элементов):\n";
    output += "Верх стека (последний добавленный) ↓\n";
    output += "[ ";

    for (int i = stack.size() - 1; i >= 0; i--) {
        output += QString::number(stack[i]) + " ";
    }
    output += "]";
    ui->textEdit_Stack->setText(output);


    ui->textEdit_StackResult->clear();
}

void MainWindow::on_pushButton_TransformStack_clicked()
{

    if (stack.isEmpty()) {
        QMessageBox::information(this, "Ошибка",
                                 "Сначала создайте стек!");
        return;
    }

    if (stack.size() != 8) {
        QMessageBox::information(this, "Ошибка",
                                 "Стек должен содержать ровно 8 элементов!");
        return;
    }

    QStack<int> tempStack = stack;


    for (int i = 0; i < 4; i++) {

        int first = tempStack[i];
        int last = tempStack[7 - i];
        int product = first * last;

        tempStack[i] = product;
        tempStack[7 - i] = product;
    }

    ui->textEdit_StackResult->clear();
    QString result = "Я ЗАМЕНИЛ ЭЛЕМЕНТЫ СТЕКА!";
    result += "\n========================================\n\n";


    result += "Мои вычисления:\n\n";
    for (int i = 0; i < 4; i++) {
        result += "ШАГ " + QString::number(i + 1) + ": ";
        result += QString::number(stack[i]) + " * " +
                  QString::number(stack[7 - i]) + " = " +
                  QString::number(stack[i] * stack[7 - i]);
        result += "\n    Заменяю оба элемента на " +
                  QString::number(stack[i] * stack[7 - i]) + "\n\n";
    }

    result += "НОВЫЙ СТЕК:\n";
    result += "Верх стека ↓\n";
    result += "[ ";
    for (int i = tempStack.size() - 1; i >= 0; i--) {
        result += QString::number(tempStack[i]) + " ";
    }
    result += "]";

    result += "\n\nИтог: я перемножил симметричные элементы и записал "
              "произведения обратно в стек.";

    ui->textEdit_StackResult->setText(result);
}



void MainWindow::on_pushButton_CreateQueue_clicked()
{

    queue.clear();


    srand(time(0));


    for (int i = 0; i < 8; i++) {
        int num = rand() % 71 - 20;
        queue.enqueue(num);
    }


    ui->textEdit_Queue->clear();
    QString output = "Моя очередь (8 элементов):\n";
    output += "Начало → ";
    for (int i = 0; i < queue.size(); i++) {
        output += QString::number(queue[i]) + " ";
    }
    output += "← Конец";
    output += "\n\nДиапазон чисел: [-20; 50]";
    ui->textEdit_Queue->setText(output);


    ui->textEdit_QueueResult->clear();
}

void MainWindow::on_pushButton_Calculate_clicked()
{

    if (queue.isEmpty()) {
        QMessageBox::information(this, "Ошибка",
                                 "Сначала создайте очередь!");
        return;
    }


    if (queue.size() != 8) {
        QMessageBox::information(this, "Ошибка",
                                 "Очередь должна содержать ровно 8 элементов!");
        return;
    }


    QQueue<int> tempQueue;


    for (int i = 0; i < queue.size() - 1; i++) {
        int first = queue[i];
        int second = queue[i + 1];
        int average = (first + second) / 2;
        tempQueue.enqueue(average);
    }


    ui->textEdit_QueueResult->clear();
    QString result = "Я НАШЕЛ СРЕДНЕЕ СОСЕДНИХ ЭЛЕМЕНТОВ!";
    result += "\n========================================\n\n";

    result += "Моя исходная очередь:\n";
    result += "[ ";
    for (int i = 0; i < queue.size(); i++) {
        result += QString::number(queue[i]) + " ";
    }
    result += "]\n\n";

    result += "Мои вычисления:\n\n";
    for (int i = 0; i < queue.size() - 1; i++) {
        int first = queue[i];
        int second = queue[i + 1];
        int avg = (first + second) / 2;

        result += "Пара " + QString::number(i + 1) + ": ";
        result += QString::number(first) + " и " +
                  QString::number(second);
        result += "\n    (" + QString::number(first) + " + " +
                  QString::number(second) + ") / 2 = " +
                  QString::number(avg) + "\n\n";
    }

    result += "НОВАЯ ОЧЕРЕДЬ (средние значения):\n";
    result += "Начало → ";
    for (int i = 0; i < tempQueue.size(); i++) {
        result += QString::number(tempQueue[i]) + " ";
    }
    result += "← Конец";

    result += "\n\nРазмер новой очереди: " +
              QString::number(tempQueue.size()) + " элементов";
    result += "\n(было 8 элементов, стало 7)";

    result += "\n\nЯ вычислил среднее арифметическое для каждой пары "
              "соседних элементов исходной очереди.";

    ui->textEdit_QueueResult->setText(result);
}