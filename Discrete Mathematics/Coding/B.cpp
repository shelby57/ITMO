#include<bits/stdc++.h>
using namespace std;
int n,k;
void count_sort(vector <int> &p,vector <int> &c) {
    int i;
    vector <int> cnt(n);
    vector <int> p_new(n);
    for(i = 0; i < n; ++i) {
        ++cnt[c[i]];
    }
    vector <int> pos(n);
    pos[0] = 0;
    for(i = 1; i < n; ++i) {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for(i = 0; i < n; ++i) {
        int x = p[i];
        int ind = c[x];
        p_new[pos[ind]] = x;
        ++pos[ind];
    }
    p = p_new;
}
main() {
    ios :: sync_with_stdio(false);
    cin.tie();
    string st;
    getline(cin,st);
    int i;
    n = st.size();
    vector <int> p(n),c(n);
    {
        vector <pair<char,int> > a(n);
        for(i = 0; i < n; ++i) {
            a[i] = {st[i],i};
        }
        sort(a.begin(),a.end());
        for(i = 0; i < n; ++i) {
            p[i] = a[i].second;
        }
        c[p[0]] = 0;
        for(i = 1; i < n; ++i) {
            if(a[i].first == a[i - 1].first) {
                c[p[i]] = c[p[i - 1]];
            } else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
    }
    k = 1;
    while(k < n) {
        for(i = 0; i < n; ++i) {
            p[i] = (p[i] - k + n) % n;
        }
        count_sort(p, c);
        vector <int> c_new(n);
        c_new[p[0]] = 0;
        for(i = 1; i < n; ++i) {
            pair <int,int> prev = make_pair(c[p[i - 1]], c[(p[i - 1] + k) % n]);
            pair <int,int> neww = make_pair(c[p[i]], c[(p[i] + k) % n]);
            if(neww == prev) {
                c_new[p[i]] = c_new[p[i - 1]];
            } else {
                c_new[p[i]] = c_new[p[i - 1]] + 1;
            }
        }
        c = c_new;
        if(c[n] == n - 1) {
            break;
        }
        k *= 2;
    };
    for(i = 0; i < n; ++i)
        cout << st[(p[i] + st.size() - 1) % st.size()];
    return 0;
}
