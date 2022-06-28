#include<bits/stdc++.h>
using namespace std;
int n;
vector <int> a;
int lower(int x) {
	int l = -1,r = n - 1;
	while(r - l > 1) {
		int m = (r + l) / 2;
		if(a[m] >= x)
			r = m;
		else
			l = m;
	}
	return r;
}
int upper(int x) {
	int l = 0,r = n;
	while(r - l > 1) {
		int m = (r + l) / 2;
		if(a[m] > x)
			r = m;
		else
			l = m;
	}
	return r;
}
main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	a.resize(n);
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	sort(a.begin(),a.end());
	int k;
	cin >> k;
	int l,r;
	for(int i = 0; i < k; ++i) {
		cin >> l >> r;
		if(r < a[0] || l > a[n - 1])
			cout << 0;
		else
			cout << upper(r) - lower(l);
		cout << '\n';
	}
	return 0;
}


