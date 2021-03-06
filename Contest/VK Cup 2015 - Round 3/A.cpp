#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
typedef long long LL;
int n,m;
struct se{
	int l,r,c,id;
	int len(){return r-l;}
	bool operator==(se o)const{return l==o.l&&r==o.r;}
	bool operator!=(se o)const{return !(*this==o);}
}a[maxn],b[maxn];
se operator&(se A,se B){
	if(A.l>B.l)swap(A,B);
	return (se){max(B.l,A.l),min(A.r,B.r),0,0};
}
bool cmp1(se A,se B){
	return A.l!=B.l?A.l<B.l:A.r>B.r;
}
bool cmp2(se A,se B){
	return A.l!=B.l?A.l<B.l:A.r<B.r;
}
LL ans;
int ax,ay;
void solve(int l,int r,int lef,int rig){
	int mid=(l+r)>>1;
	int ps=lef;LL res=0;
	for(int i=lef;i<=rig;i++){
		LL tmp=(LL)(a[mid]&b[i]).len()*b[i].c;
		if(tmp>res)res=tmp,ps=i;
		if(tmp>ans)ans=res,ax=a[mid].id,ay=b[i].id;
	}
	if(l<mid)
	solve(l,mid-1,lef,ps);
	if(mid<r)
	solve(mid+1,r,ps,rig);
}
int BF(){
	LL ans=0,x,y;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		LL res=(LL)(a[i]&b[j]).len()*b[j].c;
		if(res>ans)ans=res,x=i,y=j;
	}
	cout<<ans<<endl;
	if(ans)cout<<x<<" "<<y<<endl;	
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i].l,&a[i].r),a[i].id=i;
	for(int i=1;i<=m;i++)scanf("%d%d%d",&b[i].l,&b[i].r,&b[i].c),b[i].id=i;
	
	if((LL)n*m<=1e7)return BF();
	
	sort(a+1,a+1+n,cmp1);
	int top=1;
	for(int i=2;i<=n;i++){
		if((a[top]&a[i])!=a[i]&&a[i].len())
			a[++top]=a[i];
	}n=top;
	sort(b+1,b+1+m,cmp2);
	solve(1,n,1,m);
	cout<<ans<<endl;
	if(ans)cout<<ax<<" "<<ay<<endl;
	return 0;
}
