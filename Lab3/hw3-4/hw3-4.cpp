#include <iostream>
#include <cstdint>
#include <vector>
#include <string.h>
#include <mutex>
#include <thread>
#include <cmath>

using namespace std;

int n, m;
vector<uint64_t> subsets;
uint64_t one = static_cast<uint64_t>(1), global_count = 0;
mutex mtx;

int solve(int index, uint64_t current) {
    int local_count = 0;
    if (index == m) {
        if (current == (one << n) - 1) return 1;
    } else {
        local_count += solve(index + 1, current);
        local_count += solve(index + 1, current | subsets[index]);
        return local_count;
    }
    return local_count;
}

void check(int index, uint64_t current) {
    int sum = solve(index, current);
    lock_guard<mutex> lock(mtx);
    global_count += sum;
}

int main(int argc, char* argv[]) {
    cin >> n >> m;

    int num_of_thread;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            num_of_thread = atoi(argv[i + 1]);
            break;
        }
    }

    subsets.resize(m);
    for (int i = 0; i < m; i++) {
        int p, temp;
        cin >> p;
        for (int j = 0; j < p; j++) {
            cin >> temp;
            subsets[i] |= (one << temp);
        }
    }

    thread t[8];
    int index = log2(num_of_thread);
    switch (index)
        {
        case 0:
            t[0] = thread(check, index, 0);
            break;
        case 1:
            t[0] = thread(check, index, 0);
            t[1] = thread(check, index, subsets[0]);
            break;
        case 2:
            t[0] = thread(check, index, 0);
            t[1] = thread(check, index, subsets[0]);
            t[2] = thread(check, index, subsets[1]);
            t[3] = thread(check, index, subsets[0] | subsets[1]);
            break;
        case 3:
            t[0] = thread(check, index, 0);
            t[1] = thread(check, index, subsets[0]);
            t[2] = thread(check, index, subsets[1]);
            t[3] = thread(check, index, subsets[2]);
            t[4] = thread(check, index, subsets[0] | subsets[1]);
            t[5] = thread(check, index, subsets[0] | subsets[2]);
            t[6] = thread(check, index, subsets[1] | subsets[2]);
            t[7] = thread(check, index, subsets[0] | subsets[1] | subsets[2]);
            break;
        default:
            break;
        }

    for (int i = 0; i < num_of_thread; i++) t[i].join();

    cout << global_count << endl;
    return 0;
}
