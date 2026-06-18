#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QStringList>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit_Countries->setReadOnly(true);
    ui->textEdit_Result->setReadOnly(true);

    ui->spinBox_Countries->setMinimum(1);
    ui->spinBox_Countries->setMaximum(10);
    ui->spinBox_Countries->setValue(3);

    ui->lineEdit_Cars->setText("Toyota, BMW, Audi, Ford, Mercedes, Honda, Nissan, Volkswagen");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Generate_clicked()
{
    QString carsText = ui->lineEdit_Cars->text();
    carBrands = carsText.split(",", Qt::SkipEmptyParts);

    for (int i = 0; i < carBrands.size(); i++) {
        carBrands[i] = carBrands[i].trimmed();
    }

    if (carBrands.isEmpty()) {
        QMessageBox::information(this, "Ошибка",
                                 "Введите марки машин через запятую!");
        return;
    }

    srand(time(0));

    int countryCount = ui->spinBox_Countries->value();
    countryCars.clear();
    countries.clear();

    for (int i = 0; i < countryCount; i++) {
        QString countryName = "Страна " + QString::number(i + 1);
        countries.append(countryName);

        QSet<QString> carSet;
        int carCount = rand() % carBrands.size() + 1;

        for (int j = 0; j < carCount; j++) {
            int index = rand() % carBrands.size();
            carSet.insert(carBrands[index]);
        }

        countryCars[countryName] = carSet;
    }

    ui->textEdit_Countries->clear();
    QString output = "ДАННЫЕ ПО СТРАНАМ:\n";
    output += "========================================\n\n";

    for (int i = 0; i < countries.size(); i++) {
        QString country = countries[i];
        output += country + ":\n";
        output += "  Доставленные марки: ";

        QSet<QString> cars = countryCars[country];
        QStringList carList = cars.values();

        if (carList.isEmpty()) {
            output += "нет машин";
        } else {
            for (int j = 0; j < carList.size(); j++) {
                output += carList[j];
                if (j < carList.size() - 1) output += ", ";
            }
        }
        output += "\n\n";
    }

    ui->textEdit_Countries->setText(output);
    ui->textEdit_Result->clear();
}

void MainWindow::on_pushButton_Analyze_clicked()
{
    if (countryCars.isEmpty()) {
        QMessageBox::information(this, "Ошибка",
                                 "Сначала сгенерируйте данные!");
        return;
    }

    int countryCount = countries.size();

    QSet<QString> allCars;
    QSet<QString> inAllCountries;
    QSet<QString> inSomeCountries;
    QSet<QString> inNoCountries;

    for (int i = 0; i < carBrands.size(); i++) {
        allCars.insert(carBrands[i]);
    }

    for (int i = 0; i < carBrands.size(); i++) {
        QString brand = carBrands[i];
        int count = 0;

        for (int j = 0; j < countries.size(); j++) {
            QString country = countries[j];
            if (countryCars[country].contains(brand)) {
                count++;
            }
        }

        if (count == countryCount) {
            inAllCountries.insert(brand);
        } else if (count > 0) {
            inSomeCountries.insert(brand);
        } else {
            inNoCountries.insert(brand);
        }
    }

    ui->textEdit_Result->clear();
    QString result = "РЕЗУЛЬТАТЫ АНАЛИЗА ПОСТАВОК:\n";
    result += "========================================\n\n";

    result += "Всего марок: " + QString::number(allCars.size()) + "\n";
    result += "Всего стран: " + QString::number(countryCount) + "\n\n";

    result += "1. МАРКИ, ДОСТАВЛЕННЫЕ ВО ВСЕ СТРАНЫ:\n";
    QStringList allList = inAllCountries.values();
    if (allList.isEmpty()) {
        result += "   Нет таких марок\n";
    } else {
        for (int i = 0; i < allList.size(); i++) {
            result += "   • " + allList[i] + "\n";
        }
    }
    result += "\n";

    result += "2. МАРКИ, ДОСТАВЛЕННЫЕ В НЕКОТОРЫЕ СТРАНЫ:\n";
    QStringList someList = inSomeCountries.values();
    if (someList.isEmpty()) {
        result += "   Нет таких марок\n";
    } else {
        for (int i = 0; i < someList.size(); i++) {
            result += "   • " + someList[i] + "\n";
        }
    }
    result += "\n";

    result += "3. МАРКИ, НЕ ДОСТАВЛЕННЫЕ НИ В ОДНУ СТРАНУ:\n";
    QStringList noList = inNoCountries.values();
    if (noList.isEmpty()) {
        result += "   Нет таких марок\n";
    } else {
        for (int i = 0; i < noList.size(); i++) {
            result += "   • " + noList[i] + "\n";
        }
    }
    result += "\n";

    result += "ДЕТАЛЬНАЯ ИНФОРМАЦИЯ ПО КАЖДОЙ МАРКЕ:\n";
    result += "----------------------------------------\n";
    for (int i = 0; i < carBrands.size(); i++) {
        QString brand = carBrands[i];
        result += brand + " → ";

        QStringList countriesWithBrand;
        for (int j = 0; j < countries.size(); j++) {
            QString country = countries[j];
            if (countryCars[country].contains(brand)) {
                countriesWithBrand.append(country);
            }
        }

        if (countriesWithBrand.isEmpty()) {
            result += "не доставлена никуда\n";
        } else if (countriesWithBrand.size() == countryCount) {
            result += "доставлена во все страны\n";
        } else {
            result += "доставлена в: ";
            for (int j = 0; j < countriesWithBrand.size(); j++) {
                result += countriesWithBrand[j];
                if (j < countriesWithBrand.size() - 1) result += ", ";
            }
            result += "\n";
        }
    }

    ui->textEdit_Result->setText(result);
}