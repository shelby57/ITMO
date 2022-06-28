#include<bits/stdc++.h>
using namespace std;
bool comp(vector <int> &x, vector <int> &y) {
	int len = min(x.size(), y.size());
	for(int i = 0; i < len; ++i)
		return x[i] > y[i];
	return x.size() > y.size();
}
main() {
	int n;
	cin >> n;
	vector <vector <int> > base;
	for(int i = 0; i < (1 << n); i++) {
		vector <int> a;
		int x = i;
		int pos = 0;
		while(x > 0) {
			if(x % 2 == 1)
				a.push_back(pos);
			pos++;
			x /= 2;
		}
		base.push_back(a);
	}
	sort(base.begin(), base.end());
	for(int i = 0; i < base.size(); ++i) {
		for(auto x : base[i])
			cout << x + 1 << " ";
		cout << endl;
	}
	return 0;
}
