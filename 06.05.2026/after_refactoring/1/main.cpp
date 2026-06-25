#include <iostream>
#include <string>
using namespace std;

//Проверка строки (Целое число)
bool isInteger(const string& str) {
    if (str.empty()) return false;

    int start = 0;
    //Проверка минуса
    if (str[0] == '-') {
        if (str.length() == 1) return false; // просто "-"
        start = 1;
    }

    //Проверка наличия букв
    for (int i = start; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

//Преобразование строки в целое число
int stringToInt(const string& str) {
    int num = 0;
    int start = (str[0] == '-') ? 1 : 0;

    for (int i = start; i < str.length(); i++) {
        num = num * 10 + (str[i] - '0');
    }

    return (str[0] == '-') ? -num : num;
}

int main() {
    setlocale(LC_ALL, "ru");

    string input;
    cout << "Введите число: ";
    cin >> input;

    //Вывод результата
    if (isInteger(input)) {
        int num = stringToInt(input);

        if (input.length() == 1 && input[0] != '-')
            cout << "Вы ввели цифру: " << num << endl;
        else
            cout << "Вы ввели число: " << num << endl;

        cout << "Квадрат числа: " << num * num << endl;
    } else {
        cout << "Вы ввели текст: " << input << endl;
    }

    return 0;
}
/*
n1 = 39
n2 = 17
N1 = 70
N2 = 53
n = 56
N = 123
V = 715
D = 60.8
H = 43472
*/