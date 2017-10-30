// Original Code: https://algospot.com/wiki/read/Manacher's_algorithm
// C++11
#include <algorithm>

// You can only find odd-length palindromes without padding.
namespace manacher {
	const int MAXN = 200004;
	int dp[MAXN];

	// S[] can be non-null-terminated string.
	void run(const char S[], int N) {
		int r = -1, p = -1;
		for (int i = 0; i < N; ++i) {
			int &di = dp[i];
			if (i <= r) di = std::min(dp[2 * p - i], r - i);
			else di = 0;
			for (++di; i - di >= 0 && i + di < N\
				&& S[i - di] == S[i + di]; ++di);
			--di;
			if (r < i + di) r = i + di, p = i;
		}
	}

	int pad(char T[], const char S[]) {
		const char dl = '#';
		int i;
		T[0] = dl;
		for (i = 0; S[i]; ++i) {
			T[2 * i + 1] = S[i];
			T[2 * i + 2] = dl;
		}
		T[2 * i + 1] = '\0';
		return 2 * i + 1;
	}
}

// Test Code - BOJ 14444
#include <cstdio>

char S1[100004];
char S2[200004];

int main() {
	scanf("%s", S1);

	const int len = manacher::pad(S2, S1);
	manacher::run(S2, len);

	int ans = 1;
	for (int i = 0; i < len; ++i)
		ans = std::max(ans, manacher::dp[i]);
	
	printf("%d\n", ans);
	return 0;
}
