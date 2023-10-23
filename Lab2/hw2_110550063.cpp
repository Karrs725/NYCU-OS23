#include <bits/stdc++.h>
using namespace std;

struct Process{
    int arrival_time;
    int bust_time;
    int remain_time;
    int wait_time = 0;
    int turnaround_time;
    int complete_time;
};

struct Queue{
    int mode;
    int time_quantum;
    vector<int> process_in_queue;
};

int FCFS(vector<Queue> &q, vector<Process> &p, int num_of_process){
    bool end = false;
    
    int time = 0, id = 0, total_wait = 0;
    for (int i = 0; i < num_of_process; i++)
    {
        total_wait += p[i].wait_time;
    }
    
    while (!end){
        if (p[id].arrival_time == time){
            p[id].wait_time = p[id];
            id++;

        }
        
    }
}

int main(){
    int N, M, global_time = 0, id = 0;
    bool end = false;
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
        p.remain_time = p.bust_time;
        processes.push_back(p);
    }

    
    

    if (N == 1)
    {
        switch (queues[0].mode)
        {
        case 0:
            FCFS();
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

