#include<bits/stdc++.h>
using namespace std;
main() {
	int flag;
	cin >> flag;
	string s;
	getline(cin, s);
	getline(cin, s);
	vector <int> a;
	int p = 1;
	int cnt_s = 0;
	int n = s.size();
	if(flag == 1) {
		while(cnt_s < n) {
			if(p == a.size() + 1) {
				a.push_back(0);
				p *= 2;
				continue;
			}
			a.push_back(s[cnt_s++] - 48);
		}
		int m = ceil(log2(p));
		vector <vector <int> > base(m, vector <int> (a.size()));
		for(int j = 0; j < a.size(); ++j) {
			int x = j + 1;
			int i = 0;
			while(x > 0) {
				base[i++][j] = x % 2;
				x /= 2;
			}
		}
		vector <int> res(m);
		for(int i = 0; i < m; ++i) {
			int sum = 0;
			for(int j = 0; j < base[i].size(); ++j)
				sum += a[j] * base[i][j];
			res[i] = sum % 2;
		}
		p = 1;
		for(int i = 0; i < m; ++i, p *= 2)
			a[p - 1] = res[i];
		for(auto x : a)
			cout << x;
		cout << '\n';	
	} else {
		for(int i = 0; i < s.size(); ++i)
			a.push_back(s[i] - 48);
		int m = ceil(log2(a.size()));
		vector <vector <int> > base(m, vector <int> (a.size()));
		for(int j = 0; j < a.size(); ++j) {
			int x = j + 1;
			int i = 0;
			while(x > 0) {
				base[i++][j] = x % 2;
				x /= 2;
			}
		}
		vector <int> res(m);
		for(int i = 0; i < m; ++i) {
			int sum = 0;
			for(int j = 0; j < base[i].size(); ++j)
				sum += a[j] * base[i][j];
			res[i] = sum % 2;
		}
		p = 1;
		int num = 0;
		for(int i = 0; i < m; ++i, p *= 2)
			num += res[i] * p;
		if(a[num - 1] == 0)
			a[num - 1] = 1;
		else
			a[num - 1] = 0;
		p = 1;
		for(int i = 0; i < a.size(); ++i)
			if(i != p - 1) {
				cout << a[i];
			} else {
				p *= 2;
			}
		cout << '\n';	
	}
	return 0;
}/*100100101110001
  11110110001011110001*/




