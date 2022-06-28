#include<bits/stdc++.h>
using namespace std;
vector <char> alf(26);
int find_ind(char x) {
	for(int i = 0; i < 26; ++i)
		if(alf[i] == x) {
			alf.erase(alf.begin() + i);
			alf.push_back(x);
			return 26 - i;
		}
	return 0;
}
main() {
	for(int i = 0; i < 26; ++i)
		alf[i] = i + 97;
	reverse(alf.begin(), alf.end());
	string s;
	getline(cin,s);
	int n = s.size();
	for(int i = 0; i < n; ++i)
		cout << find_ind(s[i]) << " ";
	return 0;
}



