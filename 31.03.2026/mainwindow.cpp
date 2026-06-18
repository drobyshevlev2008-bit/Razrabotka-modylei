#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_List->setReadOnly(true);
    ui->textEdit_Result->setReadOnly(true);
    ui->textEdit_LinkList->setReadOnly(true);
    ui->textEdit_SortResult->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Create_clicked()
{
    QString sizeText = ui->lineEdit_Size->text();
    bool ok;
    int size = sizeText.toInt(&ok);

    if (!ok || size <= 0) {
        QMessageBox::information(this, "Ошибка",
                                 "Введите положительное целое число для размера списка!");
        return;
    }

    list.clear();
    for (int i = 0; i < size; i++) {
        list.append(rand() % 100);
    }

    ui->textEdit_List->clear();
    QString output = "Исходный список (размер " + QString::number(size) + "):\n";
    output += "[ ";
    for (int i = 0; i < list.size(); i++) {
        output += QString::number(list[i]) + " ";
    }
    output += "]";
    ui->textEdit_List->setText(output);
    ui->textEdit_Result->clear();
    ui->lineEdit_N->clear();
    ui->lineEdit_K->clear();
}

void MainWindow::on_pushButton_Delete_clicked()
{
    if (list.isEmpty()) {
        QMessageBox::information(this, "Ошибка",
                                 "Сначала создайте список!");
        return;
    }

    QString nText = ui->lineEdit_N->text();
    QString kText = ui->lineEdit_K->text();

    bool okN, okK;
    int N = nText.toInt(&okN);
    int K = kText.toInt(&okK);

    if (!okN || !okK) {
        QMessageBox::information(this, "Ошибка",
                                 "Введите целые числа для позиций!");
        return;
    }

    if (N < 0 || K >= list.size() || N > K) {
        QMessageBox::information(this, "Ошибка",
                                 "Некорректные позиции!\n"
                                 "Условия: 0 <= N <= K < " + QString::number(list.size()));
        return;
    }

    QList<int> tempList = list;

    for (int i = K; i >= N; i--) {
        tempList.removeAt(i);
    }

    ui->textEdit_Result->clear();
    QString result = "Удалены элементы с позиций " + QString::number(N) +
                     " по " + QString::number(K) + "\n\n";
    result += "Результат (размер " + QString::number(tempList.size()) + "):\n";
    result += "[ ";
    for (int i = 0; i < tempList.size(); i++) {
        result += QString::number(tempList[i]) + " ";
    }
    result += "]";

    result += "\n\nУдаленные элементы: [ ";
    for (int i = N; i <= K; i++) {
        result += QString::number(list[i]) + " ";
    }
    result += "]";

    ui->textEdit_Result->setText(result);
}

void MainWindow::on_pushButton_CreateLink_clicked()
{
    QString sizeText = ui->lineEdit_LinkSize->text();
    bool ok;
    int size = sizeText.toInt(&ok);

    if (!ok || size <= 0) {
        QMessageBox::information(this, "Ошибка",
                                 "Введите положительное целое число для размера связного списка!");
        return;
    }

    linkedList.clear();
    for (int i = 0; i < size; i++) {
        linkedList.append(rand() % 100);
    }

    ui->textEdit_LinkList->clear();
    QString output = "Исходный связный список (размер " + QString::number(size) + "):\n";
    output += "[ ";

    QLinkedList<int>::iterator it = linkedList.begin();
    while (it != linkedList.end()) {
        output += QString::number(*it) + " ";
        ++it;
    }
    output += "]";
    ui->textEdit_LinkList->setText(output);
    ui->textEdit_SortResult->clear();
}

void MainWindow::on_pushButton_Sort_clicked()
{
    if (linkedList.isEmpty()) {
        QMessageBox::information(this, "Ошибка",
                                 "Сначала создайте связный список!");
        return;
    }

    QLinkedList<int> sortedList = linkedList;

    QList<int> tempList;
    QLinkedList<int>::iterator it = sortedList.begin();
    while (it != sortedList.end()) {
        tempList.append(*it);
        ++it;
    }

    for (int i = 0; i < tempList.size() - 1; i++) {
        for (int j = i + 1; j < tempList.size(); j++) {
            if (tempList[i] < tempList[j]) {
                int temp = tempList[i];
                tempList[i] = tempList[j];
                tempList[j] = temp;
            }
        }
    }

    sortedList.clear();
    for (int i = 0; i < tempList.size(); i++) {
        sortedList.append(tempList[i]);
    }

    ui->textEdit_SortResult->clear();
    QString result = "Связный список, ОТСОРТИРОВАННЫЙ ПО УБЫВАНИЮ:\n";
    result += "[ ";

    QLinkedList<int>::iterator itResult = sortedList.begin();
    while (itResult != sortedList.end()) {
        result += QString::number(*itResult) + " ";
        ++itResult;
    }
    result += "]";

    result += "\n\nСортировка выполнена по убыванию (от большего к меньшему)";

    ui->textEdit_SortResult->setText(result);
}