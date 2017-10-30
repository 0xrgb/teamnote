// Original Code: ?
// C++11
#include <vector>
#include <deque>
#include <algorithm>

// Using 1-based index
namespace match {
	const int MAXU = 204;
	const int MAXV = 204;
	const int INF = 1000000000; // 1e9

	int U, V;
	std::vector<int> E[MAXU];
	std::deque<int> Q;
	int pu[MAXU], pv[MAXV];
	int lv[MAXU], ht[MAXU];

	bool bfs() {
		for (int u = 1; u <= U; ++u) {
			if (pu[u] == 0) {
				lv[u] = 0;
				Q.push_back(u);
			}
			else lv[u] = INF;
			ht[u] = 0;
		}

		lv[0] = INF;
		while (!Q.empty()) {
			const int u = Q.front();
			Q.pop_front();
			if (lv[u] < lv[0]) {
				for (const int v : E[u]) {
					if (lv[pv[v]] == INF) {
						lv[pv[v]] = lv[u] + 1;
						Q.push_back(pv[v]);
					}
				}
			}
		}

		return lv[0] != INF;
	}

	bool dfs(int u) {
		if (u == 0) return true;
		for (int &i = ht[u]; i < E[u].size(); ++i) {
			const int v = E[u][i];
			if (lv[pv[v]] == lv[u] + 1 && dfs(pv[v])) {
				pv[v] = u;
				pu[u] = v;
				return true;
			}
		}
		lv[u] = INF;
		return false;
	}

	void init(int u, int v) {
		U = u, V = v;
		std::fill(pu, pu + U + 1, 0);
		std::fill(pv, pv + U + 1, 0);
		for (int i = 0; i <= U; ++i) E[i].clear();
	}

	int match() {
		int ans = 0;
		while (bfs()) {
			for (int u = 1; u <= U; ++u) {
				if (pu[u] == 0 && dfs(u)) ++ans;
			}
		}
		return ans;
	}
};

// Test Code - BOJ 2787
#include <cstdio>

const int MAXN = 204;

int N;
bool imp[MAXN][MAXN];

int main() {
	int q;
	scanf("%d%d", &N, &q);
	while (q--) {
		int qt, x, y, v;
		scanf("%d%d%d%d", &qt, &x, &y, &v);
		if (x > y) std::swap(x, y);
		switch(qt) {
		case 1:
			for (int i = 1; i <= N; ++i) {
				if (x <= i && i <= y) {
					for (int j = v + 1; j <= N; ++j) imp[i][j] = true;
				} else imp[i][v] = true;
			}
			break;
		case 2:
			for (int i = 1; i <= N; ++i) {
				if (x <= i && i <= y) {
					for (int j = 1; j < v; ++j) imp[i][j] = true;
				} else imp[i][v] = true;
			}
			break;
		}
	}

	match::init(N, N);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (imp[i][j]) continue;
			match::E[i].push_back(j);
		}
	}

	int ans = match::match();
	if (ans < N) {
		puts("-1");
		return 0;
	}

	for (int i = 1; i <= N; ++i) {
		printf("%d ", match::pu[i]);
	}

	return 0;
}
