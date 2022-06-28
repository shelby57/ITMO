#include<bits/stdc++.h>
using namespace std;
struct node {
	int l,r;
};
bool comp(string &x, string &y) {
	return x[0] < y[0];
}
main() {
	string s;
	getline(cin,s);
	int n = s.size();
	vector <char> a(n);
	vector <string> ans(n);
	for(int i = 0; i < n; ++i)
		a[i] = s[i];
	sort(a.begin(), a.end());
	vector <node> srt;
	int l = 0,r = 0;
	while(r < n) {
		while(r < n && a[l] == a[r])
			++r;
		srt.push_back({l,r});
		l = r;
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			ans[j] = s[j] + ans[j];
		}
		sort(ans.begin(),ans.end(), comp);
		for(auto x : srt)
			sort(ans.begin() + x.l, ans.begin() + x.r);
	}
	cout << ans[0];
	return 0;
}

