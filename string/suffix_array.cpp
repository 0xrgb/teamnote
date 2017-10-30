// Original Code: Competitive Programming 3 (p257)
// C++11
#include <algorithm>

namespace suffix {
	const int MAXN = 500004;

	int RA[MAXN], tRA[MAXN];
	int SA[MAXN], tSA[MAXN];
	int LCP[MAXN];
	int cnt[MAXN]; // Use in countingSort

	void countingSort(int k, int N) {
		int i, sum, NN = std::max(128, N);
		std::fill(cnt, cnt + NN + 1, 0);
		for (i = 0; i < N; ++i)
			cnt[i + k < N ? RA[i + k] : 0]++;
		for (i = sum = 0; i <= NN; ++i) {
			int t = cnt[i]; cnt[i] = sum; sum += t;
		}
		for (int i = 0; i < N; ++i)
			tSA[cnt[SA[i] + k < N ? RA[SA[i] + k] : 0]++] = SA[i];
		std::copy(tSA, tSA + N, SA);
	}

	// Complexity: O(N lg N)
	void createSA(const char T[], int N) {
		for (int i = 0; i < N; ++i)
			RA[i] = T[i], SA[i] = i;

		tRA[N] = RA[N] = 0;
		for (int k = 1; k < N; k <<= 1) {
			countingSort(k, N);
			countingSort(0, N);

			int r;
			tRA[SA[0]] = r = 1;
			for (int i = 1; i < N; ++i) {
				tRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]]\
					&& RA[SA[i] + k] == RA[SA[i - 1] + k])\
					? r : ++r;
			}

			std::copy(tRA, tRA + N, RA);
			if (r >= N) break;
		}

		for (int i = 0; i < N; ++i) --RA[i];
	}

	// Complexity: O(N)
	void createLCP(const char T[], int N) {
		for (int i = 0, k = 0; i < N; ++i) {
			if (k != 0) --k;

			const int nowr = RA[i];
			if (nowr <= 0) continue;

			for (int j = SA[nowr - 1]; T[i + k] == T[j + k]; ++k);
			LCP[nowr] = k;
		}
		LCP[0] = -1;
	}
};

// Test Code - BOJ 9248
#include <cstdio>
#include <cstring>

char D[suffix::MAXN];

int main() {
	scanf("%s", D);
	int len = strlen(D);

	suffix::createSA(D, len);
	suffix::createLCP(D, len);

	for (int i = 0; i < len; ++i)
		printf("%d ", suffix::SA[i] + 1);

	printf("\nx ");
	for (int i = 1; i < len; ++i)
		printf("%d ", suffix::LCP[i]);

	return 0;
}
