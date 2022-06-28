#include<bits/stdc++.h>
using namespace std;
int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ifstream fin("problem2.in");
	ofstream fout("problem2.out");
	string s;
	fin >> s;

	int n, m, k;
	fin >> n >> m >> k;
	vector <bool> dop(n);
	vector <vector <pair <int,char >>> matr(n);
	int x, y;
	char c;
	for (int i = 0; i < k; ++i) {
		fin >> x;
		dop[x - 1] = true;
	}
	for (int i = 0; i < m; ++i) {
		fin >> x >> y >> c;
		matr[x - 1].push_back({y - 1, c - 'a'});
	}
	set <int> now;
	now.insert(0);
	for(int i = 0; i < s.size(); ++i) {
		set <int> next;
		c = s[i] - 'a';
		for(auto &v : now)
			for(auto &u: matr[v])
				if(u.second == c)
					next.insert(u.first);
		now.clear();
		now = next;
	}
	fin.close();
	for(auto &v : now) {
		if(dop[v]) {
			fout << "Accepts";
			fout.close();
			return 0;
		}
	}
	fout << "Rejects";
	fout.close();
	return 0;
}

