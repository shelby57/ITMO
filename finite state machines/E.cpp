#include <bits/stdc++.h>
using namespace std;
const long long md = 1e9 + 7;
 
int main() {
    ifstream fin("problem5.in");
    ofstream fout("problem5.out");
 
    int n, m, k, l;
    fin >> n >> m >> k >> l;
    vector<bool> dop(n);
    vector<map<int, vector<int>>> sp(n);
    int x, y;
    char c;
    for (int i = 0; i < k; ++i) {
        fin >> x;
        dop[x - 1] = true;
    }
 
    for (int i = 0; i < m; ++i) {
        fin >> x >> y >> c;
        sp[x - 1][c - 'a'].push_back(y - 1);
    }
 
    vector<set<int>> queue;
 
    queue.push_back({0});
 
    map<set<int>, map<set<int>, int>> result;
 
    int pos = 0;
    map<set<int>, bool> base;
    base[queue[0]] = dop[0];
    result[queue[0]] = {};
    while (pos < queue.size()) {
        set<int> now = queue[pos];
        for (int i = 0; i < 26; ++i) {
            bool ok = false;
            set<int> new_;
            for (int num = 0; num < n; ++num) {
                if (now.find(num) == now.end()) {
                    continue;
                }
                for (auto p: sp[num][i]) {
                    new_.insert(p);// в этом цикле идем по ребрам с одинаковой буквой
                    ok |= dop[p];
                }
            }
            if (base.find(new_) == base.end()) {
                queue.push_back(new_);
                base[new_] = ok;
                result[new_] = {};
                result[now][new_] = 0;
            }
            ++result[now][new_];
        }
        ++pos;
    }

    map<set<int>, long long> now;
    now[queue[0]] = 1;
    for (int i = 0; i < l; ++i) {
        map<set<int>, long long> next;
        for (auto &v: now)
            for (auto &u: result[v.first])
                next[u.first] = (next[u.first] + v.second * result[v.first][u.first] % md) % md;
        now.clear();
        now = next;
    }
    fin.close();
    long long res = 0;
    for (auto &v: now)
        if (base[v.first])
            res = (res + v.second) % md;
    fout << res;
    fout.close();
    return 0;
}