#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;
int32_t main() {
	ios ::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ifstream fin("nfc.in");
	ofstream fout("nfc.out");
	int n;
	char start, c;
	fin >> n >> start;
	string s;
	vector<vector<pair<int, int>>> base(26);

	for (int i = 0; i < n; ++i) {
		fin >> c >> s >> s;
		int u = c - 'A';
		if (s.size() == 1)
			base[u].emplace_back(s[0] - 'a', -1);
		else
			base[u].emplace_back(s[0] - 'A', s[1] - 'A');
	}

	fin >> s;
	std::size_t len = s.size();
	vector<vector<vector<int>>> dp(26, vector<vector<int>>(len, vector<int>(len)));
	for (int j = 0; j < 26; ++j)
		for (int i = 0; i < len; ++i)
			for (auto &x: base[j])
				if (x.second == -1 && (s[i] - 'a') == x.first)
					++dp[j][i][i];

	for (int m = 2; m <= len; ++m)
		for (int left = 0; left < len - m + 1; ++left)
			for (int j = left; j < left + m - 1; ++j)
				for (int i = 0; i < 26; ++i)
					for (auto &x: base[i])
						if (x.second != -1)
							dp[i][left][left + m - 1] = (dp[i][left][left + m - 1] + dp[x.first][left][j] % mod * (dp[x.second][j + 1][left + m - 1] % mod)) % mod;

	fout << dp[start - 'A'][0][len - 1] % mod;
	fin.close();
	fout.close();
	return 0;
}
