// Original Code: ?
// C++11

// 1-based string
namespace kmp {
	const int MAXN = 5004;

	int F[MAXN];
	int D[MAXN];

	// P[0], S[0] can be anything.
	// F[0], D[0] == 0
	int createF(const char P[]) {
		int i;
		F[1] = 0;
		for (i = 2; P[i]; ++i) {
			int v = F[i - 1];
			while (true) {
				if (P[i] == P[v + 1]) {
					F[i] = v + 1;
					break;
				} else if (v == 0) {
					F[i] = 0; // Add this to re-use
					break;
				}
				v = F[v];
			}
		}
		return i - 1;
	}

	int createD(const char S[], const char P[]) {
		int i;
		for (i = 1; S[i]; ++i) {
			int v = D[i - 1];
			while (true) {
				if (S[i] == P[v + 1]) {
					D[i] = v + 1;
					break;
				} else if (v == 0) {
					D[i] = 0; // Add this to re-use
					break;
				}
				v = F[v];
			}
		}
		return i - 1;
	}
};

// Test Code - BOJ 1701
#include <cstdio>
#include <algorithm>

char D1[kmp::MAXN];

int main() {
	scanf(" %[^\n]s", D1 + 1);

	int ans = 0;
	for (int i = 1; D1[i]; ++i) {
		int s = kmp::createF(D1 + (i - 1));
		for (int j = 1; j <= s; ++j) {
			ans = std::max(ans, kmp::F[j]);
		}
	}

	printf("%d\n", ans);
	return 0;
}
