#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node {
	bool left;
	bool right;
	int cnt_0;
	int cnt_1;
	int len_0;
	int len_1;
	bool update;
	bool bit;
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
	void build(int x,int lx,int rx) {
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
		result.left = x.left;
		result.right = y.right;
		result.cnt_1 = x.cnt_1 + y.cnt_1;
		result.cnt_0 = x.cnt_0 + y.cnt_0;
		result.update = 0;
		result.bit = 0;
		result.len_0 = x.len_0 + y.len_0;
		result.len_1 = x.len_1 + y.len_1;
		if(x.right == y.left && x.right == 1) {
			--result.cnt_1;
		}
		if(x.right == y.left && x.right == 0) {
			--result.cnt_0;
		}
		return result;
	}
	void propagate(int x) {
		if(!tree[x].update)
			return;
		tree[x].update = 0;
		tree[2 * x + 1] = {tree[x].bit, tree[x].bit, -1, -1, -1, -1, 1, tree[x].bit};
		tree[2 * x + 2] = {tree[x].bit, tree[x].bit, -1, -1, -1, -1, 1, tree[x].bit};
		if(tree[x].bit == 0) {
			tree[2 * x + 1].cnt_0 = 1;
			tree[2 * x + 2].cnt_0 = 1;
			tree[2 * x + 1].cnt_1 = 0;
			tree[2 * x + 2].cnt_1 = 0;
			tree[2 * x + 1].len_0 = tree[x].len_0 / 2;
			tree[2 * x + 1].len_1 = 0;
			tree[2 * x + 2].len_0 = tree[x].len_0 / 2;
			tree[2 * x + 2].len_1 = 0;
		} else {
			tree[2 * x + 1].cnt_0 = 0;
			tree[2 * x + 2].cnt_0 = 0;
			tree[2 * x + 1].cnt_1 = 1;
			tree[2 * x + 2].cnt_1 = 1;
			tree[2 * x + 1].len_1 = tree[x].len_1 / 2;
			tree[2 * x + 1].len_0 = 0;
			tree[2 * x + 2].len_1 = tree[x].len_1 / 2;
			tree[2 * x + 2].len_0 = 0;
		}
	}

	void set(int l,int r, bool color) {
		set(l, r, color, 0, 0, size);
	}
	void set(int l,int r, bool color, int x, int lx,int rx) {

		if(rx <= l || r <= lx)
			return;
		if(rx - lx > 1)
			propagate(x);
		if(l <= lx && rx <= r) {
			tree[x] = {color, color, -1, -1, -1, -1, 1, color};
			if(color == 0) {
				tree[x].cnt_0 = 1;
				tree[x].cnt_1 = 0;
				tree[x].len_0 = rx - lx;
				tree[x].len_1 = 0;
			} else {
				tree[x].cnt_0 = 0;
				tree[x].cnt_1 = 1;
				tree[x].len_0 = 0;
				tree[x].len_1 = rx - lx;
			}
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
	ios :: sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	segtree st;
	st.init(SIZE);
	st.build();
	int x,l;
	string s;
	while(n--) {
		cin >> s >> x >> l;
		x += 500000;
		if(s == "B") {
			st.set(x, x + l, 1);
			cout << st.get_cnt() << " " << st.get_len() << endl;
		} else {
			st.set(x, x + l, 0);
			cout << st.get_cnt() << " " << st.get_len() << endl;
		}
	}
	return 0;
}
