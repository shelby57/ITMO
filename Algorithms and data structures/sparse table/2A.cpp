#include <cmath>
#include <iostream>
#include <vector>
#define int long long
using namespace std;
int fl(int n) {
    if (n <= 1) {
        return 0;
    }
    return fl(n / 2) + 1;
}
int32_t main() {
    int n, m, a1;
    cin >> n >> m >> a1;
    int u1, v1;
    vector<int> base(n);
    base[0] = a1;
    for (int i = 1; i < n; ++i)
        base[i] = (23 * base[i - 1] + 21563) % 16714589;
 
    int len = ceil(log2(n)) + 1;
    vector<vector<int>> table(2 * n, vector<int>(len, LONG_LONG_MAX));
 
    for (int j = 0; j <= log2(n); ++j)
        for (int i = 0; i + (1 << j) <= n; ++i) {
            if (j == 0) {
                table[i][j] = base[i];
            } else {
                table[i][j] = min(table[i][j - 1], table[i + (int) pow(2, j - 1)][j - 1]);
            }
        }
    cin >> u1 >> v1;
    int lg = (int) log2(abs(v1 - u1) + 1);
    int res = min(table[min(u1, v1) - 1][lg], table[max(v1, u1) - (1 << lg)][lg]);
    for (int i = 1; i < m; ++i) {
        // cout << u1 << " " << v1 << " " << res << endl;
        u1 = ((17 * u1 + 751 + res + 2 * i) % n) + 1;
        v1 = ((13 * v1 + 593 + res + 5 * i) % n) + 1;
        lg = (int) log2(abs(v1 - u1) + 1);
        res = min(table[min(u1, v1) - 1][lg], table[max(v1, u1) - (int) pow(2, lg)][lg]);
    }
    cout << u1 << " " << v1 << " " << res;
    return 0;
}