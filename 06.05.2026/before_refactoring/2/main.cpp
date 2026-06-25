#include <iostream>
#include <string>
#include <cmath>
using namespace std;

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
            cout << "Результат " << firstNumber << " + " << secondNumber << " = " << firstNumber + secondNumber << endl;
            break;
        
        case '-':
            cout << "Результат " << firstNumber << " - " << secondNumber << " = " << firstNumber - secondNumber << endl;
            break;

        case '*':
            cout << "Результат " << firstNumber << " * " << secondNumber << " = " << firstNumber * secondNumber << endl;
            break;

        case '/':
            cout << "Результат " << firstNumber << " / " << secondNumber << " = " << firstNumber / secondNumber << endl;
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

        double result_1 = pow(number, degree);
        cout << "Результат: " << result_1 << endl;

        break;
    }

    case 3:{
        int firstNegativeNumber;
        int secondNegativeNumber;

        cout << "Введите первое отрицательно число: ";
        cin >> firstNegativeNumber;
        cout << "Введите второе отрицательно число:";
        cin >> secondNegativeNumber;

        if(firstNegativeNumber > 0 || secondNegativeNumber > 0){
            cout << "Вы ввели не отрицательное число!" << endl;
            break;
        }
        else{
            int result_2 = firstNegativeNumber * secondNegativeNumber;
            cout << "Результат: " << result_2 << endl;
        }
    }
    default:
        break;
    }

    return 0;
}
/*
n1 = 35
n2 = 34
N1 = 92
N2 = 68
n = 69
N = 160
V = 978
D = 35
H = 34230
*/