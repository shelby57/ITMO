#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ifstream fin("equivalence.in");
    ofstream fout("equivalence.out");
    int n, m, k;
    fin >> n >> m >> k;
    vector<vector<int>> sp1(n + 1);
    for (int i = 0; i <= n; ++i)
        sp1[i].assign(26, n);
    vector<bool> dop1(n), mark1(n);
    int x, y;
    char c;
    for (int i = 0; i < k; ++i) {
        fin >> x;
        dop1[x - 1] = true;
    }
    for (int i = 0; i < m; ++i) {
        fin >> x >> y >> c;
        sp1[x - 1][c - 'a'] = y - 1;
    }
    fin >> n >> m >> k;
    vector<vector<int>> sp2(n + 1);
    for (int i = 0; i <= n; ++i)
        sp2[i].assign(26, n);
 
    vector<bool> dop2(n);
    for (int i = 0; i < k; ++i) {
        fin >> x;
        dop2[x - 1] = true;
    }
    for (int i = 0; i < m; ++i) {
        fin >> x >> y >> c;
        sp2[x - 1][c - 'a'] = y - 1;
    }
    vector<pair<int, int>> queue;
    queue.emplace_back(0, 0);
    int pos = 0;
    vector<bool> mark2(n);
    set<pair<int, int>> base;
    while (pos < queue.size()) {
        int u = queue[pos].first;
        int v = queue[pos].second;
        if (dop1[u] != dop2[v]) {
            fout << "NO";
            return 0;
        }
        base.insert(queue[pos]);
        for (int i = 0; i < 26; ++i) {
            pair<int, int> p = {sp1[u][i], sp2[v][i]};
            if (base.find(p) == base.end()) {
                queue.emplace_back(p);
            }
        }
        ++pos;
    }
    fout << "YES";
    fin.close();
    fout.close();
    return 0;
}
