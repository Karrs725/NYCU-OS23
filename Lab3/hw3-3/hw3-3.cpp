#include <iostream>
#include <thread>
#include <string.h>

using namespace std;

int n, global_count = 0;

bool is_prime(int num) {
    if (num == 1) return false;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void check(int start, int end) {
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) global_count++;
    }
}

int main(int argc, char* argv[]) {
    cin >> n;

    int num_of_thread;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            num_of_thread = atoi(argv[i + 1]);
            break;
        }
    }

    int chunk_size = n / num_of_thread;
    thread t[8];
    for (int i = 0; i < num_of_thread; i++) {
        int start = i * chunk_size + 1;
        int end = (i != num_of_thread - 1) ? (i + 1) * chunk_size : n;
        cout << start << " " << end << endl;
        t[i] = thread(check, start, end);
    }

    for (int i = 0; i < num_of_thread; i++) t[i].join();

    cout << global_count << endl;
    return 0;
}
