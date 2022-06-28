#include<bits/stdc++.h>

using namespace std;
int32_t main() {
	ifstream in("muggers.in");
	ofstream out("muggers.out");
	int n,k;
	in >> n >> k;
	vector <int> a(n);
	for(int i = 0; i < n; ++i)
		in >> a[i];
	++k;
	for(int i = k; i < n; ++i) {
		int ans = 1e9;
		for(int j = i - k; j < i; ++j)
			ans = min(ans, a[j]);
		a[i] += ans;
	}
	out << a[n - 1] << '\n';
	return 0;
}


