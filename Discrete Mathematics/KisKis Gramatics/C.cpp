#include <bits/stdc++.h>
using namespace std;
 
map<int, vector<string>> base;
vector<bool> mark;
void dfs(int v) {
    if (mark[v])
        return;
    mark[v] = true;
    for (const auto &y: base[v])
        for (auto x: y)
            if (x >= 'A' && x <= 'Z')
                dfs(x - 'A');
}
int main() {
    ifstream fin("useless.in");
    ofstream fout("useless.out");
    int n;
    char start;
    fin >> n >> start;
    start -= 'A';
    string s;
    char c;
    vector<bool> ass(26);
    ass[start] = true;
    for (int i = 0; i < n; ++i) {
        fin >> c;
        c -= 'A';
        ass[c] = true;
        getline(fin, s);
        for (char j: s)
            if (j >= 'A' && j <= 'Z')
                ass[j - 'A'] = true;
        base[c].push_back(s);
    }
    vector<bool> por(26);
    for (auto &p: base)
        for (const auto &y: p.second) {
            bool ok = true;
            for (auto x: y)
                if (x >= 'A' && x <= 'Z') {
                    ok = false;
                    break;
                }
            if (ok) {
                por[p.first] = true;
                break;
            }
        }
    bool flag = true;
    while (flag) {
        flag = false;
        for (auto &p: base) {
            if (!por[p.first])
                for (const auto &y: p.second) {
                    bool ok = true;
                    for (auto x: y)
                        if (x >= 'A' && x <= 'Z' && !por[x - 'A']) {
                            ok = false;
                            break;
                        }
                    if (ok) {
                        flag = true;
                        por[p.first] = true;
                        break;
                    }
                }
        }
    }
    vector<bool> res(26);
 
    for (int i = 0; i < 26; ++i)
        if (!por[i] && ass[i]) {
            base.erase(i);
            res[i] = true;
            for (auto &p: base) {
                vector<string> result;
                for (auto &k: p.second) {
                    bool ok = true;
                    for (char j: k)
                        if (j == (i + 'A')) {
                            ok = false;
                        }
                    if (ok)
                        result.push_back(k);
                }
                p.second = result;
            }
        }
    mark.assign(26, false);
    dfs(start);
    for (int i = 0; i < 26; ++i)
        if (!mark[i] && ass[i])
            res[i] = true;
    for (int i = 0; i < 26; ++i)
        if (res[i])
            fout << char(i + 'A') << " ";
    fin.close();
    fout.close();
    return 0;
}
