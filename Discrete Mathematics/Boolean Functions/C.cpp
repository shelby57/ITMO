#include<bits/stdc++.h>
using namespace std;
vector <vector <int> > sp;
vector <vector <bool> > table;
vector <bool> mark,value;
int mx = 0;
bool convert (char x) {
    if(x == '0')
        return 0;
    return 1;
}
void dfs_depth(int v, int depth) {
    mx = max(mx,depth);
    if(mark[v])
        return;
    mark[v] = true;
    for(auto x : sp[v])
        if(!mark[x])
            dfs_depth(x,depth + 1);
}
vector <int> num,p;
void dfs_way(int v) {
    if(mark[v])
        return;
    mark[v] = 1;
    for(auto x : sp[v]) {
        if(!mark[x])
            dfs_way(x);
        num[v] += value[x] * p[v];
        p[v] *= 2;
    }
    if(sp[v].size() > 0)
        value[v] = table[v][num[v]];
    //cout << v << " -> " << num[v] << "// " << value[v] << " ** " << '\n';
    num[v] = 0;
    p[v] = 1;
}
bool comp(int &x, int &y) {
    return x > y;
}
main() {
    int n;
    cin >> n;
    int m;
    int v;
    char x;
    sp.resize(n);
    table.resize(n);
    mark.assign(n,0);
    vector <int> list;
    value.resize(n);
    num.resize(n,0);
    p.assign(n,1);
    for(int i = 0; i < n; ++i) {
        cin >> m;
        if(m == 0) {
            list.push_back(i);
            continue;
        }
        for(int j = 0; j < m; ++j) {
            cin >> v;
            sp[i].push_back(v - 1);
        }
        sort(sp[i].begin(),sp[i].end(),comp);
 
        for(int j = 0; j < (1 << m); ++j) {
            cin >> x;
            table[i].push_back(convert(x));
        }
    }
    dfs_depth(n - 1,0);
    int len = (1 << list.size());
    vector <bool> res(len);
    for(int i = 0; i < len; ++i) {
        int r = i;
        int j = list.size() - 1;
        value.assign(n,0);
        mark.assign(n,0);
        while(r > 0) {
            value[list[j--]] = r % 2;
            r /= 2;
        }
        dfs_way(n - 1);
        res[i] = value[n - 1];
    }
    cout << mx << '\n';
    for(int i = 0; i < len; ++i)
        cout << res[i];
    return 0;
}
