// Original Code: https://blog.qwaz.io/problem-solving/scc%EC%99%80-2-sat
// C++11
#include <vector>
#include <algorithm>

namespace scc {
	using namespace std;
	const int MAXN = 20004;

	int N;
	vector<int> E[MAXN];
	vector<int> S;
	bool iss[MAXN];
	int idx[MAXN], idx_cnt = 0;
	int scc[MAXN], scc_cnt = 0;

	void init(int n) {
		N = n;
		for (int i = 0; i < N; ++i) E[i].clear();
		S.clear();
		fill(iss, iss + N, false);
		fill(idx, idx + N, 0);
		fill(scc, scc + N, 0);
		idx_cnt = scc_cnt = 0;
	}

	int dfs(int p) {
		int t = idx[p] = ++idx_cnt;
		S.push_back(p);
		iss[p] = true;
		for (const int u : E[p]) {
			if (!idx[u]) t = min(t, dfs(u));
			else if (iss[u]) t = min(t, idx[u]);
		}

		if (t == idx[p]) {
			int sb;
			++scc_cnt;
			do {
				sb = S.back();
				S.pop_back();
				iss[sb] = false;
				scc[sb] = scc_cnt;
			} while (sb != p);
		}

		return t;
	}

	void tarjan() {
		for (int i = 0; i < N; ++i) {
			if (idx[i]) continue;
			dfs(i);
		}
	}
}

// Test Code - BOJ 11281
#include <cstdio>
int N, M;
int ans[10004];

int main() {
	scanf("%d%d", &N, &M);
	scc::init(N * 2);

	for (int i = 0; i < M; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);

		if (x < 0) x = ((-x - 1) << 1) | 1;
		else x = (x - 1) << 1;
		if (y < 0) y = ((-y - 1) << 1) | 1;
		else y = (y - 1) << 1;

		scc::E[x ^ 1].push_back(y);
		scc::E[y ^ 1].push_back(x);
	}

	scc::tarjan();

	// if (scc[x] == scc[!x]) => impossible
	// elif (scc[x] > scc[!x]) => x: false (x => !x could exist)
	// else => x: true
	bool is_possible = true;
	for (int i = 0; i < N; ++i) {
		int x1 = scc::scc[i << 1];
		int x2 = scc::scc[(i << 1) | 1];

		if (x1 == x2) {
			is_possible = false;
			break;
		}
		else ans[i] = (x1 < x2);
	}

	if (!is_possible) {
		puts("0");
		return 0;
	}

	puts("1");
	for (int i = 0; i < N; ++i)
		printf("%d ", ans[i]);

	return 0;
}
