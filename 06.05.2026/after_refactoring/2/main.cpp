#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//Сложение
double Plus(int first, int second){
    return first + second;
}

//Вычитание
double Minus(int first, int second){
    return first - second;
}

//Умножение
double Multi(int first, int second){
    return first * second;
}

//Деление
double Div(int first, int second){
    return first / second;
}

//Возведение в степень
double Pow(int number, int degree){
    return pow(number, degree);
}

//Умножение отрицательных чисел
double MultiNegative(int first, int second){
    if(first > 0 || second > 0){
        cout << "Вы ввели не отрицательные числа!" << endl;
        return 0;
    }
    else{
        return first * second;
    }
}

int main(){
    setlocale(LC_ALL, "ru");

    int choose;

    cout << "Выберите действие" << endl;
    cout << "1.Арифметические действия" << endl;
    cout << "2.Возведение в степень числа" << endl;
    cout << "3.Умножение отрицательных чисел" << endl;
    cout << "Ответ: ";
    cin >> choose;

    switch (choose)
    {
    case 1:{
        int firstNumber;
        char symbol;
        int secondNumber;

        cout << "Введите первое число, знак и второе число: " << endl;
        cin >> firstNumber >> symbol >> secondNumber;
        
        switch (symbol)
        {
        case '+':
            cout << "Результат: " << Plus(firstNumber, secondNumber) << endl;
            break;
        
        case '-':
            cout << "Результат: " << Minus(firstNumber, secondNumber) << endl;
            break;

        case '*':
            cout << "Результат: " << Multi(firstNumber, secondNumber) << endl;
            break;

        case '/':
            cout << "Результат: " << Div(firstNumber, secondNumber) << endl;
            break;
    
        default:
            break;
        }

        break;
    }

    case 2:{
        int number;
        cout << "Введите число: ";
        cin >> number;

        int degree;
        cout << "Введите значение, в которое нужно возвести число: ";
        cin >> degree;

        cout << "Результат: " << Pow(number, degree) << endl;

        break;
    }

    case 3:{
        int firstNegativeNumber;
        int secondNegativeNumber;

        cout << "Введите первое отрицательно число: ";
        cin >> firstNegativeNumber;
        cout << "Введите второе отрицательно число:";
        cin >> secondNegativeNumber;

        cout << "Результат: " << MultiNegative(firstNegativeNumber, secondNegativeNumber) << endl;
    }
    default:
        break;
    }

    return 0;
}
/*
n1 = 35
n2 = 28
N1 = 93
N2 = 58
n = 63
N = 151
V = 903
D = 36.2
H = 32689
*/