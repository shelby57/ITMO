#include<bits/stdc++.h>
using namespace std;
vector <int> cnt, len, p;

int find(int x) {
	if(p[x] != x)
		return find(p[x]);
	return x;
}

void uni(int x,int y) {
	x = find(x);
	y = find(y);
	if(x == y)
		return;
	if(len[x] > len[y])
		swap(x,y);
	p[x] = y;
	cnt[x] -= cnt[y];
	len[y] += len[x];
}

int get(int x) {
	int sum = 0;
	while(p[x] != x) {
		sum += cnt[x];
		x = p[x];
	}
	sum += cnt[x];
	return sum;
}

void add(int x, int v) {
	x = find(x);
	cnt[x] += v;
}

main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin >> n >> m;
	string s;
	len.assign(n,1);
	cnt.assign(n,0);
	p.resize(n);
	for(int i = 0; i < n; ++i)
		p[i] = i;
	getline(cin,s);
	for(int i = 0; i < m; ++i) {
		getline(cin,s);
		vector <string> b;
		int ns = 0;
		s += " ";
		for(int i = 0; i < s.size() - 1; ++i) {
			if(s[i] == ' ' && s[i + 1] != ' ')
				ns = i + 1;
			if(s[i] != ' ' && s[i + 1] == ' ')
				b.push_back(s.substr(ns,i - ns + 1));
		}
		if(b[0] == "add") {
			int x = atoi(b[1].c_str());
			int v = atoi(b[2].c_str());
			add(x - 1,v);
		}
		if(b[0] == "join") {
			int x = atoi(b[1].c_str());
			int y = atoi(b[2].c_str());
			uni(x - 1,y - 1);
		}
		if(b[0] == "get") {
			int x = atoi(b[1].c_str());
			cout << get(x - 1) << endl;
		}
	}
	return 0;
}

