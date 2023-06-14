#include<iostream>
#include <vector>
#define int long long
using namespace std;

struct SNM {
    vector<int> tree;
    vector<int> sum;
    vector<int> size;

    explicit SNM(int n) {
        sum.resize(n, 0);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            tree.push_back(i);
        }
    }

    int find(int x) {
        if (tree[x] == x) {
            return x;
        }
        return tree[x] = find(tree[x]);
    }

    void uni(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return;
        }
        if (size[x] > size[y]) {// x < y
            swap(x, y);
        }
        tree[x] = y;
        size[y] += size[x];
        sum[y] += sum[x];
    }

    void send(int x) {
        x = find(x);
        sum[x]++;
    }

    int read(int x) {
        x = find(x);
        int res = sum[x];
        sum[x] = 0;
        return res;
    }
};

int32_t main() {
    int n, m;
    cin >> n >> m;
    int zerg = 0;
    int p = 1e6 + 3;
    SNM s(n);
    for (int k = 0; k < m; k++) {
        int t, i;
        cin >> t >> i;
        i = (i + zerg) % n;
        if (t == 1) {
            s.send(i);
            zerg = (30 * zerg + 239) % p;
        } else if (t == 2) {
            int j;
            cin >> j;
            s.uni(i, j);
            j = (j + zerg) % n;
            zerg = (13 * zerg + 11) % p;
        } else {
            int q = s.read(i);
            cout << q << "------\n";
            zerg = (100500 * zerg + q) % p;
        }
    }
    return 0;
}
