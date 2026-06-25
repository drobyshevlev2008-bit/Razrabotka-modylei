#include <cstring>
#include <iostream>
#include <memory>
using namespace std;

// Структура
struct Task {
  char desc[200];
  int priority;
  bool completed;
};

// Функция сортировки
void sortTasks(Task *tasks, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (tasks[j].priority < tasks[j + 1].priority) {
        Task tmp = tasks[j];
        tasks[j] = tasks[j + 1];
        tasks[j + 1] = tmp;
      }
    }
  }
}

// Ввод одной задачи
void inputTask(Task &task, int index) {
  cout << "Task " << index + 1 << " description: ";
  cin >> task.desc;
  cout << "Priority (1-5): ";
  cin >> task.priority;
  task.completed = false;
}

// Главная
int main() {
  int cnt;
  cout << "Number of tasks: ";
  cin >> cnt;

  // Объект
  Task *tasks = new Task[cnt];

  for (int i = 0; i < cnt; i++) {
    inputTask(tasks[i], i);
  }

  sortTasks(tasks, cnt);

  cout << "Top 3 tasks: " << endl;
  for (int i = 0; i < 3 && i < cnt; i++) {
    cout << tasks[i].desc << " (priority " << tasks[i].priority << ")" << endl;
  }

  delete[] tasks; // БЫЛО: внутри цикла, ИСПРАВЛЕНО: один раз в конце
  return 0;
}
