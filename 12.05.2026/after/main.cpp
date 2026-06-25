#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//Структура Student
struct Student {
    char* name;
    int* grades;
    int gradesCount;
    float avg;
};

//Вычисление среднего 
void computeAverage(Student* s) {
    int sum = 0;
    for (int i = 0; i < s->gradesCount; ++i) {
        sum += s->grades[i];
    }
    s->avg = (float)sum / s->gradesCount;
}

//Сортировка пузырьком
void bubbleSort(Student** arr, int n) {
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j]->avg < arr[j+1]->avg) {
                Student* tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

//Вывод топ-3 студентов
void printTop(Student** students, int n) {
    cout << "\nTop 3 students:\n";
    int topCount = (n < 3) ? n : 3;
    for (int i = 0; i < topCount; ++i) {
        cout << i+1 << " " << students[i]->name << " (" << students[i]->avg << ")" << endl;
    }
}

//Вывод всех студентов
void printAll(Student** students, int n) {
    cout << "\nSorted list of all students:\n";
    for (int i = 0; i < n; ++i) {
        cout << students[i]->name << " - " << students[i]->avg << endl;
    }
}

//Очистка памяти
void cleanup(Student** students, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] students[i]->name;
        delete[] students[i]->grades;
        delete students[i];
    }
    delete[] students;
}


int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student** students = new Student*[n];
    
    for (int i = 0; i < n; ++i) {
        students[i] = new Student;
        
        char buf[256];
        cout << "Enter name: ";
        cin >> buf;
        students[i]->name = new char[strlen(buf)+1];
        strcpy(students[i]->name, buf);
        
        cout << "Enter number of grades: ";
        int m;
        cin >> m;
        students[i]->gradesCount = m;
        students[i]->grades = new int[m];
        
        for (int j = 0; j < m; ++j) {
            cout << "Grade " << j+1 << ": ";
            cin >> students[i]->grades[j];
        }
        computeAverage(students[i]);
    }
    
    printAll(students, n);
    bubbleSort(students, n);
    printTop(students, n);
    cleanup(students, n);
    
    return 0;
}