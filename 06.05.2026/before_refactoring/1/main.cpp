#include <iostream>
#include <string>
using namespace std;


int main(){
    setlocale(LC_ALL, "ru");

    //Вводимое число
    string number;

    cout << "Введите число: ";
    cin >> number;


    bool isNumber = true;
    bool isMinus = false;
    int symbol = 0;

    //Проверка первого символа
    if(number[0] == '-'){
        if(number.length() == 1){
            isNumber = false;
        }
        else{
            isMinus = true;
            symbol = 1;
        }
    }

    //Проверка остальных символов (Диапазон символа)
    for(int i = symbol; i < number.length(); i++){
        if(number[i] < '0' || number[i] > '9'){
            isNumber = false;
            break;
        }
    }

    //Вывод результата
    if (isNumber) {
        int num = 0;

        //Сборка числа из цифр
        for (int i = symbol; i < number.length(); i++) {
            num = num * 10 + (number[i] - '0');
        }

        //Проверка минуса
        if (isMinus) {
            num = -num;
        }

        cout << "Вы ввели: " << num << endl;
 
        cout << "Квадрат числа: " << num * num << endl;
    } 
    else {
        cout << "Вы ввели текст: " << number << endl;
    }

    return 0;
}
/*
n1 = 32
n2 = 17
N1 = 78
N2 = 56
n = 49
N = 134
V = 752
D = 52.6
H = 39555
*/