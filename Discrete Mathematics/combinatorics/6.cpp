#include<bits/stdc++.h>
using namespace std;
main() {
	int n;
	cin >> n;
	vector <vector <bool> > base;
	for(int i = 0; i < (1 << n); i++) {
		vector <bool> a(n);
		int x = i;
		int pos = n - 1;
		while(x > 0) {
			a[pos--] = x % 2;
			x /= 2;
		}
		bool ok = 1;
		for(int i = 0; i < n - 1; i++)
			if(a[i] * a[i + 1] > 0) {
				ok = 0;
				break;
			}
		if(ok)
			base.push_back(a);
	}
	int len = base.size();
	cout << len << endl;
	for(int i = 0; i < len; ++i) {
		for(int j = 0; j < n; ++j)
			cout << base[i][j];
		cout << endl;
	}
	return 0;
}
