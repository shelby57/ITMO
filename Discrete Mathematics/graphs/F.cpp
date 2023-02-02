#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> code(n - 2), sz(n, 0);
    set<int> V;
    for (int i = 0; i < n - 2; ++i) {
        cin >> code[i];
        sz[--code[i]]++;
    }
    for (int i = 0; i < n; ++i)
        if (sz[i] == 0) {
            V.insert(i);
        }
    vector<pair<int, int>> result;
    int pos = 0;
    while(pos < code.size()) {
        int v = *V.begin();
        V.erase(v);
        int u = code[pos++];
        --sz[u];
        if(sz[u] == 0) {
            V.insert(u);
        }
        result.emplace_back(u, v);
    }
    result.emplace_back(*V.begin(), *(++V.begin()));
    for (auto p: result) {
        cout << p.first + 1 << " " << p.second + 1 << "\n";
    }

    return 0;
}
