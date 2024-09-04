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

const int n_size=5e6+5;

typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;

int n,m,s[n_size];
ll ans[n_size];

int dig[n_size];//son_cnt 
void get_pur(){
	for(int i=1;i<n;i++) scanf("%d",&s[i]);
	int p=-1;
	for(int i=1;i<n;i++) dig[s[i]]++,dig[i]++;
	for(int i=1;i<=n;i++) if(dig[i]==1&&p==-1) p=i;
	int leaf=p;
	for(int i=1;i<=n-2;i++){
		int nex=s[leaf];
		ans[i]=nex;
		if(--dig[nex]==1&&nex<p){
			leaf=nex;
		}else{
			p++;
			while(dig[p]!=1) p++;
			leaf=p;
		}
	}
	for(int i=1;i<=n-2;i++) ans[i]=ans[i-1]^((ll)i*ans[i]);
	printf("%lld",ans[n-2]);
}

void get_f(){
	for(int i=1;i<n-1;i++) scanf("%d",&s[i]);
	for(int i=1;i<n-1;i++) dig[s[i]]++;
	for(int i=1;i<n;i++) dig[i]++;
	int p=-1;
	for(int i=1;i<=n;i++) if(dig[i]==1&&p==-1) p=i;
	int leaf=p;
	for(int i=1;i<=n-2;i++){
		int nex=s[i];
		ans[leaf]=nex;
		if(--dig[nex]==1&&nex<p){
			leaf=nex;
		}else{ 
			p++;
			while(dig[p]!=1) p++;
			leaf=p;
		}
	}
	for(int i=1;i<=n-1;i++) if(ans[i]==0) ans[i]=n;
	for(int i=1;i<=n-1;i++) ans[i]=ans[i-1]^((ll)i*ans[i]);
	printf("%lld",ans[n-1]);
}

int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	if(m==1) get_pur();
	else get_f();
	return 0;
}

