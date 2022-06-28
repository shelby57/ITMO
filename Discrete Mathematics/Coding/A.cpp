#include<bits/stdc++.h>
#define int long long
#define s second
#define f first
using namespace std;
struct node {
    int l,r;
};
vector <node> tree;
vector <int> a;
int res = 0, n;
void dfs(node v,int ans) {
    if(v.l >= n)
        dfs(tree[v.l - n], ans + 1);
    else
        res += ans * a[v.l];
    if(v.r >= n)
        dfs(tree[v.r - n], ans + 1);
    else
        res += ans * a[v.r];
}
main() {
    int v;
    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    sort(a.begin(), a.end());
    multimap <int, int> mas;
    for(int i = 0; i < n; ++i)
        mas.insert({a[i],i});
    int k = n;
    while(mas.size() > 1) {
        auto v1 = mas.begin();
        auto v2 = ++v1;
        --v1;
        tree.push_back({v1 -> s, v2 -> s});
        mas.insert({v1 -> f + v2 -> f,k++});
        mas.erase(v1);
        mas.erase(v2);
    }
    dfs(tree.back(), 1);
    cout << res;
    return 0;
}
