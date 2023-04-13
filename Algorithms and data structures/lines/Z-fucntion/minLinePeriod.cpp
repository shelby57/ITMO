/*
В этой задаче строка p называется периодом строки s,
если повторённая бесконечное количество раз строка p
содержит s в качестве своего префикса. Иными словами, если pp…p…
начинается s.

Ваша задача найти такую строку p, которая является кратчайшим периодом заданной строки s.
Например, для s = abcab её минимальный период это p=abc.

ЕСЛИ НУЖЕН ТОЧНЫЙ ПЕРИОД, ТО ДЕЛИТЕЛИ
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
        string s;
        cin >> s;
        vector<int> z = Z_function(s);
        vector<int> result(s.size() + 1, 1);
        for (int i: z) {
            if (i != 0)
                result[i] += 1;
        }
        int count = 0;
        for (int i = result.size() - 1; i >= 0; --i) {
            int prev = count;
            if (result[i] != 1) {
                count += result[i] - 1;
            }
            result[i] += prev;
        }
        for (int i = 1; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << "\n";
    }
}
