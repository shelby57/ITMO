#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
vector<vector<bool>> base;

bool comp(int x, int y) {
    return base[x][y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    base.resize(n);
    vector<int> path(n);
    for (int i = 0; i < n; ++i) {
        base[i].resize(n, false);
        path[i] = i;
    }
    char x;
    for (int i = 1; i < n; ++i)
        for (int j = 0; j < i; ++j) {
            cin >> x;
            base[i][j] = (x == '1');
            base[j][i] = !base[i][j];
        }
    stable_sort(path.begin(), path.end(), comp);
    vector<int> cycle;
    int k = n - 1;
    while (k > 1 && !base[path[k]][path[0]]) {
        --k;
    }
    cycle.insert(cycle.begin(), path.begin(), path.begin() + k + 1);
    path.erase(path.begin(), path.begin() + k + 1);
    k = 0;
    while(!path.empty()) {
        int pos = 0;
        while (pos < cycle.size() && !base[path[k]][cycle[pos]]) {
            ++pos;
        }
        if (pos < cycle.size()) {
            cycle.insert(cycle.begin() + pos, path.begin(), path.begin() + k + 1);
            path.erase(path.begin(), path.begin() + k + 1);
            k = 0;
        } else {
            k++;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << cycle[i] + 1 << " ";
    }
    return 0;
}
/*
 * 4
 *
 * 0
 * 11
 * 001
 */
