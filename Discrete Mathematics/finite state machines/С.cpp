#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> sp;
vector<bool> dop;
vector<int> weight;
vector<int> mark;
vector<int> countt;
const int mod = 1e9 + 7;
bool ok = true;
void dfs(int v, int cnt) {
	if (mark[v] == 2)
		return;
	if (mark[v] == 1) {
		ok = false;
		return;
	}
	countt[v] = cnt;
	mark[v] = 1;
	for (auto &x: sp[v])
		dfs(x, cnt * weight[v] % mod);
	mark[v] = 2;
}
int main() {
	ifstream fin("problem3.in");
	ofstream fout("problem3.out");
	int n, m, k;
	fin >> n >> m >> k;
	sp.resize(n);
	dop.assign(n, false);
	countt.assign(n, 0);
	weight.assign(n, 0);
	mark.assign(n, 0);
	int x, y;
	for (int i = 0; i < k; ++i) {
		fin >> x;
		dop[x - 1] = true;
	}
	char c;
	for (int i = 0; i < m; ++i) {
		fin >> x >> y >> c;
		sp[x - 1].push_back(y - 1);
		++weight[x - 1];
	}
	dfs(0, 1);
	int res = 0;
	for (int i = 0; i < n; ++i)
		if (dop[i])
			res += countt[i];
	if(res == 0) {
		fout << res;
		fout.close();
	}
	if (!ok) {
		fout << -1;
		fout.close();
	}
	fout << res;

	fout << res;
	fin.close();
	fout.close();
	return 0;
}

