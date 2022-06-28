#include<bits/stdc++.h>
using namespace std;
main() {
	ios :: sync_with_stdio(false);
	cin.tie();
	string s1,s2;
	int i,j;
	getline(cin,s1);
	getline(cin,s2);
	int l1 = s1.size() + 1;
	int l2 = s2.size() + 1;
	int dp[l1][l2];
	for(i = 0; i < l1; ++i)
		dp[i][0] = i;
	for(j = 0; j < l2; ++j)
		dp[0][j] = j;
	for(i = 1; i < l1; ++i)
		for(j = 1; j < l2; ++j)
			if(s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			} else {
				dp[i][j] = min(min(dp[i - 1][j],dp[i][j - 1]),dp[i - 1][j - 1]) + 1;
			}
	cout << dp[l1 - 1][l2 - 1];
	return 0;
}