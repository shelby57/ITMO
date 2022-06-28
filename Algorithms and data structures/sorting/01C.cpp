#include<bits/stdc++.h>
using namespace std;
main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <int> a(n);
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	vector <bool> mark(n);
	for(int i = 0; i < n; ++i)
		if(a[i] < n)
			mark[a[i]] = 1;
	for(int i = 0; i < n; ++i)
		if(!mark[i]) {
			cout << i;
			return 0;
		}
	cout << n;
	return 0;
}


