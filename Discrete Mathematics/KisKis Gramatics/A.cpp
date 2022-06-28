#include <bits/stdc++.h>
using namespace std;
vector<vector<pair<int, int>>> base(26);
bool dfs(int v, string &s, int ind) {
    if (ind == s.size())
        return v == -1;
 
    if (v == -1)
        return false;
 
    for (auto &x: base[v])
        if (x.first == (s[ind] - 'a') && dfs(x.second, s, ind + 1))
            return true;
    return false;
}
int main() {
    ios ::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream fin("automaton.in");
    ofstream fout("automaton.out");
    int n;
    char start;
    fin >> n >> start;
    string s;
    char c;
    set<char> result;
    for (int i = 0; i < n; ++i) {
        fin >> c >> s >> s;
        int u = c - 'A';
        int symb = s[0] - 'a';
        if (s.size() == 1)
            base[u].emplace_back(symb, -1);
        else
            base[u].emplace_back(symb, s[1] - 'A');
    }
    int m;
    fin >> m;
    while (m--) {
        fin >> s;
        if (dfs(start - 'A', s, 0))
            fout << "yes\n";
        else
            fout << "no\n";
    }
    fin.close();
    fout.close();
    return 0;
}
