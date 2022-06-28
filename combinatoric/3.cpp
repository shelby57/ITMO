#include<bits/stdc++.h>
using namespace std;
main() {
	int n;
	cin >> n;
	for(int i = 0; i < pow(3,n - 1); i++) {
		vector <int> a(n);
		int x = i;
		int pos = n - 1;
		while(x > 0) {
			a[pos--] = x % 3;
			x /= 3;
		}
		for(int s = 0; s < 3; ++s) {
			for(int j = 0; j < n; ++j)
				cout << (a[j] + s) % 3;
			cout << endl;
		}
	}
	return 0;
}
