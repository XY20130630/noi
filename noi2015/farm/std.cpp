#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

const int N=50010,oo=0x3f3f3f3f,M=600005;
int n,s,t,S,T,e=1,a1,n1[N],n2[N],n3[N],f[N],g[N],p1[N],p2[N],F[N],G[N],d[N],to[M],nx[M],c[M],hd[N],ch[N],cr[N],x1[N],x2[N],x3[N],x4[N];
map<int,int> m1,m2,m3;
struct nd {
	int x,y,id;
	bool operator < (const nd &k) const {return y==k.y?x>k.x:y>k.y;}
}a[N];
void ad(int x,int y,int z) {to[++e]=y,c[e]=z,nx[e]=hd[x],hd[x]=e,to[++e]=x,c[e]=0,nx[e]=hd[y],hd[y]=e;}

void dfs(int x,int k) {
	if(!x) return;
	if(k) printf("%d ",a[x].id),dfs(p2[x],0);
	else {
		if(p1[x]<x) {
			for(int i=x;a[i].y==a[x].y;i++) printf("%d ",a[i].id);
			for(int i=x-1;i>p1[x];i--) printf("%d ",a[i].id);
		} else if(p1[x]>x) {
			for(int i=x;a[i].y==a[x].y;i--) printf("%d ",a[i].id);
			for(int i=x+1;i<p1[x];i++) printf("%d ",a[i].id);
		}
		dfs(p1[x],1);
	}
}
void sol(int *f,int *g,int l) {
	for(int i=1;i<=n;i++) n1[i]=m1[a[i].x-a[i].y],n2[i]=m2[a[i].x],n3[i]=m3[a[i].x+a[i].y],m1[a[i].x-a[i].y]=m2[a[i].x]=m3[a[i].x+a[i].y]=i;
	for(int i=1+l,j;i<=n;i=j) {
		int r=i-1;
		for(j=i;a[j].y==a[i].y;j++) {
			r++,g[j]=x1[j]=max(f[n1[j]],max(f[n2[j]],f[n3[j]]))+1,x3[j]=j;
			if(f[n1[j]]>f[n2[j]]&&f[n1[j]]>f[n3[j]]) p2[j]=n1[j];
			else if(f[n2[j]]>f[n3[j]]) p2[j]=n2[j];
			else p2[j]=n3[j];
			if(j>i) {x1[j]=max(x1[j-1],x1[j]); if(g[x3[j-1]]-x3[j-1]>g[x3[j]]-x3[j]) x3[j]=x3[j-1];}
		}
		for(j=r;j>=i;j--) {x2[j]=g[j],x4[j]=j; if(j<r) {x2[j]=max(x2[j],x2[j+1]); if(g[x4[j+1]]+x4[j+1]>g[x4[j]]+x4[j]) x4[j]=x4[j+1];}}
		for(j=i;a[j].y==a[i].y;j++) {
			if(f[j]<g[j]) f[j]=g[j],p1[j]=j;
			if(j<r) {
				if(l) f[j]=max(f[j],x2[j+1]+r-j);
				else if(f[j]<g[x4[j+1]]+x4[j+1]-i) f[j]=g[x4[j+1]]+x4[j+1]-i,p1[j]=x4[j+1];
			}
			if(j>i) {
				if(l) f[j]=max(f[j],x1[j-1]+j-i);
				else if(f[j]<g[x3[j-1]]-x3[j-1]+r) f[j]=g[x3[j-1]]-x3[j-1]+r,p1[j]=x3[j-1];
			}
		}
	}
}
bool tel(int s,int t) {
	queue<int> q; q.push(s),memset(ch,0,sizeof ch),ch[s]=1;
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(int i=hd[u];i;i=nx[i]) if(!ch[to[i]]&&c[i]) ch[to[i]]=ch[u]+1,q.push(to[i]);
	}
	return ch[t];
}
int zng(int a,int b,int t) {
	if(a==t) return b;
	int r=0;
	for(int i=cr[a];i&&b>r;i=nx[i]) if(ch[to[i]]==ch[a]+1&&c[i]) {
		int k=zng(to[i],min(b-r,c[i]),t);
		c[i]-=k,c[i^1]+=k,r+=k;
		if(c[i]>0) cr[a]=i;
	}
	if(!r) ch[a]=0;
	return r;
}

int main() {
	scanf("%d",&n),a[++n]=(nd){0,0,0},a[n+1].y=2333,t=n+1,S=n+2,T=n+3,ad(t,s,oo);
	for(int i=1;i<n;i++) scanf("%d%d",&a[i].x,&a[i].y),a[i].id=i;
	sort(a+1,a+1+n),sol(f,g,0),printf("%d\n",g[n]-1),dfs(p2[n],0);
	for(int i=1;i<=n/2;i++) swap(a[i],a[n-i+1]);
	m1.clear(),m2.clear(),m3.clear(),memset(F,0xcf,sizeof F),memset(G,0xcf,sizeof G),F[1]=G[1]=1,sol(F,G,1);
	for(int i=1;i<=n;i++) ad(s,i,oo),ad(i,t,oo);
	for(int i=1;i<=n;i++) {
		if(n1[i]&&F[n1[i]]+f[n-i+1]==g[n]) d[n1[i]]--,d[i]++,ad(n1[i],i,oo);
		if(n2[i]&&F[n2[i]]+f[n-i+1]==g[n]) d[n2[i]]--,d[i]++,ad(n2[i],i,oo);
		if(n3[i]&&F[n3[i]]+f[n-i+1]==g[n]) d[n3[i]]--,d[i]++,ad(n3[i],i,oo);
	}
	for(int i=1;i<=n;i++)
	if(d[i]<0) ad(i,T,-d[i]);
	else if(d[i]>0) ad(S,i,d[i]);
	while(tel(S,T)) {memcpy(cr,hd,sizeof hd); for(int r;r=zng(S,oo,T););}
	a1=c[3],c[2]=c[3]=0;
	while(tel(t,s)) {memcpy(cr,hd,sizeof hd); for(int r;r=zng(t,oo,s);a1-=r);}
	printf("\n%d",a1);
	return 0;
}
