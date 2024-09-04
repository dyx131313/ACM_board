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
            int to, nex, weight, cost;
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
        void add_edge(int a, int b, int c, int d){
            e[++cnt].to = b;
            e[cnt].nex = head[a];
            e[cnt].weight = c;
            e[cnt].cost = d;
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
    void add_edge(int a, int b, int c, int d){
        G.add_edge(a, b, c, d);
        G.add_edge(b, a, 0, -d);
    }
    bool rebuild_SPFA(){
        for(int i = 1; i <= n; i++) dis[i] = inf;
        for(int i = 1; i <= n; i++) cur[i] = G.head[i];
        dis[S] = 0;
        que.push(S);
        while(!que.empty()){
            int curr = que.front();
            que.pop();
            vis[curr] = 0;
            for(int i = G.head[curr], v; i; i = G.e[i].nex){
                v = G.e[i].to;
                if(G.e[i].cost && dis[v] > dis[curr] + G.e[i].weight){
                    dis[v] = dis[curr] + G.e[i].weight;
                    if(!vis[v]) vis[v] = 1, que.push(v);
                }
            }
        }
        return dis[T] != inf;
    }
    int dfs(int curr, int sum){
        if(curr == T) return sum;
        int ret = 0;
        for(int i = cur[curr], v; i; i = G.e[i].nex){
            v = G.e[i].to;
            cur[curr] = i;
            if(G.e[i].cost && dis[v] == dis[curr] + G.e[i].weight){
                int k = dfs(v, min(G.e[i].cost, sum - ret));
                if(k) ans += k * G.e[i].weight, ret += k, G.e[i].cost -= k, G.e[i ^ 1].cost += k;
            }
        }
        return ret;
    }
    pa costflow(){
        int ret = 0;
        while(rebuild_SPFA()) ret += dfs(S, inf);
        return make_pair(ret, ans);
    }
};