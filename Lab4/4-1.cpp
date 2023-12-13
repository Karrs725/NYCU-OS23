#include<iostream>
#include<vector>

using namespace std;

int main(){
    int cache_num, stream_size, data, total_misses = 0;
    bool is_hit;
    vector<int> cache(cache_num, -1);
    cin >> cache_num >> stream_size;
    for (int i = 0; i < stream_size; i++)
    {
        is_hit = false;
        cin >> data;
        for (int j = 0; j < cache_num; j++)
        {
            if (data == cache[j])
            {
                is_hit = true;
                break;
            }
        }
        if (!is_hit)
        {
            cache[i % cache_num] = data;
            total_misses++;
        }
    }
    cout << "Total Cache Misses:" << total_misses;
}