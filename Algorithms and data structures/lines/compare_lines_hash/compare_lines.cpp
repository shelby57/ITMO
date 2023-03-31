#include <iostream>
#include <utility>
#include <vector>
using namespace std;
struct MyString {
    string s;
    vector<long long> hash;
    vector<long long> p;
    const long long md = 2147483647;
    explicit MyString(string ss) : s(std::move(ss)) {
        hash.resize(s.size() + 1, 0);
        p.resize(s.size() + 1, 1);
        for (int i = 1; i < p.size(); i++) {
            p[i] = (p[i - 1] * 239) % md;
        }
        hash[0] = 0;
        for (int i = 0; i < s.size(); i++) {
            hash[i + 1] = (hash[i] + (p[i] * s[i]) % md) % md;
        }
    }
    bool compare(int l1, int r1, int l2, int r2) {
        if (r1 - l1 != r2 - l2 || get_hash(l1, r1) != get_hash(l2, r2)) {
            return false;
        }
        for (int i = 0; i <= r1 - l1; i++) {
            if (s[l1 + i - 1] != s[l2 + i - 1]) {
                return false;
            }
        }
        return true;
    }
    long long get_hash(int l, int r) {
        return ((hash[r] - hash[l - 1]) * p[s.size() - l] % md + md) % md;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    getline(cin, s);
    MyString line = MyString(s);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (line.compare(l1, r1, l2, r2) ? "Yes\n" : "No\n");
    }
    return 0;
}