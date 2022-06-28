#include<bits/stdc++.h>
using namespace std;
main() {
	string s;
	getline(cin,s);
	cout << s;
	string alf = "abcdefghijklmnopqrstuvwxyz";
	map <string, int> base;
	int cnt = 0;
	for(int i = 0; i < alf.size(); ++i)
		base[alf.substr(i,1)] = cnt++;
	string buf = "";
	for(int i = 0; i < s.size(); ++i)
		if(base.find(buf + s[i]) != base.end())
			buf += s[i];
		else {
			base[buf + s[i]] = cnt++;
			cout << base[buf] << " ";
			buf = s[i];
		}
	cout << base[buf];
	return 0;
}


