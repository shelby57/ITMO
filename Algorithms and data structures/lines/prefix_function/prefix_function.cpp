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