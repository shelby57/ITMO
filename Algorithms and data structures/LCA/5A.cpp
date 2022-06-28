#include<bits/stdc++.h>
using namespace std;
vector <vector <int> > out,jmp;
vector <bool> mark;
vector <int> dist,way;
int n;
void dfs(int v,int k) {
	if(mark[v])
		return;
	mark[v] = 1;
	dist[v] = k;
	way.push_back(v);
	int s = 1;
	while(s <= k) {
		jmp[v].push_back(way[k - s]);
		s *= 2;
	}
	for(auto x : out[v])
		dfs(x,k + 1);
	way.pop_back();
}
int lca(int u,int v) {
	if(dist[u] < dist[v])
		swap(u,v);
	int d = dist[u] - dist[v];
	for(int k = trunc(log2(n)); k >= 0; --k)
		if(d >= (1 << k)) {
			u = jmp[u][k];
			d -= (1 << k);
		}
	if(u == v)
		return u;
	for(int k = trunc(log2(n)); k >= 0; --k) {
		if(k >= jmp[u].size() || k >= jmp[v].size())
			continue;
		int u1 = jmp[u][k];
		int v1 = jmp[v][k];
		if(u1 != v1) {
			u = u1;
			v = v1;
		}
	}
	return jmp[u][0];
}
main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	out.resize(n);
	dist.resize(n);
	mark.assign(n,0);
	jmp.resize(n);
	int v;
	for(int i = 1; i < n; ++i) {
		cin >> v;
		out[v - 1].push_back(i);
	}
	dfs(0,0);
	int m,u;
	cin >> m;
	for(int i = 0; i < m; ++i)  {
		cin >> u >> v;
		cout << lca(u - 1,v - 1) + 1 << endl;
	}
	return 0;
}