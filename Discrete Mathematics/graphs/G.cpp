#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void dfs(vector<set<int> > &color, vector<int> &mark, vector<vector<int>> &base, int v) {
    int clr = 1;
    while (color[v].find(clr) != color[v].end()) {
        ++clr;
    }
    color[v].insert(clr);
    mark[v] = clr;
    for (int x: base[v]) {
        color[x].insert(clr);
    }
    for (int x: base[v]) {
        if (!mark[x])
            dfs(color, mark, base, x);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> base(n);
    vector<set<int>> color(n);
    vector<int> mark(n, 0);
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        base[u - 1].push_back(v - 1);
        base[v - 1].push_back(u - 1);
    }
    dfs(color, mark, base, n / 2);
    size_t mx = base[0].size();
    for(int i = 1; i < n; ++i) {
        mx = max(mx, base[i].size());
    }
    if (mx % 2 == 0)
        ++mx;
    cout << mx << endl;
    for (int x: mark) {
        cout << x << endl;
    }
    return 0;
}