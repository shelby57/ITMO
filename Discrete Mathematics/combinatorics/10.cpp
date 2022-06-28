#include<bits/stdc++.h>
using namespace std;
vector <int> a;
int n, k;
void rec(int s) {
	int i;
	if(s == n) {
		for(i = 0; i < a.size() - 1; ++i) {
			cout << a[i] << "+";
		}
		cout << a[i] << endl;
		++k;
		return;
	}
	for(i = 1; i <= min(a.back(),n - s); ++i) {
		a.push_back(i);
		rec(s + i);
		a.pop_back();
	}
}
main() {
	cin >> n;
	vector <int> ans;
	for(int j = 1; j <= n; ++j) {
		a.push_back(j);
		rec(j);
		a.pop_back();
	}
	if(ans.size() > 0)
		cout << k - ans.back() << endl;
	ans.push_back(k);
	return 0;
}
