#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<int> &tree, vector<vector<int>> &base, int v) {
    for (int to: base[v]) {
        if (tree[v] != to) {
            tree[to] = v;
            dfs(tree, base, to);
        }
    }
}

vector <int> f(vector<vector<int>> &base) {
    vector <int> tree(base.size());
    tree[base.size() - 1] = -1;
    dfs(tree, base, base.size() - 1);
    int pos = -1;
    vector<size_t> sz(base.size());
    for (int i = 0; i < base.size(); ++i) {
        sz[i] = base[i].size();
        if (pos == -1 && sz[i] == 1) {
            pos = i;
        }
    }
    int end = pos;
    vector<int> ans;
    for (int i = 0; i < base.size() - 2; ++i) {
        int to = tree[end];
        ans.push_back(to);
        sz[to]--;
        if (sz[to] == 1 && to < pos) {
            end = to;
            continue;
        }
        ++pos;
        while (pos < base.size() && sz[pos] != 1) {
            ++pos;
        }
        end = pos;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<vector<int>> base(n);
    int u, v;
    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
        base[u - 1].push_back(v - 1);
        base[v - 1].push_back(u - 1);
    }
    vector <int> w = f(base);
    for(auto x : w) {
        cout << x + 1 << " ";
    }

    return 0;
}
