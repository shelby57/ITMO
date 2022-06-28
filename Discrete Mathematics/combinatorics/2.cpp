#include<bits/stdc++.h>
using namespace std;
main() {
	int n;
	cin >> n;
	vector <string> ans;
	ans.push_back("0");
	ans.push_back("1");
	while(ans.size() < (1 << n)) {
		int len = ans.size();
		for(int i = len - 1; i >= 0; --i)
			ans.push_back(ans[i]);
		for(int i = 0; i < len; ++i) {
			ans[i] += "0";
			ans[len + i] += "1";
		}
	}
	for(int i = 0; i < ans.size(); i++)
		cout << ans[i] << endl;
	return 0;
}



