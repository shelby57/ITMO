#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int count(int x) {
    int res = 0;
    while (x > 0) {
        res += x % 2;
        x >>= 1;
    }
    return res;
}

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    int m, n;
    cin >> n >> m;
    int len = (1 << n);
    vector<int> base(len);
    vector<vector<int>> sp(m);
    int k;
    bool ok = true;
    for (int i = 0; i < m; ++i) {
        cin >> k;
        int res = 0;
        if (k == 0) {
            ok = false;
        }
        int x;
        for (int j = 0; j < k; ++j) {
            cin >> x;
            x--;
            sp[i].push_back(x);
            res += (1 << x);
        }
        base[res]++;
    }
    if (ok) {
        cout << "NO";
        return 0;
    }

    for (int i = 0; i < m; i++)
        for (int p = 0; p < (1 << sp[i].size()); ++p) {
            int x = 0;
            for (int j = 0; j < sp[i].size(); ++j) {
                if (p & (1 << j)) {
                    x += (1 << sp[i][j]);
                }
            }
            if (!base[x]) {
                cout << "NO";
                return 0;
            }
        }

    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j)
            if (base[i] && base[j] && count(i) < count(j)) {
                int x = i;
                int y = j;
                for (int p = 0; p < n; ++p) {
                    if ((x & (1 << p)) && (y & (1 << p))) {
                        y ^= (1 << p);
                    }
                }

                vector<int> s;

                for (int p = 0; p < n; ++p) {
                    if (y & (1 << p)) {
                        s.push_back((1 << p));
                    }
                }
                ok = false;
                for (int p: s) {
                    if (base[x + p]) {
                        ok = true;
                    }
                }

                if (!ok) {
                    cout << "NO";
                    return 0;
                }

            }
    }
    cout << "YES";
    return 0;
}