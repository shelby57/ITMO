#include <bits/stdc++.h>
using namespace std;
const long long MMAX = 2e18;
struct segtree {
    struct node {
        long long int mn;
        long long int plus;
        long long assignment;
    };
    vector<node> tree;
    int size;
    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;
        tree.assign(2 * size - 1, {MMAX, 0, MMAX});
    }
    void propagate(int x, int delta) {
        if (delta < 2)
            return;
        if(tree[x].assignment != MMAX) {
            tree[2 * x + 1].mn = tree[x].assignment + tree[x].plus;
            tree[2 * x + 1].assignment = tree[x].assignment;
            tree[2 * x + 1].plus = tree[x].plus;
            tree[2 * x + 2].mn = tree[x].assignment + tree[x].plus;
            tree[2 * x + 2].assignment = tree[x].assignment;
            tree[2 * x + 2].plus = tree[x].plus;
            tree[x].assignment = MMAX;
            tree[x].plus = 0;
            return;
        }
        tree[2 * x + 1].mn += tree[x].plus;
        tree[2 * x + 1].plus += tree[x].plus;
        tree[2 * x + 2].mn += tree[x].plus;
        tree[2 * x + 2].plus += tree[x].plus;
        tree[x].plus = 0;
    }
    node f(node x, node y) {
        return {min(x.mn, y.mn), 0, MMAX};
    }
    void set(int l, int r, long long v) {
        set(l, r, v, 0, 0, size);
    }
    void set(int l, int r, long long int v, int x, int lx, int rx) {
        propagate(x, rx - lx);
        if (rx <= l || r <= lx)
            return;
        if (l <= lx && rx <= r) {
            tree[x] = {v, 0, v};
            return;
        }
        int m = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, m);
        set(l, r, v, 2 * x + 2, m, rx);
        tree[x] = f(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int l, int r, long long int v) {
        add(l, r, 0, 0, size, v);
    }
    void add(int l, int r, int x, int lx, int rx, long long int v) {
        propagate(x, rx - lx);
        if (rx <= l || r <= lx)
            return;
        if (l <= lx && rx <= r) {
            tree[x].mn += v;
            tree[x].plus += v;
            return;
        }
        int m = (lx + rx) / 2;
        add(l, r, 2 * x + 1, lx, m, v);
        add(l, r, 2 * x + 2, m, rx, v);
        tree[x] = f(tree[2 * x + 1], tree[2 * x + 2]);
    }
    long long int mn(int l, int r) {
        return mn(l, r, 0, 0, size);
    }
    long long int mn(int l, int r, int x, int lx, int rx) {
        propagate(x, rx - lx);
        if (rx <= l || r <= lx)
            return MMAX;
        if (l <= lx && rx <= r) {
            return tree[x].mn;
        }
        int m = (lx + rx) / 2;
        long long int res1 = mn(l, r, 2 * x + 1, lx, m);
        long long int res2 = mn(l, r, 2 * x + 2, m, rx);
        return min(res1, res2);
    }
};
int main() {
    ios ::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    segtree st;
    st.init(n);
    long long x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        st.set(i, i + 1, x);
    }
    string s;
    int l, r;
    long long v;
    while (cin >> s >> l >> r) {
        --l;
        if (s == "set") {
            cin >> v;
            st.set(l, r, v);
        } else if (s == "add") {
            cin >> v;
            st.add(l, r, v);
        } else {
            cout << st.mn(l, r) << endl;
        }
    }
    return 0;
}