#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<deque>
#include<stack>
#include<vector>
#include<set>
#include<map>
#include<iostream>
using namespace std;
typedef long long int ll;
typedef double db;
typedef string str;
typedef pair<int,int> pa;
typedef vector<int> vec;
const int n_size=1e4+5;

int n,m,que[n_size],ans[n_size];
int nex[2*n_size],to[2*n_size],head[n_size],w[2*n_size],cnt;
void add(int u,int v,int t){
	to[++cnt]=v;
	w[cnt]=t;
	nex[cnt]=head[u];
	head[u]=cnt;
}

int siz[n_size];
int get_size(int u,int fat){
	siz[u]=1;
	for(int i=head[u],v;i;i=nex[i]){
		v=to[i];
		if(v==fat) continue;
		get_size(v,u);
		siz[u]+=siz[v];
	} 
	return siz[u];
}
int get_cen(int u,int fat,int tree_size){
	for(int i=head[u],v;i;i=nex[i]){
		v=to[i]; 
		if(v==fat) continue;
		if(siz[v]>tree_size/2) return get_cen(v,u,tree_size);
	}
	return u;
}

vec f;
set<int> s;
void dfs(int u,int fat,int dep){
	f.push_back(dep);
	for(int i=head[u],v;i;i=nex[i]){
		v=to[i];
		if(v==fat) continue;
		dfs(v,u,dep+w[i]); 
	}
}
void cdq(int u){
	int c=get_cen(u,-1,get_size(u,-1));
	//get_cen
	s.clear();s.insert(0);f.clear();
	for(int i=head[c],v;i;i=nex[i]){
		v=to[i];
		f.clear();
		dfs(v,c,w[i]);
		for(int j=0;j<(int)f.size();j++){
			for(int k=1;k<=m;k++) if(!ans[k]&&s.count(que[k]-f[j])) ans[k]=1; 
		}
		s.insert(f.begin() ,f.end());
	} 
	//divide;
	for(int i=head[c],v;i;i=nex[i]){
		v=to[i];
		//u>>v;
		if(to[head[v]]==c){
			head[v]=nex[head[v]];
		}else{
			int k=head[v];
			while(to[nex[k]]!=c) k=nex[k];
			nex[k]=nex[nex[k]];
		}
		cdq(v);
	}
}

int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&que[i]);
	}
	cdq(1);
	for(int i=1;i<=m;i++){
		if(ans[i]) printf("AYE\n");
		else printf("NAY\n");
	} 
	return 0;
}