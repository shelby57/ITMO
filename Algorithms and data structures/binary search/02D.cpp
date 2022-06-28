#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
vector <int> a;
bool f(int l) {
	int cnt = 0;
	for(int i = 0; i < n; ++i)
		cnt += a[i] / l;
	return cnt >= k;
}
main() {
	cin >> n >> k;
	a.resize(n);
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	sort(a.begin(),a.end());
	int l = 0,r = 1e9;
	while(r - l > 1) {
		int m = (r + l) / 2;
		if(f(m))
			l = m;
		else
			r = m;
	}
	if(f(r))
		cout << r;
	else
		cout << l;
	return 0;
}



