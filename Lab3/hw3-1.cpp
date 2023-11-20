#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int next_index = 0;

void count(int index) {
  static mutex io_mutex;
  int num = 1000000;
  while (num--) {}
  {
    unique_lock<mutex> lock(io_mutex);
    while (index != next_index) {
      lock.unlock();
      lock.lock();
    }
    
    cout << "I'm thread " << index << ", local count: 1000000\n";
    next_index++;
  }
}

int main(void) {
  thread t[100];

  for (int i = 0; i < 100; i++)
    t[i] = thread(count, i);

  for (int i = 0; i < 100; i++)
    t[i].join();
}
