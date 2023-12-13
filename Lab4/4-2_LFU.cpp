#include<iostream>
#include<vector>
#include<utility>

using namespace std;

int main(){
    int cache_num, K, set_num, stream_size, data, total_misses = 0, swap_pos, min_val;
    bool is_hit;
    vector<pair<int, int>> set;
    vector<vector<pair<int, int>>> cache;
    cin >> cache_num >> K >> stream_size;
    set_num = cache_num / K;
    for (int i = 0; i < K; i++) set.push_back(make_pair(-1, -1));
    for (int i = 0; i < set_num; i++) cache.push_back(set);
    for (int i = 0; i < stream_size; i++)
    {
        is_hit = false;
        cin >> data;
        for (int j = 0; j < set_num; j++)
        {
            for (int k = 0; k < K; k++)
            {
                if (data == cache[j][k].first)
                {
                    is_hit = true;
                    cache[j][k].second++;
                    break;
                }
            }
            if (is_hit) break;
        }
        if (!is_hit)
        {
            swap_pos = -1;
            min_val = 99999999;
            for (int j = 0; j < K; j++)
            {
                if (cache[i % set_num][j].second < min_val) {
                    min_val = cache[i % set_num][j].second;
                    swap_pos = j;
                }
            }
            cache[i % set_num][swap_pos].first = data;
            cache[i % set_num][swap_pos].second = 1;
            total_misses++;
        }
    }
    cout << "Total Cache Misses:" << total_misses;
}