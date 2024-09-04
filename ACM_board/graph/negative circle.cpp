#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<deque>
#include<iostream>
using namespace std;

typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;

const int n_size=2e3+5,m_size=3e3+5,INF=2e9;

int T; 

int n,m;

int cnt,head[n_size],to[2*m_size],nex[2*m_size],w[2*m_size];
void add(int a,int b,int c){
	to[++cnt]=b;
	nex[cnt]=head[a];
	head[a]=cnt;
	w[cnt]=c;
} 

int dis[n_size],in_q[n_size],vis[n_size];
queue<int> que;
void SPFA(){
	while(!que.empty()){
		int u=que.front();que.pop();in_q[u]=0;
		for(int i=head[u],v;i;i=nex[i]){
			v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				if(!in_q[v]){
					vis[v]++;
					if(vis[v]>=n){
						printf("YES\n");
						return;
					}
					in_q[v]=1;
					que.push(v);
				}
			}
		}
	}
	printf("NO\n");
}

void init(){
	for(int i=1;i<=n;i++){
		vis[i]=0,head[i]=0,in_q[i]=0;
		dis[i]=INF;
	}
	cnt=0;
	while(!que.empty()) que.pop();
	dis[1]=0;que.push(1);in_q[1]=1;vis[1]=1;
}

int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		init();
		for(int i=1,t,u,v;i<=m;i++){
			scanf("%d%d%d",&u,&v,&t);
			if(t>=0) add(u,v,t),add(v,u,t);
			else add(u,v,t);
		}
		SPFA();
	}
	return 0;
}
