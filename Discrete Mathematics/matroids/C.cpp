#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool dfs(int v, vector<bool> &mark, vector<vector<int>> &base, vector<int> &math) {
    if (mark[v]) {
        return false;
    }
    mark[v] = true;
    for (int u: base[v])
        if (math[u] == -1 || dfs(math[u], mark, base, math)) {
            math[u] = v;
            return true;
        }
    return false;
}
int main() {
    ifstream fin("matching.in");
    ofstream fout("matching.out");
    int n;
    fin >> n;
    vector<pair<int, int>> sp(n);
    for (int i = 0; i < n; i++) {
        fin >> sp[i].first;
        sp[i].second = i;
    }
    sort(sp.rbegin(), sp.rend());
    int k, v;
    vector<vector<int>> base(n);
    for (int i = 0; i < n; ++i) {
        fin >> k;
        for (int j = 0; j < k; ++j) {
            fin >> v;
            base[i].push_back(v - 1);
        }
    }
    fin.close();
    vector<bool> mark(n, false);
    vector<int> math(n, -1);

    for (int i = 0; i < n; i++) {
        fill(mark.begin(), mark.end(), false);
        dfs(sp[i].second, mark, base, math);
    }

    vector <int> result(n);
    for (int i = 0; i < n; i++)
        if (math[i] != -1)
            result[math[i]] = i + 1;

    for (int i = 0; i < n; i++) {
        fout << result[i] << " ";
    }
    fout.close();
    return 0;
}