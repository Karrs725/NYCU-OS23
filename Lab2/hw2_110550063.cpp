#include <bits/stdc++.h>
using namespace std;

struct Process{
    int arrival_time;
    int burst_time;
    int remain_time;
    int wait_time = 0;
    int turn_around_time;
    int complete_time = 0;
    int queue_time;
    int idx;
};

struct Queue{
    int mode;
    int time_quantum;
    int time_quantum_left;
    vector<Process> process_in_queue;
};

bool SRTF_cmp(Process p1, Process p2){
    if (p1.remain_time == p2.remain_time)
    {
        return p1.arrival_time < p2.arrival_time;
    }
    return p1.remain_time < p2.remain_time;
}

Process vector_pop_front(vector<Process> &v){
    Process p;
    p = v[0];
    for (int i = 0; i < v.size() - 1; i++)
    {
        v[i] = v[i + 1];
    }
    v.pop_back();
    return p;
}

int main(){
    int N, M, global_time = 0, id = 0, queue_now_processing = 0, current_process, total_turn_around_time = 0, total_wait_time = 0;
    bool end = false, is_complete = true;
    vector<Queue> queues;
    vector<Process> processes;
    vector<int> done;
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        Queue q;
        cin >> q.mode >> q.time_quantum;
        q.time_quantum_left = q.time_quantum;
        queues.push_back(q);
    }
    for (int i = 0; i < M; i++){
        Process p;
        cin >> p.arrival_time >> p.burst_time;
        p.remain_time = p.burst_time;
        p.queue_time = p.arrival_time;
        p.idx = i;
        processes.push_back(p);
    }

    while (!end)
    {
        /* new arrival */
        if (processes[id].arrival_time == global_time)
        {
            if (queue_now_processing != 0)
            {
                queues[queue_now_processing].time_quantum_left = queues[queue_now_processing].time_quantum;
                if (is_complete)
                {
                    is_complete = false;
                }
                else
                {
                    processes[current_process].queue_time = global_time;
                    Process temp_p = vector_pop_front(queues[queue_now_processing].process_in_queue);
                    temp_p.queue_time = global_time;
                    if (queue_now_processing < N - 1)
                    {
                        queues[queue_now_processing + 1].process_in_queue.push_back(temp_p);
                        if (queues[queue_now_processing + 1].mode == 1) sort(queues[queue_now_processing + 1].process_in_queue.begin(), queues[queue_now_processing + 1].process_in_queue.end(), SRTF_cmp);
                    }
                    else
                    {
                        queues[queue_now_processing].process_in_queue.push_back(temp_p);
                        if (queues[queue_now_processing].mode == 1) sort(queues[queue_now_processing].process_in_queue.begin(), queues[queue_now_processing].process_in_queue.end(), SRTF_cmp);
                    }
                }
                queue_now_processing = 0;
                queues[0].process_in_queue.push_back(processes[id]);
                current_process = id;
            }
            else
            {
                if (is_complete)
                {
                    is_complete = false;
                    if (queues[0].process_in_queue.empty())
                    {
                        queues[0].process_in_queue.push_back(processes[id]);
                        current_process = id;
                    }
                    else
                    {
                        if (queues[0].mode == 1)
                        {
                            if (queues[0].process_in_queue[0].remain_time > processes[id].remain_time)
                            {
                                current_process = id;
                            }
                            queues[0].process_in_queue.push_back(processes[id]);
                            sort(queues[0].process_in_queue.begin(), queues[0].process_in_queue.end(), SRTF_cmp);
                        }
                        else if (queues[0].mode == 2)
                        {
                            if (queues[0].process_in_queue[queues[0].process_in_queue.size() - 1].queue_time == processes[id].queue_time)
                            {
                                Process temp_p = queues[0].process_in_queue[queues[0].process_in_queue.size() - 1];
                                queues[0].process_in_queue.pop_back();
                                queues[0].process_in_queue.push_back(processes[id]);
                                queues[0].process_in_queue.push_back(temp_p);
                            }
                            else
                            {
                                queues[0].process_in_queue.push_back(processes[id]);
                            }
                        }
                        else
                        {
                            queues[0].process_in_queue.push_back(processes[id]);
                        }
                    }
                }
                else
                {
                    if (N == 1)
                    {
                        queues[0].process_in_queue.push_back(processes[id]);
                        if (queues[0].mode == 1)
                        {
                            if (queues[0].process_in_queue[0].remain_time > processes[id].remain_time)
                            {
                                processes[current_process].queue_time = global_time;
                                queues[0].process_in_queue[0].queue_time = global_time;
                                current_process = id;
                            }
                            sort(queues[0].process_in_queue.begin(), queues[0].process_in_queue.end(), SRTF_cmp);
                        }
                    }
                    else
                    {
                        queues[0].process_in_queue.push_back(processes[id]);
                        if (queues[0].mode == 1)
                        {
                            if (queues[0].process_in_queue[0].remain_time > processes[id].remain_time)
                            {
                                processes[current_process].queue_time = global_time;
                                Process temp_p = vector_pop_front(queues[0].process_in_queue);
                                temp_p.queue_time = global_time;
                                current_process = id;
                                queues[1].process_in_queue.push_back(temp_p);
                                if (queues[1].mode == 1) sort(queues[1].process_in_queue.begin(), queues[1].process_in_queue.end(), SRTF_cmp);
                            }
                            sort(queues[0].process_in_queue.begin(), queues[0].process_in_queue.end(), SRTF_cmp);
                        }
                    }
                }
            }
            id++;
        }
        
        /* do process */
        if (queues[queue_now_processing].process_in_queue.empty())
        {
            global_time++;
            continue;
        }
        is_complete = false;
        queues[queue_now_processing].process_in_queue[0].remain_time--;
        processes[current_process].remain_time--;
        if (queues[queue_now_processing].process_in_queue[0].remain_time == 0)
        {
            done.push_back(current_process);
            queues[queue_now_processing].time_quantum_left = queues[queue_now_processing].time_quantum;
            is_complete = true;
            processes[current_process].complete_time = global_time + 1;
            Process temp_p = vector_pop_front(queues[queue_now_processing].process_in_queue);
            for (int i = queue_now_processing; i < N; i++)
            {
                if (!queues[i].process_in_queue.empty())
                {
                    current_process = queues[i].process_in_queue[0].idx;
                    queue_now_processing = i;
                    break;
                }
                if (i == N - 1) queue_now_processing = 0;
            }
        }
        else
        {
            if (queues[queue_now_processing].mode == 2)
            {
                queues[queue_now_processing].time_quantum_left--;
                if (queues[queue_now_processing].time_quantum_left == 0)
                {
                    is_complete = true;
                    queues[queue_now_processing].time_quantum_left = queues[queue_now_processing].time_quantum;
                    Process temp_p = vector_pop_front(queues[queue_now_processing].process_in_queue);
                    temp_p.queue_time = global_time + 1;
                    processes[current_process].queue_time = global_time + 1;
                    if (queue_now_processing < N - 1)
                    {
                        queues[queue_now_processing + 1].process_in_queue.push_back(temp_p);
                        if (queues[queue_now_processing + 1].mode == 1)
                        {
                            sort(queues[queue_now_processing + 1].process_in_queue.begin(), queues[queue_now_processing + 1].process_in_queue.end(), SRTF_cmp);
                        }
                        for (int i = queue_now_processing; i < N; i++)
                        {
                            if (!queues[i].process_in_queue.empty())
                            {
                                current_process = queues[i].process_in_queue[0].idx;
                                queue_now_processing = i;
                                break;
                            }
                            if (i == N - 1) queue_now_processing = 0;
                        }
                    }
                    else
                    {
                        queues[queue_now_processing].process_in_queue.push_back(temp_p);
                        current_process = queues[queue_now_processing].process_in_queue[0].idx;
                    }
                }
            }
        }
        
        /* end condition */
        if (done.size() == M) end = true;
        global_time++;
    }

    for (int i = 0; i < M; i++)
    {
        processes[i].turn_around_time = processes[i].complete_time - processes[i].arrival_time;
        total_turn_around_time += processes[i].turn_around_time;
        processes[i].wait_time = processes[i].turn_around_time - processes[i].burst_time;
        total_wait_time += processes[i].wait_time;
        cout << processes[i].wait_time << " " << processes[i].turn_around_time << "\n";
    }
    cout << total_wait_time << "\n";
    cout << total_turn_around_time << "\n";
}

