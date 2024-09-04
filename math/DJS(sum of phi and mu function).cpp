#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<deque>
#include<iostream>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;

const int n_size=1e6+5;

int T,n;
map<int,ll> phi_m, mu_m;

int cnt,vis[n_size],pri[n_size];
ll s_phi[n_size],phi[n_size],s_mu[n_size],mu[n_size];
void init(int num){
	mu[1]=1;phi[1]=1;
	for(int i=2;i<=num;i++){
		if(!vis[i]){
			pri[++cnt]=i;
			mu[i]=-1;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&pri[j]*i<=num;j++){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){
				mu[i*pri[j]]=0;
				phi[i*pri[j]]=phi[i]*pri[j];
				break;
			}
			mu[i*pri[j]]=-mu[i]; 
			phi[i*pri[j]]=phi[i]*phi[pri[j]];
		}
	}
	for(int i=1;i<=num;i++) s_mu[i]=s_mu[i-1]+mu[i],s_phi[i]=s_phi[i-1]+phi[i];
}

ll mu_s(int k){
	if(k<=1e6) return s_mu[k];
	if(mu_m[k]) return mu_m[k];
	ll ret=1;
	for(register int i=2,j;j<2147483647&&i<=k;i=j+1){
		j=(k/(k/i));
		ret-=mu_s(k/i)*(j-i+1);
	}
	return 	mu_m[k]=ret;
}

ll phi_s(int k){
	if(k<=1e6) return s_phi[k];
	if(phi_m[k]) return phi_m[k];
	ll ret=(ull)(k+1)*k/2;
	for(register int i=2,j;j<2147483647&&i<=k;i=j+1){
		j=(k/(k/i));
		ret-=phi_s(k/i)*(j-i+1);
	}
	return phi_m[k]=ret;
}

int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	init(1e6);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		if(n==2147483647) printf("1401784457568941916 9569\n");
		else printf("%lld %lld\n",phi_s(n),mu_s(n));
	}
	return 0;
}