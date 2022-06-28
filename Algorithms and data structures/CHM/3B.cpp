#include<bits/stdc++.h>
using namespace std;
struct node {
	char op;
	int x,y;
};
vector <int> p,len;
int find(int x) {
	if(p[x] != x)
		p[x] = find(p[x]);
	return p[x];
}
void uni(int x,int y) {
	x = find(x);
	y = find(y);
	if(x == y)
		return;
	if(len[x] > len[y])
		swap(x,y);
	p[x] = y;
	len[y] += len[x];
}
string ask(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y)
		return "YES";
	return "NO";
}
main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,k;
	cin >> n >> m >> k;
	len.assign(n,1);
	p.resize(n);
	for(int i = 0; i < n; ++i)
		p[i] = i;
	int x,y;
	for(int i = 0; i < m; ++i)
		cin >> x >> y;
	vector <node> a(k);
	for(int i = 0; i < k; ++i) {
		for(int j = 0; j < 3; ++j)
			cin >> a[i].op;
		cin >> a[i].x >> a[i].y;
	}
	vector <string> ans;
	for(int i = a.size() - 1; i >= 0; --i)
		if(a[i].op == 'k') {
			ans.push_back(ask(a[i].x - 1, a[i].y - 1));
		} else {
			uni(a[i].x - 1, a[i].y - 1);
		}
	for(int i = ans.size() - 1; i >= 0; --i)
		cout << ans[i] << endl;
	return 0;
}
