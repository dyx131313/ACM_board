//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5, inf = 2e9;

class Dinic{
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
    vector<int> inq, vis, cur, dis;
    Chain_forward G;
    int n, m, S, T, cnt = 1;
    int ans = 0;
public:
    void init(int cur_n, int cur_m, int cur_S, int cur_T){
        n = cur_n;
        m = cur_m;
        S = cur_S;
        T = cur_T;
        inq.resize(n + bias);
        vis.resize(n + bias);
        cur.resize(n + bias);
        dis.resize(n + bias);
        G.init(n, m);
    }
    void add_edge(int a, int b, ll c){
        G.add_edge(a, b, c);
        G.add_edge(b, a, 0ll);
    }
    bool rebuild_divide_graph(){
        for(int i = 1; i <= n; i++) dis[i] = inf;
        dis[S] = 0;
        cur[S] = G.head[S];
        while(!que.empty()) que.pop();
        que.push(S);
        while(!que.empty()){
            int curr = que.front();
            que.pop();
            for(int i = G.head[curr], v; i; i = G.e[i].nex){
                v = G.e[i].to;
                if(G.e[i].weight && dis[v] == inf){
                    que.push(v);
                    cur[v] = G.head[v];
                    dis[v] = dis[curr] + 1;
                }
            }
            if(dis[T] != inf) return true;
        }
        return dis[T] != inf;
    }
    ll dfs(int curr, ll sum){
        if(curr == T) return sum;
        ll ret = 0, k = 0;
        for(int i = cur[curr], v; i && sum > ret; i = G.e[i].nex){
            cur[curr] = i;
            v = G.e[i].to;
            if(G.e[i].weight && dis[v] == dis[curr] + 1){
                k = dfs(v, min(G.e[i].weight, sum - ret));
                if(k) ret += k, G.e[i].weight -= k, G.e[i ^ 1].weight += k;
            }
        }
        return ret;
    }
    ll maxflow(){
        ll ret = 0;
        while(rebuild_divide_graph()) ret += dfs(S, inf);
        return ret;
    }
};