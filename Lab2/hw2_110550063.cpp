#include <bits/stdc++.h>
using namespace std;

struct process{
    int arrival_time;
    int bust_time;
};

void FCFS(process p, int t);

int main(){
    int N, M, time = 0;
    vector<vector<int>> queues;
    vector<process> processes;
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        int mode, time_quantum;
        vector<int> q;
        cin >> mode >> time_quantum;
        q.push_back(mode);
        q.push_back(time_quantum);
        queues.push_back(q);
    }
    for (int i = 0; i < M; i++){
        process p;
        cin >> p.arrival_time >> p.bust_time;
        processes.push_back(p);
    }    
}

