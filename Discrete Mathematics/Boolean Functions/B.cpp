#include<bits/stdc++.h>
#define int long long
using namespace std;
bool check_T0(vector <bool> &f) {
    return (f[0] == 0);
}
bool check_T1(vector <bool> &f) {
    return (f.back() == 1);
}
int num_1(int x) {
    int cnt = 0;
    while(x > 0) {
        cnt += x % 2;
        x /= 2;
    }
    return cnt;
}
bool check_S(vector <bool> &f) {
    for(int i = 0; i < f.size(); ++i)
        if(f[i] == f[f.size() - i - 1])
            return 0;
    return 1;
}
bool check_M(vector <bool> &f) {
    for(int i = 0; i < f.size(); ++i)
        for(int j = i + 1; j < f.size(); ++j)
            if((i | j) == j && f[i] > f[j])
                return 0;
    return 1;
}
bool check_L(vector <bool> &f) {
    int k = f.size();
    vector <vector <bool> > a(k, vector <bool> (k));
    for(int i = 0; i < k; ++i)
        a[0][i] = f[i];
    for(int i = 1; i < k; ++i)
        for(int j = 0; j < k - i; ++j)
            a[i][j] = (a[i - 1][j] + a[i - 1][j + 1]) % 2;
    int x = 0,cnt = 0;
    for(int i = 0; i < k; ++i) {
        if(num_1(i) > 1 && a[i][0])
            return 0;
    }
    return 1;
}
main() {
    int n;
    cin >> n;
    vector <bool> mark;
    mark.assign(5,1);
    char x;
    int s;
    for(int i = 0; i < n; ++i) {
        cin >> s;
        vector <bool> a;
        for(int j = 0; j < (1 << s); ++j) {
            cin >> x;
            if(x == '0')
                a.push_back(0);
            else
                a.push_back(1);
        }
        mark[0] = mark[0] * check_T0(a);
        mark[1] = mark[1] * check_T1(a);
        mark[2] = mark[2] * check_S(a);
        mark[3] = mark[3] * check_M(a);
        mark[4] = mark[4] * check_L(a);
    }
    int ok = 0;
    for(int i = 0; i < 5; ++i) {
        ok += mark[i];
    }
    if(ok == 0)
        cout << "YES";
    else
        cout << "NO";
    return 0;
 
}
