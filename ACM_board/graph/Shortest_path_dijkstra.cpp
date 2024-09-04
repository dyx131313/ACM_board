//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class Dijkstra{
private:
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
            e.resize(2 * m + bias);
        }
        void add_edge(int a, int b, int c){
            e[++cnt].to = b;
            e[cnt].nex = head[a];
            e[cnt].weight = c;
            head[a] = cnt;
        }
    };
    priority_queue<pa> que;
    vector<int> vis, dis;
    Chain_forward G;
    int n, m, S;
public:
    void init(int cur_n, int cur_m, int cur_S){
        n = cur_n;
        m = cur_m;
        S = cur_S;
        vis.resize(n + bias);
        dis.resize(n + bias);
        for(int i = 1; i <= n; i++) dis[i] = (i == S) ? 0 : 1e9 + 7;
        G.init(n, m);
    }
    void add_edge(int a, int b, int c){
        G.add_edge(a, b, c);
    }
    void dijkstra(){
        que.push(make_pair(-dis[S], S));
        while(!que.empty()){
            pa cur = que.top(); que.pop();
            if(vis[cur.second]) continue;
            vis[cur.second] = 1;
            for(int i = G.head[cur.second], to; i; i = G.e[i].nex){
                to = G.e[i].to;
                if(!vis[to] && dis[to] > dis[cur.second] + G.e[i].weight){
                    dis[to] = dis[cur.second] + G.e[i].weight;
                    que.push(make_pair(-dis[to], to));
                }
            }
        }
    }
};