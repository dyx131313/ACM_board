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

const int n_size=1e5+5;

int n,m; 

int rt[n_size],dis[n_size],val[n_size],tf[n_size],l[n_size],r[n_size];

int find(int x){
	if(rt[x]==x) return x;
	return rt[x]=find(rt[x]);
}

int merge(int x,int y){
	if(!x||!y) return x+y;
	if(val[x]==val[y]?x>y:val[x]>val[y]) swap(x,y);
	r[x]=merge(y,r[x]);
	rt[l[x]]=rt[r[x]]=x;
	if(dis[l[x]]<dis[r[x]]) swap(l[x],r[x]);
	dis[x]=dis[r[x]]+1;
	return x;
}

int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&val[i]);
		rt[i]=i;
	}
	for(int i=1,op,x,y;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&x,&y);
			if(tf[x]||tf[y]) continue;
			int a=find(x),b=find(y);
			if(a!=b){
				rt[a]=rt[b]=merge(a,b);
			}
		}else{
			scanf("%d",&x);
			int k=find(x);
			if(tf[x]){
				printf("-1\n");
				continue;
			}
			printf("%d\n",val[k]);
			tf[k]=1;
			rt[l[k]]=rt[r[k]]=merge(l[k],r[k]);
			rt[k]=rt[l[k]];
			l[k]=r[k]=dis[k]=0;
		}
	}
	return 0;
}
