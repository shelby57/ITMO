#include<bits/stdc++.h>
using namespace std;
struct node {
	int w,c,ind;
};
bool comp(node &x, node &y) {
	return x.w < y.w;
}
main() {
	int n,s;
	cin >> n >> s;
	++n;
	++s;
	int dp[n][s];
	vector <node> a(n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < s; ++j)
			dp[i][j] = 0;
	for(int i = 1; i < n; ++i) {
		cin >> a[i].w;
		a[i].ind = i;
	}
	for(int i = 1; i < n; ++i)
		cin >> a[i].c;
	sort(a.begin(), a.end(), comp);
	int mxi = -1, mxj = -1, mx = 0;
	for(int i = 1; i < n; ++i)
		for(int j = 1; j < s; ++j) {
			dp[i][j] = dp[i - 1][j];
			if(j < a[i].w)
				continue;
			dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i].w] + a[i].c);
			if(dp[i][j] > mx) {
				mx = dp[i][j];
				mxi = i;
				mxj = j;
			}
		}
	if(mx == 0) {
		cout << 0;
		return 0;
	}
	vector <int> ans;
	while(mxj > 0 && mxi > 0) {
		if(dp[mxi - 1][mxj] == dp[mxi][mxj])
			--mxi;
		else {
			ans.push_back(a[mxi].ind);
			mxj -= a[mxi--].w;
		}
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for(auto x : ans)
		cout << x << " ";
	return 0;
}

