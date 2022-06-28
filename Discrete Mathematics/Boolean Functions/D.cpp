#include<bits/stdc++.h>
using namespace std;
bool convert (char x) {
    if(x == '0')
        return 0;
    return 1;
}
struct node {
    int operation,one,two;
};
main() {
    int n;
    cin >> n;
    int len = (1 << n);
    int v;
    vector <node> ans;
    int k = n;
    int end;
    vector <int> num(n);
    vector <bool> a(n);
    char x;
    bool ok = 0;
    for(int q = 0; q < len; ++q) {
        for(int j = 0; j < n; ++j) {
            cin >> x;
            a[j] = convert(x);
            num[j] = j;
        }
        cin >> v;
        if(v) {
            for(int i = 0; i < n; ++i)
                if(!a[i]) {
                    ans.push_back({1,i,-1});
                    num[i] = k;
                    ++k;
                }
            for(int i = 1; i < n; ++i) {
                ans.push_back({2,num[i - 1],num[i]});
                num[i] = k;
                ++k;
            }
            if(ok) {
                ans.push_back({3,end,num[n - 1]});
                ++k;
            }
            ok = 1;
            end = k - 1;
        }
    }
     
    if(!ok) {
        cout << n + 2 << '\n';
        cout << 1 << " " << 1 << '\n';
        cout << 2 << " " << 1 << " " << n + 1;
        return 0;
    }
    cout << ans.size() + n << '\n';
    for(int i = 0; i < ans.size(); ++i) {
        int x = ans[i].operation;
        cout << x << " ";
        if(x == 1) {
            cout << ans[i].one + 1;
        } else {
            cout << ans[i].one + 1 << " " << ans[i].two + 1;
        }
        cout << '\n';
    }
    return 0;
}
