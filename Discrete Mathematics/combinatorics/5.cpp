#include<bits/stdc++.h>
using namespace std;
main() {
	int n, k;
	cin >> n >> k;
	for(int b = 0; b < k; ++b) {
		vector <int> a;
		for(int i = 0; i < n; i++)
			a.push_back(i);
		if(b > 0) {
			a[0] = b - 1;
			for(int i = 0; i < n - 1; ++i) {
				for(int j = 0; j < n; ++j)
					cout << a[j];
				swap(a[i], a[i + 1]);
				cout << endl;
			}
		}
		a[n - 1] = b;
		if(b + 1 < k) {
			a[0] = b + 1;
			for(int i = 0; i < n - 1; ++i) {
				for(int j = 0; j < n; ++j)
					cout << a[j];
				swap(a[i], a[i + 1]);
				cout << endl;
			}
		}
	}
	return 0;
}



