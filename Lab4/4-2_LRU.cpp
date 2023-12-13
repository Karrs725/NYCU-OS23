#include<iostream>
#include<vector>

using namespace std;

int main(){
    int cache_num, K, set_num, stream_size, data, total_misses = 0;
    bool is_hit;
    vector<int> set;
    vector<vector<int>> cache;
    cin >> cache_num >> K >> stream_size;
    set_num = cache_num / K;
    for (int i = 0; i < K; i++) set.push_back(-1);
    for (int i = 0; i < set_num; i++) cache.push_back(set);
    for (int i = 0; i < stream_size; i++)
    {
        is_hit = false;
        cin >> data;
        for (int j = 0; j < set_num; j++)
        {
            for (int k = 0; k < K; k++)
            {
                if (data == cache[j][k])
                {
                    is_hit = true;
                    cache[j].push_back(data);
                    cache[j].erase(cache[j].begin() + k);
                    break;
                }
            }
            if (is_hit) break;
        }
        if (!is_hit)
        {
            cache[i % set_num].push_back(data);
            cache[i % set_num].erase(cache[i % set_num].begin());
            total_misses++;
        }
    }
    cout << "Total Cache Misses:" << total_misses;
}