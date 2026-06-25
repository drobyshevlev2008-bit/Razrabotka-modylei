#include <cstring>
#include <iostream>
#include <memory>
using namespace std;

struct t {
  char d[200];
  int p;
  bool c;
};

void s(t *ts, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1; i++) {
      if (ts[j].p < ts[j + 1].p) {
        t tmp = ts[j];
        ts[j] = ts[j + 1];
        ts[j + 1] = tmp;
      }
    }
  }
}

int main() {
  int cnt;
  cout << "Number of tasks: ";
  cin >> cnt;

  t *tasks = new t[cnt];

  for (int i = 0; i < cnt; i++) {
    cout << "Task desc: ";
    cin >> tasks[i].d;
    cout << "Priority (1-5): ";
    cin >> tasks[i].p;
    tasks[i].c = false;
  }

  s(tasks, cnt);
  cout << "Top 3 tasks: " << endl;

  for (int i = 0; i < 3 && i < cnt; i++) {
    cout << tasks[i].d << " (priority " << tasks[i].p << ")" << endl;
    delete[] tasks;
  }
  return 0;
}
