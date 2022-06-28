#include <bits/stdc++.h>
using namespace std;
const int md = 1e9 + 7;
int main() {
    ios ::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream fin("problem4.in");
    ofstream fout("problem4.out");
    string s;
 
    int n, m, k, l;
    fin >> n >> m >> k >> l;
    vector<bool> dop(n);
    vector<map<long long, long long>> sp(n);
    int x, y;
    char c;
    for (int i = 0; i < k; ++i) {
        fin >> x;
        dop[x - 1] = true;
    }
    for (int i = 0; i < m; ++i) {
        fin >> x >> y >> c;
        ++sp[x - 1][y - 1];
    }
    map<long long, long long> now;
    now[0] = 1;
    for (int i = 0; i < l; ++i) {
        map<long long, long long> next;
        for (auto &v: now)
            for (auto &u: sp[v.first])
                next[u.first] = (next[u.first] + v.second * sp[v.first][u.first]) % md;
        now.clear();
        now = next;
    }
    fin.close();
    long long res = 0;
    for (auto &v: now)
        if (dop[v.first])
            res = (res + v.second) % md;
    fout << res;
    fout.close();
    return 0;
}