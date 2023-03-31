/*

Дана строка s. Ответьте на m запросов вида: равны ли подстроки s[a..b] и s[c..d].

Входные данные
В первой строке ввода записана строка s (1 ≤ |s| ≤ 105).

Во второй строке записано целое число m — количество запросов (0 ≤ m ≤ 105).

В следующих m строках четверки чисел a, b, c, d (1 ≤ a ≤ b ≤ |s|, 1 ≤ c ≤ d ≤ |s|).

Выходные данные
Выведите m строк.
Выведите Yes, если подстроки совпадают, и No иначе.
*/
#include <iostream>
#include <vector>
using namespace std;
vector<int> prefix_function(const string &s) {
    vector<int> func(s.size(), 0);
    for (int i = 1; i < s.size(); ++i) {
        int k = func[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = func[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        func[i] = k;
    }
    return func;
}
int main() {
    string s;
    cin >> s;
    vector<int> func = prefix_function(s);
    for (int i: func) {
        cout << i << " ";
    }
    return 0;
}
/*
 *
 */
