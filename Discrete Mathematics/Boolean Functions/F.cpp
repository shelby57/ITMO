#include<bits/stdc++.h>
using namespace std;
main() {
    int n,k;
    cin >> n >> k;
    vector <vector <int> > a(k,vector <int> (n));
    vector <int> check(n);
    vector <int> cnt(k);
    for(int i = 0; i < k; ++i)
        for(int j = 0; j < n; ++j) {
            cin >> a[i][j];
            if(a[i][j] >= 0)
                ++cnt[i];
        }
    while(true) {
        bool ok = false;
        for(int i = 0; i < k; ++i) {
            if(cnt[i] == 0) {
                cout << "YES";
                return 0;
            }
            if(cnt[i] == -2)
                continue;
            if(cnt[i] == 1) {
                ok = true;
                for(int j = 0; j < n; ++j)
                    if(a[i][j] >= 0)
                        for(int p = 0; p < k; ++p)
                            if(a[i][j] == a[p][j]) {
                                cnt[p] = -2;
                            } else if(a[p][j] >= 0) {
                                --cnt[p];
                                a[p][j] = -1;
                            }
            }
        }
        if(!ok) {
            cout << "NO";
            return 0;
        }
 
    }
}
