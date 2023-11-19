#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>

using namespace std;

sem_t semaphore;

void count(int index) {
  int num = 1000000;
  while (num--) {}
  {
    sem_wait(&semaphore);
    cout << "I'm thread " << index << ", local count: 1000000\n";
    sem_post(&semaphore);
  }
}

int main(void) {
  thread t[100];

  for (int i = 0; i < 100; i++)
    t[i] = thread(count, i);

  for (int i = 0; i < 100; i++)
    t[i].join();
}
