/*
Заданы две строки s и t одинаковой длины. Надо проверить, является ли t
циклическим сдвигом s.
Если да, то выведите позицию циклического сдвига влево, иначе -1.
https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/B
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> Z_function(const string &s) {
    size_t n = s.size();
    vector<int> z(s.size());
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); i++) {
        if (r >= i) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (z[i] + i < n && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin >> q;
    while (q--) {
        string s, t;
        cin >> s;
        cin >> t;
        size_t len = t.size();
        t.append("$").append(s).append(s);
        vector<int> z = Z_function(t);
        int pos = find(z.begin(), z.end(), len) - z.begin() - len - 1;
        cout << ((pos > len) ? -1 : pos) << "\n";
    }
    return 0;
}
