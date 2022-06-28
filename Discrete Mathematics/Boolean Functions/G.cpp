#include<bits/stdc++.h>
#define int long long
using namespace std;
main() {
    int n,s;
    cin >> n;
    vector <int> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    cin >> s;
    if(s == 0) {
        if(!a[0])
            cout << "1";
        else
            cout << "1&~1";
        return 0;
    }
    string str = "";
    vector <int> bin(50),ans(50);
    int end = 49;
    while(s > 0) {
        bin[end--] = s % 2;
        s /= 2;
    }
    vector <vector <int> > base(n, vector <int> (50));
    for(int i = 0; i < n; ++i) {
        end = 49;
        while(a[i] > 0) {
            base[i][end--] = a[i] % 2;
            a[i] /= 2;
        }
    }
    for(int i = 0; i < bin.size(); ++i) {
        if(!bin[i])
            continue;
        vector <int> check(50);
        for(int j = 0; j < n; ++j) {
            if(base[j][i]) {
                str += to_string(j + 1);
                if(j == 0)
                    check = base[j];
                else
                    for(int k = 0; k < 50; ++k)
                        check[k] &= base[j][k];
            } else {
                str += "~" + to_string(j + 1);
                if(j == 0)
                    for(int k = 0; k < 50; ++k)
                        check[k] = ~base[j][k];
                else
                    for(int k = 0; k < 50; ++k)
                        check[k] &= ~base[j][k];
            }
            if(j != n - 1)
                str += "&";
        }
        for(int k = 0; k < 50; ++k)
            ans[k] |= check[k];
        str += "|";
    }
    str = str.substr(0,str.size() - 1);
    if(ans == bin)
        cout << str;
    else
        cout << "Impossible";
    return 0;
}
