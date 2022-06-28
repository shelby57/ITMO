#include<bits/stdc++.h>
using namespace std;
bool comp(int x, int y) {
	return x % 10 < y % 10;
}
main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector <int> a(n);
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	stable_sort(a.begin(),a.end(),comp);
	for(int i = 0; i < n; ++i)
		cout << a[i] << " ";
	return 0;
}


