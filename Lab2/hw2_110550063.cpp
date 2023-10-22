#include <bits/stdc++.h>
using namespace std;

struct Process{
    int arrival_time;
    int bust_time;
    int remain_time;
    int wait_time;
    int turnaround_time;
};

struct Queue{
    int mode;
    int time_quantum;
    vector<int> process_in_queue;
};



int main(){
    int N, M, time = 0;
    vector<Queue> queues;
    vector<Process> processes;
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        Queue q;
        cin >> q.mode >> q.time_quantum;
        queues.push_back(q);
    }
    for (int i = 0; i < M; i++){
        Process p;
        cin >> p.arrival_time >> p.bust_time;
        processes.push_back(p);
    }

    if (M == 1)
    {
        switch (queues[0].mode)
        {
        case 0:
            /* code */
            break;
        case 1:

            break;
        case 2:

            break;
        default:
            break;
        }
    }
      
}

