//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class Chain_forward{
public:
    struct edge{
        int to, nex, weight;
    };
    vector<edge> e;
    vector<int> head;
    int n, m, cnt;
    void init(int cur_n, int cur_m){
        n = cur_n;
        m = cur_m;
        cnt = 0;
        head.resize(n + bias);
        fill(head.begin(), head.end(), 0);
        e.resize(m + bias);
    }
    void add_edge(int a, int b, int c){
        e[++cnt].to = b;
        e[cnt].nex = head[a];
        e[cnt].weight = c;
        head[a] = cnt;
    }
};

class Adjacency_table{
public:
    struct edge{
        int to, weight;
    };
    vector<vector<edge> > e;
    int n, m;
    void init(int cur_n, int cur_m){
        n = cur_n;
        m = cur_m;
        e.clear();
        e.resize(n + bias);
    }
    void add_edge(int a, int b, int c){
        e[a].push_back((edge){b, c});
    }
};