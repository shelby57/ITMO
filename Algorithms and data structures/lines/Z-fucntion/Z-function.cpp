/*
Постройте Z-функцию для заданной строки s.
Входные данные
Первая строка входного файла содержит s (1 ≤ |s| ≤ 10e6). Строка состоит из букв латинского алфавита.
Выходные данные
Выведите значения Z-функции строки s для индексов 2,3,...,|s|.
*/
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
    string s;
    cin >> s;
    vector<int> result = Z_function(s);
    for (int i = 1; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    return 0;
}
