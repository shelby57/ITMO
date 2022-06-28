#include<bits/stdc++.h>
using namespace std;
main() {
	string s;
	getline(cin, s);
	if(s == "()") {
		cout << 2;
		return 0;
	}
	bool ok = 1;
	int n = s.size();
	vector <int> pref(n);
	int cntl = 0, cntr = 0;
	for(int i = 0; i < n; ++i) {
		if(s[i] == '(')
			++cntl;
		else
			++cntr;
		if(cntl < cntr)
			ok = 0;
	}
	if(cntl != cntr)
		ok = 0;
	if(!ok) {
		cout << 0;
		return 0;
	}
	vector <int> p(n);
	int cnt = 0, ans = 1, k = 1;
	for(int i = 0; i < n; ++i) {
		if(s[i] == '(') {
			cnt++;
		}
		if(s[i] == ')') {
			k *= cnt;
			cnt--;
		}
		if(cnt == 0) {
			k *= 2;
			if(k == 1) {
				
			ans *= (k * 2 + 2);
		}
	}
	cout << ans;
	return 0;
}
