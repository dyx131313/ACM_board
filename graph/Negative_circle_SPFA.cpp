//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class Negative_circle{
private:
    class Chain_forward{
    public:
        struct edge{
            int to, nex;
            ll weight;
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
            e.resize(2 * m + bias);
        }
        void add_edge(int a, int b, ll c){
            e[++cnt].to = b;
            e[cnt].nex = head[a];
            e[cnt].weight = c;
            head[a] = cnt;
        }
    };
    queue<int> que;
    vector<int> vis, dis, in_q;
    Chain_forward G;
    int n, m, cnt = 1;
public:
    void init(int cur_n, int cur_m){
        n = cur_n;
        m = cur_m;
        vis.resize(n + bias);
        fill(vis.begin(), vis.end(), 0);
        dis.resize(n + bias);
        fill(dis.begin(), dis.end(), 0x3f3f3f3f);
        in_q.resize(n + bias);
        fill(in_q.begin(), in_q.end(), 0);
        G.init(n, m);
        que = queue<int>();
        dis[1] = 0;
        que.push(1);
        in_q[1] = 1;
        vis[1] = 1;
    }
    void add_edge(int a, int b, ll c){
        G.add_edge(a, b, c);
    }
    bool SPFA(){
        while(!que.empty()){
            int u = que.front();
            que.pop();
            in_q[u] = 0;
            for(int i = G.head[u]; i; i = G.e[i].nex){
                int v = G.e[i].to;
                if(dis[v] > dis[u] + G.e[i].weight){
                    dis[v] = dis[u] + G.e[i].weight;
                    if(!in_q[v]){
                        vis[v]++;
                        if(vis[v] >= n){
                            return true;
                            return;
                        }
                        in_q[v] = 1;
                        que.push(v);
                    }
                }
            }
        }
        return 0;
    }
};