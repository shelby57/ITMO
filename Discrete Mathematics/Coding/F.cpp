#include<bits/stdc++.h>
using namespace std;

main() {
	string alf = "abcdefghijklmnopqrstuvwxyz";
	map <int, string> base_num;
	int cnt = 0;
	int n;
	cin >> n;
	vector <int> a(n);
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	for(int i = 0; i < alf.size(); ++i)
		base_num[cnt++] = alf.substr(i,1);


	int old = a[0];
    string buf = "", x = "";
	for(int i = 0; i < n - 1; ++i) {
		int ind = a[i + 1];
		if(base_num.find(ind) == base_num.end()) {
			buf = base_num[old];
			buf = buf + x;
		} else
			buf = base_num[ind];
		x = buf[0];
		base_num[cnt++] = base_num[old] + x;
		old = ind;
	}
	for(int i = 0; i < n; ++i)
		cout << base_num[a[i]];
	return 0;
}
