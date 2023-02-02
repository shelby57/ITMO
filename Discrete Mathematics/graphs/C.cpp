#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string s;

bool comp(int x, int y) {
    cout << 1 << " " << x << " " << y << endl;
    cout.flush();
    cin >> s;
    return s == "YES";
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    stable_sort(a.begin(), a.end(), comp);
    cout << 0;
    for (int i: a) {
        cout << " " << i;
    }
    cout << endl;
    return 0;
}