//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class Heap{
private:
    int n;
    vector<int> heap;
    int cnt;
public:
    void init(int cur_n){
        n = cur_n;
        heap.resize(n + bias);
        cnt = 0;
    }
    void up(int k){
        if(k == 1) return;
        if(heap[k] < heap[k / 2]){
            swap(heap[k], heap[k / 2]);
            up(k / 2);
        }
        return;
    }
    void down(int k){
        if(2 * k > cnt) return;
        int num;
        if(2 * k + 1 <= cnt) num = heap[2 * k] > heap[2 * k + 1] ? 2 * k + 1 : 2 * k;
        else num = 2 * k;
        if(heap[k] > heap[num]){
            swap(heap[k], heap[num]);
            down(num);
        }
    }
};