#include<bits/stdc++.h>
using namespace std;
main() {
	int n;
	cin >> n;
	for(int i = 0; i < (1 << n); i++) {
		vector <int> a(n);
		int x = i;
		int pos = n - 1;
		while(x > 0) {
			a[pos--] = x % 2;
			x /= 2;
		}
		for(int i = 0; i < n; i++)
			cout << a[i];
		cout << endl;
	}
	return 0;
}
