#include<bits/stdc++.h>
using namespace std;
main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int r,c;
	cin >> r >> c;
	int n = r * c;
	vector <int> a(n);
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	sort(a.begin(),a.end());
	int res = 0;
	for(int i = c; i <= n; i += c)
		res = max(res, a[i - 1] - a[i - c]);
	cout << res;
	return 0;
}


