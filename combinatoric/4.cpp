#include<bits/stdc++.h>
using namespace std;
main() {
	int n;
	cin >> n;
	set <string> base;
	string s = "";
	for(int i = 0; i < n; i++)
		s += "0";
	bool ok = 0;
	do {
		cout << s << endl;
		ok = true;
		base.insert(s);
		string x = s.substr(1) + "1";
		if(base.find(x) == base.end()) {
			base.insert(x);
			s = x;
			ok = false;
		}  else {
			x = s.substr(1) + "0";
			if(base.find(x) == base.end()) {
				base.insert(x);
				ok = false;
				s = x;
			}
		}
	} while(!ok);
	
	return 0;
}
