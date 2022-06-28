#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node {
	int mn;
	int sum;
	bool update;
};
const int SIZE = 1000001;
struct segtree {
	vector <node> tree;
	int size;
	void init(int n) {
		size = 1;
		while(size < n)
			size *= 2;
		tree.resize(2*size - 1);
	}
	void build() {
		build(0, 0, size);
	}
	void build(aint x,int lx,int rx) {
		if(rx - lx == 1) {
			if(lx < SIZE)
				tree[x] = {0, 0, 1, 0, 1, 0, 0, 0};
			return;
		}
		int m = (lx + rx) / 2;
		build(2*x + 1,lx,m);
		build(2*x + 2,m,rx);
		tree[x] = f(tree[2*x + 1], tree[2*x + 2]);
	}
	node f(node x, node y) {
		node result;
		return result;
	}
	void propagate(int x) {

	}

	void set(int l,int r, bool color) {
		set(l, r, color, 0, 0, size);
	}
	void set(int l,int r, int p, int x, int lx,int rx) {

		if(rx <= l || r <= lx)
			return;
		if(rx - lx > 1)
			propagate(x);
		if(l <= lx && rx <= r) {
			tree[x] = {x, x, };
		
			return;
		}
		int m = (lx + rx) / 2;
		set(l, r, color, 2 * x + 1, lx, m);
		set(l, r, color, 2 * x + 2, m, rx);
		tree[x] = f(tree[2 * x + 1], tree[2 * x + 2]);
	}
	int get_cnt() {
		return tree[0].cnt_1;
	}
	int get_len() {
		return tree[0].len_1;
	}
};
main() {
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
		int p;
		while(cin >> s >> x >> y) {
			--x;
			if(s == "set") {
				cin >> p;
				st.set(x, y, p);
			} else if(s == "add") {
				cin >> p;
				st.add(x, y, p);
			} else {
				cout << st.min(x, y);
			}
		}
		return 0;
	}
