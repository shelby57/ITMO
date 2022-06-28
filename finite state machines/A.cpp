#include<bits/stdc++.h>
using namespace std;
vector<vector<pair<int, char>>> sp;
set <int> dop;
string s;
bool dfs(int v, int num) {
	if (s.size() == num) {
		if(dop.find(v) != dop.end()) {
			return true;
		}
		return false;
	}
	for (auto &x: sp[v])
		if (x.second == s[num])
			return dfs(x.first, num + 1);
	return false;
}
int main() {
	ifstream fin("problem1.in.txt");
	ofstream fout("problem1.out.txt");
	fin >> s;
	int n, m, k;
	fin >> n >> m >> k;
	sp.resize(n);
	int x, y;
	char c;
	for (int i = 0; i < k; ++i) {
		fin >> x;
		dop.insert(x - 1);
	}
	for (int i = 0; i < m; ++i) {
		fin >> x >> y >> c;
		sp[x - 1].push_back({y - 1, c});
	}
	if (dfs(0, 0))
		fout << "Accepts";
	else
		fout << "Rejects";
	fin.close();
	fout.close();
	return 0;
}

