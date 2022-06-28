#include<bits/stdc++.h>
#define int long long
using namespace std;
struct segtree {
	vector <int> tree;
	int size;
	void init(int n) {
		size = 1;
		while(size < n)
			size *= 2;
		tree.assign(2*size - 1,0);
	}
	void build(vector <int> &a) {
		init(a.size());
		build(a,0,0,size);
	}
	void build(vector <int> &a,int x,int lx,int rx) {
		if(rx - lx == 1) {
			if(lx < a.size())
				tree[x] = a[lx];
			return;
		}
		int m = (lx + rx) / 2;
		build(a,2*x + 1,lx,m);
		build(a,2*x + 2,m,rx);
		tree[x] = tree[2*x + 1] + tree[2*x + 2];
	}
	void set(int i,int v) {
		set(i,v,0,0,size);
	}
	void set(int i,int v,int x,int lx,int rx) {
		if(rx - lx == 1) {
			tree[x] = v;
			return;
		}
		int m = (lx + rx) / 2;
		if(i < m)
			set(i,v,2*x + 1,lx,m);
		else
			set(i,v,2*x + 2,m,rx);
		tree[x] = tree[2*x + 1] + tree[2*x + 2];
	}
	int sum(int l,int r) {
		return sum(l,r,0,0,size);
	}
	int sum(int l,int r,int x,int lx,int rx) {
		if(rx <= l || r <= lx)
			return 0;
		if(l <= lx && rx <= r)
			return tree[x];
		int m = (lx + rx) / 2;
		int s1 = sum(l,r,2*x + 1,lx,m);
		int s2 = sum(l,r,2*x + 2,m,rx);
		return s1 + s2;
	}
};
main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin >> n;
	vector <int> a(n);
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	segtree st;
	st.build(a);
	int flag,x,y;
	string s;
	while(cin >> s >> x >> y) {
		if(s == "W")
			st.set("");
		else
			cout << st.sum(x - 1,y) << endl;
	}
	return 0;
}
