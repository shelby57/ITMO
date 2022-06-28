#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node {
	int l,r;
};
bool comp( node &x, node &y) {
	return x.r < y.r;
}
main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <int> a(n),b(n);
	vector <node> p(n);
	for(int i = 0; i < n; ++i)
		cin >> p[i].l >> p[i].r;
	sort(p.begin(),p.end(),comp);
	for(int i = 0; i < n; ++i) {
		a[i] = p[i].l;
		b[i] = p[i].r;
	}
	vector <vector <int> > base(n);
	int sum = 0,mx = 0,ans = 0;
	int cnt = 0;
	for(int i = n - 1; i >= 0; --i) {
		++cnt;
		if(mx <= cnt*b[i] + sum) {
			mx = cnt*b[i] + sum;
			ans = b[i];
		}
		int ind = lower_bound(b.begin(),b.end(),a[i]) - b.begin();
		base[ind].push_back(i);
		for(auto j : base[i]) {
			--cnt;
			sum += a[j];
		}
	}
	cout << ans << " " << mx;
	return 0;
}


