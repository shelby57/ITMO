#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#define int long long
using namespace std;
int32_t main() {
    ifstream fin("schedule.in");
    ofstream fout("schedule.out");
    int n;
    fin >> n;
    vector<pair<int, int>> base;
    int d, w;
    for (int i = 0; i < n; ++i) {
        fin >> d >> w;
        if (d >= n) {
            continue;
        }
        base.emplace_back(w, d);
    }
    fin.close();
    sort(base.rbegin(), base.rend());
    vector<int> sp(n);
    int result = 0;
    for (auto x: base) {
        int pos = x.second - 1;
        int t = x.first;
        if (sp[pos] == 0) {
            sp[pos] = 1;
        } else {
            while (pos >= 0 && sp[pos] != 0) {
                --pos;
            }
            (pos == -1) ? result += t : sp[pos] = 1;
        }
    }
    fout << result;
    fout.close();
    return 0;
}
