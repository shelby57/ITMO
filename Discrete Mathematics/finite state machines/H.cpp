#include <bits/stdc++.h>
using namespace std;
 
void dfs2(vector<map<char, vector<int>>> &base_reverse, int v, vector<bool> &mark) {
    mark[v] = 1;
    for (auto &x: base_reverse[v])
        for (auto &y: x.second)
            if (!mark[y])
                dfs2(base_reverse, y, mark);
}
void dfs(int v, vector<bool> &reachable, vector<map<char, int>> &base_norm, vector<bool> &isTerminal) {
    if (reachable[v])
        return;
    reachable[v] = true;
    for (auto &u: base_norm[v])
        dfs(u.second, reachable, base_norm, isTerminal);
}
vector<vector<bool>> build_table(int n, vector<bool> &isTerminal, vector<map<char, vector<int>>> &base_reverse) {
    vector<pair<int, int>> queue;
    vector<vector<bool>> marked(n, vector<bool>(n));
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (isTerminal[i] != isTerminal[j]) {
                marked[i][j] = marked[j][i] = true;
                queue.emplace_back(i, j);
            }
    int pos = 0;
    while (pos < queue.size()) {
        auto par = queue[pos];
        for (char c = 'a'; c <= 'z'; ++c)
            for (auto r: base_reverse[par.first][c])
                for (auto s: base_reverse[par.second][c])
                    if (!marked[r][s]) {
                        marked[r][s] = marked[s][r] = true;
                        queue.emplace_back(r, s);
                    }
        ++pos;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << marked[i][j] << " ";
        }
        cout << endl;
    }
    return marked;
}
 
void build_DFA(ofstream &fout, int n, vector<int> &component, vector<map<char, int>> &base_norm, int components_count, vector<bool> &isTerminal) {
    set<pair<int, pair<int, char>>> result;
    set<int> dop;
    for (int i = 1; i < n; ++i) {
        if (component[i] < 1)
            continue;
        if (isTerminal[i])
            dop.insert(component[i]);
        for (auto x: base_norm[i])
            if (component[x.second] > 0)
                result.insert({component[i], {component[x.second], x.first}});
    }
    fout << components_count << " " << result.size() << " " << dop.size() << endl;
    if (dop.empty()) {
        return;
    }
    for (auto x: dop) {
        fout << x << " ";
    }
    fout << endl;
    for (auto x: result)
        fout << x.first << " " << x.second.first << " " << x.second.second << endl;
}
 
void minimization(int n, vector<bool> &isTerminal, vector<map<char, int>> &base_norm, vector<map<char, vector<int>>> &base_reverse, ofstream &fout) {
    vector<bool> reachable(n), mark(n);
    dfs(1, reachable, base_norm, isTerminal);
    for (int i = 0; i < n; ++i)
        if (isTerminal[i])
            dfs2(base_reverse, i, mark);
    for (int i = 0; i < n; ++i)
        reachable[i] = reachable[i] & mark[i];
    for (int i = 0; i < n; ++i)
        for (char c = 'a'; c <= 'z'; c++) {
            if (base_norm[i].find(c) == base_norm[i].end()) {
                base_norm[i][c] = 0;
                base_reverse[0][c].push_back(i);
            }
        }
    vector<vector<bool>> marked = build_table(n, isTerminal, base_reverse);
    vector<int> component;
    component.assign(n, -1);
    int components_count = 0;
    for (int i = 1; i < n; ++i) {
        if (!reachable[i])
            continue;
        if (component[i] == -1) {
            ++components_count;
            component[i] = components_count;
            for (int j = i + 1; j < n; ++j)
                if (!marked[i][j])
                    component[j] = components_count;
        }
    }
    build_DFA(fout, n, component, base_norm, components_count, isTerminal);
}
 
int main() {
    ios ::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream fin("minimization.in");
    ofstream fout("minimization.out");
    int n, m, k;
    fin >> n >> m >> k;
    ++n;
    vector<bool> dop(n);
    vector<map<char, vector<int>>> base_reverse(n);
    vector<map<char, int>> base_norm(n);
    int x, y;
    char c;
    for (int i = 0; i < k; ++i) {
        fin >> x;
        dop[x] = true;
    }
    for (int i = 0; i < m; ++i) {
        fin >> x >> y >> c;
        base_reverse[y][c].push_back(x);
        base_norm[x][c] = y;
    }
 
    minimization(n, dop, base_norm, base_reverse, fout);
    fout.close();
    fin.close();
    return 0;
}
