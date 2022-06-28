#include <bits/stdc++.h>
using namespace std;
 
 
int main() {
    ios ::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream fin("epsilon.in");
    ofstream fout("epsilon.out");
    int n;
    char start;
    fin >> n >> start;
    vector<pair<char, string>> base;
    string s;
    char c;
    set<char> result;
    for (int i = 0; i < n; ++i) {
        fin >> c;
        getline(fin, s);
        cout << s << " " << s.size() << "\n";
        std::size_t ind = s.find("->") + 3;
        //   if(s.back() > 64 && s.back() < 91)
        if (s.size() <= ind) {
            s = "";
            result.insert(c);
        } else
            s = s.substr(ind);
        cout << s << endl;
        base.emplace_back(c, s);
    }
    bool flag = true;
    while (flag) {
        flag = false;
        for (auto &x: base) {
            if (result.find(x.first) != result.end())
                continue;
            bool ok = true;
            for (const char y: x.second)
                if (result.find(y) == result.end()) {
                    ok = false;
                    break;
                }
            if (ok) {
                flag = true;
                result.insert(x.first);
            }
        }
    }
    for (auto &x: result) {
        fout << x << " ";
    }
    fin.close();
    fout.close();
    return 0;
}
