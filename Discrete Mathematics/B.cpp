#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#define int long long
using namespace std;
vector<int> p, sz;
struct record {
    int v1, v2, w, ind;
};
bool comp(record x, record y) {
    return x.w > y.w;
}
int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}
void uni(int x, int y) {
    if (sz[x] > sz[y]) {
        swap(x, y);
    }
    p[x] = y;//êîðåíü òïåïåðü ýòî Y
    sz[y] += sz[x];
}
int32_t main() {
    ifstream fin("destroy.in");
    ofstream fout("destroy.out");
    int n, m, s;
    fin >> n >> m >> s;
    vector<record> sp(m);
    int result = 0;
    for (int i = 0; i < m; ++i) {
        fin >> sp[i].v1 >> sp[i].v2 >> sp[i].w;
        --sp[i].v1;
        --sp[i].v2;
        result += sp[i].w;
        sp[i].ind = i;
    }
    fin.close();
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    sz.resize(n, 0);
    vector<bool> mark(m, false);
    sort(sp.begin(), sp.end(), comp);
    vector<int> count;
    for (int i = 0; i < m; ++i) {
        int x = find(sp[i].v1);
        int y = find(sp[i].v2);
        if (x != y) {
            uni(x, y);
            result -= sp[i].w;
            mark[i] = true;
        }
    }
    for (int i = 0; i < m; ++i) {
        if (!mark[i] && result > s) {
            result -= sp[i].w;
            mark[i] = true;
        }
    }
    for (int i = 0; i < m; ++i) {
        if (!mark[i]) {
            count.push_back(sp[i].ind);
        }
    }
    sort(count.begin(), count.end());
    fout << count.size() << "\n";
    for (int i: count) {
        fout << i + 1 << " ";
    }
    fout.close();
    return 0;
}
