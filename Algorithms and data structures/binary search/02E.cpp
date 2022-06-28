#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n,a,b,w,h;
bool f(int d) {
	int x = w / (a + 2 * d);
	int y = h / (b + 2 * d);
	bool ok = 0;
	if(x != 0 && y != 0)
		ok = ((n + x - 1) / x <= y);
	if(ok)
		return ok;
	x = h / (a + 2 * d);
	y = w / (b + 2 * d);
	if(x != 0 && y != 0)
		ok = ((n + x - 1) / x <= y);
	return ok;
}
main() {
	cin >> n >> a >> b >> w >> h;
	int l = 0,r = 1e18;
	while(r - l > 1) {
		int m = (r + l) / 2;
		if(f(m))
			l = m;
		else
			r = m;
	}
	if(f(r))
		cout << r;
	else
		cout << l;
	return 0;
}
