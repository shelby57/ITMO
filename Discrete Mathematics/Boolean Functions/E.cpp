#include<bits/stdc++.h>
using namespace std;
bool convert (char x) {
    if(x == '0')
        return 0;
    return 1;
}
main() {
    int n;
    cin >> n;
    int len = (1 << n);
    vector <vector <bool> > base(len, vector <bool> (n));
    vector <vector <bool> > a(len, vector <bool> (len));
    char x;
    for(int i = 0; i < len; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> x;
            base[i][j] = convert(x);
        }
        cin >> x;
        a[0][i] = convert(x);
    }
    for(int i = 1; i < len; ++i)
        for(int j = 0; j < len - i; ++j)
            a[i][j] = (a[i - 1][j] + a[i - 1][j + 1]) % 2;
    for(int i = 0; i < len; ++i) {
        for(int j = 0; j < n; ++j)
            cout << base[i][j];
        cout << " " << a[i][0] << '\n';
    }
    return 0;
}
