#include<bits/stdc++.h>
using namespace std;
#define int long long int
struct node {
    double ll,rr;
};
 int NOD(int x,int y)
  {
   if(x != 0) return NOD(y % x,x); else return y;
  }
   int NOK(int x,int y)
   {
   	return (x / NOD(x,y)) * y;
   }
main() {
    int n;
    cin >> n;
    string s;
    getline(cin,s);
    getline(cin,s);
    vector <int> alf(n);
    for(int i = 0; i < s.size(); ++i)
        alf[s[i] - 97] += 1;
    vector <double> ver(n);
    int md = 1e15;
    double l = 0,r = 1;
    for(int i = 0; i < n; ++i)
        ver[i] = (alf[i] + 0.0) / s.size();
    vector <double> pref(n);
    vector <node> gran(n);
    for(int i = 0; i < s.size(); ++i) {
        int x = s[i] - 97;
        gran[0].ll = l;
        gran[0].rr = gran[0].ll + (r - l) * ver[0];
        for(int j = 1; j < n; ++j) {
            gran[j].ll = gran[j - 1].rr;
            gran[j].rr = gran[j].ll + (r - l) * ver[j];
        }
        l = gran[x].ll;
        r = gran[x].rr;
    }
    cout << fixed << setprecision(40) << l << endl;
    cout << fixed << setprecision(40) << r << endl;
    int ch = 0, zn = 0, k = 0;
    for(int q = 1; q < 1e18; q *= 2) {
        ++k;
        int l1 = 0, r1 = q;
        int ans = -1;
        double ll = l * q;
        double rr = r * q;
        double res;
        while(r1 - l1 > 1) {
            int m = (l1 + r1) / 2;
            if(m >= ll && m < rr) {
                ans = m;
                break;
            }
            if(m >= ll)
                r1 = m;
            else
                l1 = m;
        }
        if(ans != -1) {
            ch = ans;
            zn = k;
            break;
        }
        res = (l1 + r1) / 2;
        if(res >= ll && res < rr) {
            ch = (l1 + r1) / 2;
            zn = k;
            break;
        }
    }
    cout << n << endl;
    for(int i = 0; i < n; ++i)
        cout << alf[i] << " ";
    cout << endl;
    if(ch == 0) {
        cout << 0;
        return 0;
    }
    vector <int> ans(zn - 1);
    zn -= 2;
    while(ch > 0) {
        ans[zn--] = ch % 2;
        ch /= 2;
    }
    for(auto x : ans)
        cout << x;
    return 0;
}
