#include <iostream>
#include <cstring>

struct Student {
    char* name;
    int* grades;
    int gradesCount;
    float avg;
};

void computeAverage(Student* s) {
    int sum = 0;
    for (int i = 0; i < s->gradesCount; ++i) {
        sum += s->grades[i];
    }
    s->avg = (float)sum / s->gradesCount;
}

void bubbleSort(Student** arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j]->avg < arr[j + 1]->avg) {
                Student* tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main() {
    int n;
    std::cout << "Enter number of students: ";
    std::cin >> n;

    Student** students = new Student*[n];
    for (int i = 0; i < n; ++i) {
        students[i] = new Student;
        char buf[256];
        std::cout << "Enter name: ";
        std::cin >> buf;
        students[i]->name = new char[strlen(buf)+1];
        strcpy(students[i]->name, buf);
    
        std::cout << "Enter number of grades: ";
        int m;
        std::cin >> m;
        students[i]->gradesCount = m;
        students[i]->grades = new int[m];
        for (int j = 0; j < m; ++j) {
            std::cout << "Grade " << j+1 << ": ";
            std::cin >> students[i]->grades[j];
        }
        computeAverage(students[i]);
    }

    // Print averages
    for (int i = 0; i < n; ++i) {
        std::cout << students[i]->name << " average: " << students[i]->avg << std::endl;
    }

    // Sort by average descending
    bubbleSort(students, n);

std::cout << "\nTop 3 students:\n";
    for (int i = 0; i < 3 && i < n; ++i) {
        std::cout << i+1 << " " << students[i]->name << " (" << students[i]->avg << ") " << std::endl;
    }

    std::cout << "\nsorted list of all students:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << students[i]->name << " - " << students[i]->avg << std::endl;
    }

    // Memory cleanup
    for (int i = 0; i < n; ++i) {
        delete[] students[i]->name;
        delete[] students[i]->grades;
        delete students[i];
    }

    delete[] students;

    return 0;
}
