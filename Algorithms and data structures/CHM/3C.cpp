#include<bits/stdc++.h>
using namespace std;
int n;
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
int place(int x) {
	int ans;
	if(p[x] == -1)
		ans = x;
	else {
		x = (find(x) + 1) % n;
		ans = x;
	}
	p[x] = x;
	int up = (x + 1) % n;
	int down = (x - 1 + n) % n;
	if(p[up] != -1) {
		up = find(up);
		p[x] = up;
	}
	if(p[down] != -1)
		p[down] = p[x];
	return ans + 1;
}
main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int x;
	cin >> n;
	len.assign(n,1);
	p.resize(n);
	for(int i = 0; i < n; ++i)
		p[i] = -1;
	for(int i = 0; i < n; ++i) {
		cin >> x;
		cout << place(x - 1) << " ";
	}
	return 0;
}

