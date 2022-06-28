#include<bits/stdc++.h>
using namespace std;
int n;
bool reflex(vector <vector <bool > > &base) {
    bool ok = 1;
    for(int i = 0; i < n; ++i)
        ok *= base[i][i];
    return ok;
}
bool antireflex(vector <vector <bool > > &base) {
    int ok = 0;
    for(int i = 0; i < n; ++i)
        ok += base[i][i];
    return (ok == 0);
}
bool symmetry(vector <vector <bool > > &base) {
    bool ok = 1;
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
            ok *= (base[i][j] == base[j][i]);
    return ok;
}
bool antisymmetry(vector <vector <bool > > &base) {
    int ok = 0;
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
            ok += ((base[i][j] == base[j][i]) && base[i][j]);
    return (ok == 0);
}
bool transitivity(vector <vector <bool > > &base) {
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            if (i == j || !base[i][j])
                continue;
            for(int k = 0; k < n; ++k) {
                if (k == i || k == j || !base[j][k])
                    continue;
                if (!base[i][k])
                    return 0;
            }
        }
    return 1;
}
void print(vector <bool> &res) {
    for(int i = 0; i < 5; ++i)
        cout << res[i] << " ";
    cout << '\n';
}
main() {
    cin >> n;
    vector <vector <bool> > a(n,vector <bool> (n));
    vector <vector <bool> > b(n,vector <bool> (n));
    vector <vector <bool> > c(n,vector <bool> (n));
    int x;
    bool oka = 0,okb = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            cin >> x;
            if(x == 1) {
                oka = 1;
                a[i][j] = 1;
            } else
                a[i][j] = 0;
        }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            cin >> x;
            if(x == 1) {
                okb = 1;
                b[i][j] = 1;
            } else
                b[i][j] = 0;
        }
    vector <bool> marka(5),markb(5);
    if(oka) {
        marka[0] = reflex(a);
        marka[1] = antireflex(a);
        marka[2] = symmetry(a);
        marka[3] = antisymmetry(a);
        marka[4] = transitivity(a);
    }  else {
        for(int i = 0; i < 5; ++i)
            marka[i] = 1;
    }
    if(okb) {
        markb[0] = reflex(b);
        markb[1] = antireflex(b);
        markb[2] = symmetry(b);
        markb[3] = antisymmetry(b);
        markb[4] = transitivity(b);
    }  else {
        for(int i = 0; i < 5; ++i)
            markb[i] = 1;
    }
    print(marka);
    print(markb);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(a[i][j])
                for(int k = 0; k < n; ++k)
                    if(b[j][k])
                        c[i][k] = 1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j)
            cout << c[i][j] << " ";
        cout << '\n';
    }
}
